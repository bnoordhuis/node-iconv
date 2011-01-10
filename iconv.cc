#include "iconv.h"

#include "Recoder.h"

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

using Recode::Recoder;
using Recode::RecoderResult;

/**
 * node.js glue, placeholder/proxy for the Recoder.
 */
class Iconv: public ObjectWrap {
public:
	static Handle<Value> New(const Arguments& args);
	static Handle<Value> Convert(const Arguments& args);

private:
	static Handle<Value> ToBuffer(RecoderResult rr);
	static Handle<Value> ToString(RecoderResult rr);

	Iconv(Recoder* recoder): recoder_(recoder) {
	}

	// destructor may not run if program is short-lived or aborted
	~Iconv() {
		delete recoder_;
	}

	Handle<Value> Convert(const char* data, size_t size);

	// used by Iconv::ToString()
	class ExternalStringResource: public String::ExternalStringResource {
	public:
		ExternalStringResource(char* data, size_t size): data_(data), size_(size) {
			assert(data_ != 0);
	        assert(size_ != 0);
		}
		virtual ~ExternalStringResource() {
			delete[] data_;
		}
		virtual const uint16_t* data() const {
			return (const uint16_t *) data_;
		}
		virtual size_t length() const {
			return size_;
		}
	private:
		const char* data_;
		const size_t size_;
	};

	// and this is what it's all about
	Recoder* recoder_;
};

Handle<Value> Iconv::New(const Arguments& args) {
	HandleScope scope;

	String::Utf8Value sourceEncoding(args[0]->ToString());
	String::Utf8Value targetEncoding(args[1]->ToString());

	Recoder* recoder = Recoder::New(*sourceEncoding, *targetEncoding);

	if (recoder == 0) {
		Local<String> message = String::New("Conversion not supported.");

		return ThrowException(Exception::Error(message));
	}

	(new Iconv(recoder))->Wrap(args.Holder());

	return args.This();
}

Handle<Value> Iconv::Convert(const char* data, size_t size) {
	Handle<Value> rv;

	if (recoder_->Recode(data, size)) {
		rv = Iconv::ToBuffer(recoder_->GetResult());
	}
	else {
		Local<Value> ex = ErrnoException(
				recoder_->GetErrorNumber(), "iconv", recoder_->GetErrorMessage());

		rv = ThrowException(ex);
	}

	recoder_->Reset();

	return rv;
}

Handle<Value> Iconv::Convert(const Arguments& args) {
	HandleScope scope;

	Iconv* self = ObjectWrap::Unwrap<Iconv>(args.This());

	Local<Value> arg = args[0];

	if (arg->IsString()) {
		String::Utf8Value string(arg->ToString());

		return self->Convert(
				*string, string.length());
	}

	if (arg->IsObject()) {
		Local<Object> object = arg->ToObject();

		if (Buffer::HasInstance(object)) {
			return self->Convert(
					Buffer::Data(object), Buffer::Length(object));
		}
	}

	// this should arguably throw an exception
	// but let's keep it for backward compatibility's sake
	return Undefined();
}

void FreeMemory(char* data, void* arg) {
	delete[] data;
}

Handle<Value> Iconv::ToBuffer(RecoderResult rr) {
	Buffer* buffer = Buffer::New(
			rr.Data(), rr.Size(), FreeMemory, NULL);

	return buffer->handle_;
}

Handle<Value> Iconv::ToString(RecoderResult rr) {
	HandleScope scope;

	String::ExternalStringResource* resource =
			new Iconv::ExternalStringResource(rr.Data(), rr.Size());

	Local<String> string = String::NewExternal(resource);

	return scope.Close(string);
}

extern "C" void init(Handle<Object> target) {
	HandleScope scope;

	Local<FunctionTemplate> t = FunctionTemplate::New(Iconv::New);
	t->InstanceTemplate()->SetInternalFieldCount(1);

	NODE_SET_PROTOTYPE_METHOD(t, "convert", Iconv::Convert);

	target->Set(String::NewSymbol("Iconv"), t->GetFunction());
}

} // namespace
