#ifndef GLOBAL_H
#define GLOBAL_H

#include <cstdlib>
#include <malloc.h>

// This keeps track of how much memory is used by the program
// so that I can know when to sweep the memory heap.

const std::size_t MEMORY_COUNTER_LIMIT = 100*1000*1000;
const std::size_t TOTAL_MEMORY_LIMIT = 10*1000*1000;

extern std::size_t memoryAllocationCounter;
extern std::size_t totalMemoryAllocationSize;

inline void* operator new(std::size_t sz)
{
	memoryAllocationCounter += sz;
	totalMemoryAllocationSize += sz;
	return std::malloc(sz);
}

inline void operator delete(void* ptr) noexcept
{
	totalMemoryAllocationSize -= malloc_usable_size(ptr);
	std::free(ptr);
}

#endif // GLOBAL_H
