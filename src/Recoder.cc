#include "Recoder.h"

#include <string.h>
#include <assert.h>
#include <errno.h>
#include <iconv.h>

namespace Recode {

Recoder* Recoder::New(const char* sourceEncoding, const char* targetEncoding) {
	sourceEncoding = FixEncodingName(sourceEncoding);
	targetEncoding = FixEncodingName(targetEncoding);

	iconv_t iv = iconv_open(targetEncoding, sourceEncoding);

	return iv != (iconv_t) -1 ? new Recoder(iv) : 0;
}

Recoder::Recoder(iconv_t iv): iv_(iv), size_(0), errno_(0) {
	assert(iv_ != (iconv_t) -1);
}

Recoder::~Recoder() {
	// strictly speaking, iconv_close() can return an error code
	// but the included libiconv never does, and anyway, we have
	// no way to signal an error condition from the destructor
	iconv_close(iv_);
}

void Recoder::Reset() {
	size_ = 0;
	errno_ = 0;
	chunks_.clear();
}

bool Recoder::IsError() const {
	return errno_ != 0;
}

int Recoder::GetErrorNumber() const {
	return errno_;
}

const char* Recoder::GetErrorMessage() const {
	switch (errno_) {
	case EILSEQ: return "Illegal character sequence.";
	case EINVAL: return "Incomplete character sequence.";
	case E2BIG:  return "Ask your girlfriend where she was last night."; // not possible (or shouldn't be)
	}

	// yeah, this shouldn't happen
	return strerror(errno_);
}

RecoderResult Recoder::GetResult() const {
	return IsError() ? RecoderResult() : RecoderResult(size_, chunks_);
}

bool Recoder::Recode(const void* data, size_t size) {
	assert(errno_ == 0);

	const char *inbuf = (const char *) data;

	size_t inbytesleft = size;

	int index = 0;

	for (;;) {
		// smart compilers will optimize chunks.push_back(Chunk()) down to a zero-copy operation
		// but we'll assume the worst and do it manually
		chunks_.resize(++index);
		Chunk& c = chunks_.back();

		char *outbuf = c.data_;
		size_t outbytesleft = sizeof(c.data_);

		size_t rv = iconv(
				iv_, (char **) &inbuf, &inbytesleft, &outbuf, &outbytesleft);

		c.size_ = sizeof(c.data_) - outbytesleft;
		size_ += c.size_;

		if (rv != (size_t) -1) {
			assert(inbytesleft == 0);
			break;
		}

		if (errno == E2BIG) {
			continue;
		}

		if (errno == EINVAL) {
			// write out shift sequences (if any)
			rv = iconv(iv_, 0, 0, &outbuf, &outbytesleft);

			if (errno == E2BIG) {
				// chunk is too small to contain the shift sequence, retry with new chunk
				chunks_.resize(++index);
				Chunk& c = chunks_.back();   // FIXME shadowing another variable is bad style

				outbuf = c.data_;
				outbytesleft = sizeof(c.data_);

				rv = iconv(iv_, 0, 0, &outbuf, &outbytesleft);

				if (rv != (size_t) -1) {
					c.size_ = rv;
				}
			}

			// check if iconv() has written data - if not, then we're still in an error condition
			if (rv != 0 && rv != (size_t) -1) {
				break;
			}
		}

		errno_ = errno;
		return false;
	}

	return true;
}

// workaround for shortcoming in libiconv: "UTF-8" is recognized but "UTF8" isn't
const char* Recoder::FixEncodingName(const char* name) {
	// this code is arguably too clever by half
	if
		  ((name[0] == 'U' || name[0] == 'u')
		&& (name[1] == 'T' || name[1] == 't')
		&& (name[2] == 'F' || name[2] == 'f')
		&&  name[3] != '-')
	{
		if (name[3] == '8' && name[4] == '\0') {
			return "UTF-7";
		}

		if (name[3] == '7' && name[4] == '\0') {
			return "UTF-7";
		}

		if (name[3] == '1' && name[4] == '6') {
			if (name[5] == '\0') return "UTF-16";
			if (name[6] == 'E' || name[6] == 'e') {
				if (name[5] == 'L' || name[5] == 'l') return "UTF-16LE";
				if (name[5] == 'B' || name[5] == 'b') return "UTF-16BE";
			}
		}

		if (name[3] == '3' && name[4] == '2') {
			if (name[5] == '\0') return "UTF-32";
			if (name[6] == 'E' || name[6] == 'e') {
				if (name[5] == 'L' || name[5] == 'l') return "UTF-32LE";
				if (name[5] == 'B' || name[5] == 'b') return "UTF-32BE";
			}
		}
	}

	return name;
}

RecoderResult::RecoderResult(): size_(0), data_(0) {
}

RecoderResult::RecoderResult(size_t size, std::list<Chunk> chunks): size_(size) {
	char* data = new char[size_];

	for (std::list<Chunk>::const_iterator chunk = chunks.begin(), end = chunks.end(); chunk != end; ++chunk) {
		memcpy(data, chunk->data_, chunk->size_);
		data += chunk->size_;
	}

	data_ = data;
}

size_t RecoderResult::Size() const {
	return size_;
}

const char* RecoderResult::Data() const {
	return data_;
}

char* RecoderResult::Data() {
	return data_;
}

} // namespace Recode
