#ifndef OBJECT_H
#define OBJECT_H

#include "valuecontext.h"

#include <jast/expression.h>

#include <cstring>
#include <string>
#include <unordered_map>
#include <cassert>

class FunctionDeclaration;
class BuiltInFunction;

enum class ObjectType
{
	Object, Function, BuiltIn, Array // TODO: possibly change Undefined to null
};

// TODO: Forbid copying of this class.
class Object
{
	ObjectType type;

public:
	// TODO: Make a union out of these and possibly make them private.
	ValueContext* objectContext;
	FunctionDeclaration* functionDeclaration;
	jast::Expression* functionBody;
	BuiltInFunction* builtInFunction;
	Value* array;
	int arrayLength;
	bool markFlag = false;

	Object(ValueContext* value) : type(ObjectType::Object), objectContext(value) {}
	Object(FunctionDeclaration* value) : type(ObjectType::Function), functionDeclaration(value), functionBody(nullptr) {}
	Object(BuiltInFunction* value) : type(ObjectType::BuiltIn), builtInFunction(value) {}
	Object(Value* array, int n) : type(ObjectType::Array), array(array), arrayLength(n) {}

	~Object();

	Object(const Object&) = delete;
	Object& operator=(const Object&) = delete;

	ObjectType objectType() const { return type; }

	void mark();

private:
};

#endif // OBJECT_H
