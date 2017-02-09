#include "global.h"

#ifndef BUILTINFUNCTION_H
#define BUILTINFUNCTION_H

#include "valuecontext.h"

#include <vector>

class FunctionDeclaration
{
public:
	std::string name;
	std::vector<std::string> arguments;

	FunctionDeclaration(const std::string& name) : name(name)
	{}
};

class BuiltInFunction
{
public:
	FunctionDeclaration* declaration;

	BuiltInFunction() = default;
	BuiltInFunction(FunctionDeclaration* declaration) : declaration(declaration)
	{}
	virtual ~BuiltInFunction()
	{
		delete declaration;
	}
	virtual Value body(ValueContext* context) = 0;
};

#endif // BUILTINFUNCTION_H
