#include "object.h"

#include "memory.h"

using namespace std;

void Object::mark()
{
	markFlag = true;
	switch (type)
	{
	case ObjectType::Object:
		Memory::mark(objectContext);
		return;
	case ObjectType::Function:
		return;
	case ObjectType::Array:
		for (int i = 0; i < arrayLength; i++)
			array[i].mark();
		return;
	}
}
