#ifndef MEMORY_H
#define MEMORY_H_H

#include "valuecontext.h"

#include <forward_list>

class Object;

class Memory
{
	std::forward_list<Object*> list;

public:
	~Memory();

	void registerObject(Object* o);
	void sweep();

	template<class T>
	static void mark(T begin, T end)
	{
		while (begin != end)
		{
			mark(*begin++);
		}
	}
	static void mark(ValueContext* context)
	{
		context->mark();
	}
};

#endif // MEMORY_H
