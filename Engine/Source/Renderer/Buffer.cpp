#include "Core.h"
#include "Buffer.h"

namespace STL
{
	Buffer::Buffer(void* data, size_t count, uint32 byteWidth)
		: buffer(nullptr), data(data), count(count), byteWidth(byteWidth)
	{
	}

	Buffer::~Buffer()
	{
		SafeRelease(buffer);
	}
}