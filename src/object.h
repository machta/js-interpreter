#ifndef OBJECT_H
#define OBJECT_H

#include "valuecontext.h"

#include <parser/expression.h>

#include <cstring>
#include <string>
#include <unordered_map>
#include <cassert>

enum class ObjectType
{
	Object, Function, Array // TODO: possibly change Undefined to null
};

class FunctionProtorype
{
public:
	std::string name;
	std::vector<std::string> arguments;

	FunctionProtorype(const std::string& name) : name(name)
	{}
};

// TODO: Forbid copying of this class.
class Object
{
	ObjectType type;

public:
	// TODO: Make a union out of these and possibly make them private.
	ValueContext* objectContext;
	FunctionProtorype* functionProtorype;
	grok::parser::Expression* functionBody;
	Value* array;
	int arrayLength;
	bool markFlag = false;

	Object(ValueContext* value) : type(ObjectType::Object), objectContext(value) {}
	Object(FunctionProtorype* value) : type(ObjectType::Function), functionProtorype(value) {}
	Object(Value* array, int n) : type(ObjectType::Array), array(array), arrayLength(n) {}

	~Object()
	{
		switch (type)
		{
		case ObjectType::Object:
			delete objectContext;
			return;
		case ObjectType::Function:
			delete functionProtorype;
			//delete functionBody; // TODO: Make a copy of the body, so that it doesn't get deleted when the AST gets destroyed.
			return;
		case ObjectType::Array:
			delete[] array;
			return;
		}
	}

	Object(const Object&) = delete;
	Object& operator=(const Object&) = delete;

	ObjectType objectType() const { return type; }

	void mark();

private:
};

#endif // OBJECT_H
