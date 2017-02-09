#include "object.h"

#include "memory.h"
#include "functiondeclaration.h"

using namespace std;

Object::~Object()
{
	switch (type)
	{
	case ObjectType::Object:
		delete objectContext;
		return;
	case ObjectType::BuiltIn:
		delete builtInFunction;
	case ObjectType::Function:
		delete functionDeclaration;
		//delete functionBody; // TODO: Make a copy of the body, so that it doesn't get deleted when the AST gets destroyed.
		return;
	case ObjectType::Array:
		return;
	}
}

void Object::mark()
{
	markFlag = true;
	switch (type)
	{
	case ObjectType::Object:
		Memory::mark(objectContext);
		return;
	case ObjectType::BuiltIn:
	case ObjectType::Function:
		return;
	case ObjectType::Array:
		for (unsigned int i = 0; i < array.size(); i++)
			array[i].mark();
		return;
	}
}
