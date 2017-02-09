#include "global.h"

#ifndef OBJECT_H
#define OBJECT_H

#include "valuecontext.h"

#include <jast/expression.h>

#include <cstring>
#include <string>
#include <unordered_map>
#include <cassert>
#include <vector>

class FunctionDeclaration;
class BuiltInFunction;

enum class ObjectType
{
	Object, Function, BuiltIn, Array
};

// TODO: Forbid copying of this class.
class Object
{
	ObjectType type;

public:
	union
	{
		ValueContext* objectContext;
		FunctionDeclaration* functionDeclaration;
		std::vector<Value>* array;
	};
	union
	{
		jast::Expression* functionBody;
		BuiltInFunction* builtInFunction;
	};

	bool markFlag = false;

	Object() : type(ObjectType::Array), array(new std::vector<Value>()) {}
	Object(ValueContext* value) : type(ObjectType::Object), objectContext(value) {}
	Object(FunctionDeclaration* value) : type(ObjectType::Function), functionDeclaration(value), functionBody(nullptr) {}
	Object(BuiltInFunction* value) : type(ObjectType::BuiltIn), builtInFunction(value) {}

	~Object();

	Object(const Object&) = delete;
	Object& operator=(const Object&) = delete;

	ObjectType objectType() const { return type; }

	void mark();

private:
};

#endif // OBJECT_H
