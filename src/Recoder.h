#ifndef ICONV_RECODER_H_
#define ICONV_RECODER_H_

#include <list>

#include <iconv.h>

namespace Recode {

class Chunk;
class Recoder;
class RecoderResult;

class Recoder {
public:
	/**
	 * Create a new Recoder object. The caller is responsible for delete()ing it.
	 */
	static Recoder* New(const char* sourceEncoding, const char* targetEncoding);

	virtual ~Recoder();

	void Reset();

	// TODO support streaming modes
	bool Recode(const void* data, size_t size);

	bool IsError() const;

	int GetErrorNumber() const;

	const char* GetErrorMessage() const;

	RecoderResult GetResult() const;

private:
	static const char* FixEncodingName(const char* name);

	Recoder(iconv_t iv);

private:
	iconv_t iv_;
	size_t size_;
	int errno_;

	std::list<Chunk> chunks_;
};

/**
 * Output of a recoding action. This object does /not/ release
 * the memory it points to, that is the responsibility of the
 * owner, i.e. he who calls Recoder::GetResult().
 */
class RecoderResult {
public:
	size_t Size() const;

	const char* Data() const;

	char* Data();

private:
	friend class Recoder;

	RecoderResult();
	RecoderResult(size_t size, const std::list<Chunk> chunks);

	size_t size_;
	char* data_;
};

// helper class - dumb slice of memory
// FIXME don't leak this implementation detail to client code
struct Chunk {
	size_t size_;
	char data_[32 * 1024];

	Chunk(): size_(0) {
	}
};

} // namespace Recode

#endif // ICONV_RECODER_H_
