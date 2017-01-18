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

class Object
{
	ObjectType type;

public:
	// TODO: Make a union out of these and possibly make them private.
	ValueContext* objectContext;
	FunctionProtorype* functionProtorype;
	grok::parser::Expression* functionBody;

	Object(ValueContext* value) : type(ObjectType::Object), objectContext(value) {}
	Object(FunctionProtorype* value) : type(ObjectType::Function), functionProtorype(value) {}

	~Object()
	{
		switch (type)
		{
		case ObjectType::Object:
			delete objectContext;
			return;
		default:
			delete functionProtorype;
			delete functionBody;
			return;
		}
	}

	ObjectType objectType() const { return type; }

private:
};

#endif // OBJECT_H
