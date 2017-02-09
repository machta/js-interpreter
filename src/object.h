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
	std::vector<Value> array;
	bool markFlag = false;

	Object() : type(ObjectType::Array) {}
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
