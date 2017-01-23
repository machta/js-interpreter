#include "memory.h"

#include "object.h"

using namespace std;

Memory::~Memory()
{
	for (Object* e : list)
		delete e;
}

void Memory::registerObject(Object* o)
{
	list.push_front(o);
}

void Memory::sweep()
{
	list.remove_if([](Object* o)
	{
		if (o->markFlag)
		{
			o->markFlag = false;
			return false;
		}
		else
		{
			delete o;
			return true;
		}
	});
}
