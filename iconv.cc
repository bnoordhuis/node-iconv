#include "iconv.h"

#include <v8.h>
#include <node.h>
#include <node_buffer.h>

#include <strings.h>	// strcasecmp + strncasecmp
#include <string.h>
#include <errno.h>

#include <list>

using namespace v8;
using namespace node;

namespace {

class Iconv: public ObjectWrap {
public:
	static void Initialize(Handle<Object>& target);
	static Handle<Value> New(const Arguments& args);
	static Handle<Value> Convert(const Arguments& args);

	Iconv(iconv_t conv);
	~Iconv(); // destructor may not run if program is short-lived or aborted

	// the actual conversion happens here
	Handle<Value> Convert(char* data, size_t length);

private:
	iconv_t conv_;
};

Iconv::Iconv(iconv_t conv): conv_(conv) {
	assert(conv_ != (iconv_t) -1);
}

Iconv::~Iconv() {
	iconv_close(conv_);
}

// helper class: reverse linked list of dumb buffers
struct chunk {
	size_t size;
	char data[32 * 1024];

	chunk(): size(0) {
	}
};

// the actual conversion happens here
Handle<Value> Iconv::Convert(char* data, size_t length) {
	assert(conv_ != (iconv_t) -1);
	assert(data != 0);

	std::list<chunk> chunks;

	char *inbuf = data;
	size_t inbytesleft = length;
	size_t size = 0;

	int index = 0;
	while (true) {
		// smart compilers will optimize chunks.push_back(chunk()) down to a zero-copy operation
		// but we'll assume the worst and do it manually
		chunks.resize(++index);
		chunk& c = chunks.back();

		char *outbuf = c.data;
		size_t outbytesleft = sizeof(c.data);

		size_t rv = iconv(conv_, &inbuf, &inbytesleft, &outbuf, &outbytesleft);
		c.size = sizeof(c.data) - outbytesleft;
		size += c.size;

		if (rv != (size_t) -1) {
			assert(inbytesleft == 0);
			break;
		}

		if (errno == E2BIG) {
			continue;
		}

		if (errno == EINVAL) {
			// write out shift sequences (if any)
			rv = iconv(conv_, 0, 0, &outbuf, &outbytesleft);
			if (errno == E2BIG) {
				// chunk is too small to contain the shift sequence, retry with new chunk
				chunks.resize(++index);
				chunk& c = chunks.back();	// FIXME shadowing another variable is bad style

				outbuf = c.data;
				outbytesleft = sizeof(c.data);

				rv = iconv(conv_, 0, 0, &outbuf, &outbytesleft);
				if (rv != (size) -1) {
					c.size = rv;
				}
			}

			// we're still in an error condition if iconv() hasn't written any bytes
			if (rv != 0 && rv != (size_t) -1) {
				break;
			}

			if (rv == 0 || errno == EINVAL) {
				return ThrowException(ErrnoException(EINVAL, "iconv", "Incomplete character sequence."));
			}
			// deliberate fall through
		}

		if (errno == EILSEQ) {
			return ThrowException(ErrnoException(errno, "iconv", "Illegal character sequence."));
		}

		return ThrowException(ErrnoException(errno, "iconv"));
	}

	// copy chunks into buffer
	Buffer& b = *Buffer::New(size);

	char* p = Buffer::Data(b.handle_);
	for (std::list<chunk>::const_iterator chunk = chunks.begin(), end = chunks.end(); chunk != end; ++chunk) {
		memcpy(p, chunk->data, chunk->size);
		p += chunk->size;
	}

	return b.handle_;
}

Handle<Value> Iconv::Convert(const Arguments& args) {
	HandleScope scope;

	Iconv* self = ObjectWrap::Unwrap<Iconv>(args.This());
	Local<Value> arg = args[0];

	if (arg->IsString()) {
		String::Utf8Value string(arg->ToString());
		return self->Convert(*string, string.length());
	}

	if (arg->IsObject()) {
		Local<Object> object = arg->ToObject();
		if (Buffer::HasInstance(object)) {
			//Buffer& buffer = *ObjectWrap::Unwrap<Buffer>(object);
			return self->Convert(Buffer::Data(object), Buffer::Length(object));
		}
	}

	return Undefined();
}

// workaround for shortcoming in libiconv: "UTF-8" is recognized but "UTF8" isn't
const char* fixEncodingName(const char* name) {
	if (!strncasecmp(name, "UTF", 3) && name[3] != '-') {
		const char* s = &name[3];

		// this code is arguably too clever by half
		switch (*s++) {
		case '1':
			if (!strcmp(s, "6"))       return "UTF-16";
			if (!strcasecmp(s, "6LE")) return "UTF-16LE";
			if (!strcasecmp(s, "6BE")) return "UTF-16BE";
			break;
		case '3':
			if (!strcmp(s, "2"))       return "UTF-32";
			if (!strcasecmp(s, "2LE")) return "UTF-32LE";
			if (!strcasecmp(s, "2BE")) return "UTF-32BE";
			break;
		case '7':
			if (!*s) return "UTF-7";
			break;
		case '8':
			if (!*s) return "UTF-8";
			break;
		}
	}
	return name;
}

Handle<Value> Iconv::New(const Arguments& args) {
	HandleScope scope;

	// inconsistency: node-iconv expects (source, target) while native iconv expects (target, source)
	// wontfix for now, node-iconv's approach feels more intuitive
	String::AsciiValue sourceEncoding(args[0]->ToString());
	String::AsciiValue targetEncoding(args[1]->ToString());

	iconv_t conv = iconv_open(
			fixEncodingName(*targetEncoding),
			fixEncodingName(*sourceEncoding));
	if (conv == (iconv_t) -1) {
		return ThrowException(ErrnoException(errno, "iconv_open", "Conversion not supported."));
	}

	Iconv* instance = new Iconv(conv);
	instance->Wrap(args.Holder());

	return args.This();
}

void Iconv::Initialize(Handle<Object>& target) {
	HandleScope scope;

	Local<FunctionTemplate> t = FunctionTemplate::New(Iconv::New);
	t->InstanceTemplate()->SetInternalFieldCount(1);

	NODE_SET_PROTOTYPE_METHOD(t, "convert", Iconv::Convert);

	target->Set(String::NewSymbol("Iconv"), t->GetFunction());
}

extern "C" void init(Handle<Object> target) {
	Iconv::Initialize(target);
}

} // namespace
