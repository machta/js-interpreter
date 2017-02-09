#include "global.h"

#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "valuecontext.h"

#include "jast/astvisitor.h"

#include <iostream>
#include <vector>
#include <cassert>

class Memory;

class Interpreter : public jast::ASTVisitor
{
public:
	Interpreter(ValueContext* context, Memory* memory) : globalContext(context), memory(memory)
	{
		context->initBuiltIn(memory);
		contextStack.push_back(context);
	}

	Value lastStatementValue()
	{
		return returnValue();
	}

// Declaration of ASTVisitor's virtual methods.
#define DECLARE_VISITOR_METHOD(type) void Visit(jast::type *) override;
AST_NODE_LIST(DECLARE_VISITOR_METHOD)
#undef DECLARE_VISITOR_METHOD

private:
	ValueContext* globalContext;
	Memory* memory;
	std::vector<ValueContext*> contextStack;
	Value tmpValue;
	std::string idName;
	//ValueContext* returnVarContext = nullptr;
	bool returnStatement = false;
	bool breakStatement = false;
	bool continueStatement = false;
	std::vector<Value>* assignArray = nullptr;
	int assignArrayIndex;
	ValueContext* assignMemberContext = nullptr;
	ValueContext* functionContext = nullptr;

	ValueContext& context()
	{
		assert(contextStack.size() > 0);
		return *contextStack.back();
	}
//	void contextPush()
//	{
//		contextPush(new ValueContext(&context()));
//	}
	void contextPush(ValueContext* context)
	{
		assert(context != nullptr);
		contextStack.push_back(context);
	}
	void contextPop(bool deleteElement)
	{
		assert(contextStack.size() > 0);
		if (deleteElement)
			delete &context();
		contextStack.pop_back();
	}
	Value returnValue()
	{
		if (idName.size() > 0)
		{
			if (assignMemberContext)
			{
				auto tmp = assignMemberContext->namedValue(idName).second;
				//assignMemberContext = nullptr;
				return tmp;
			}
			return context().namedValue(idName).second;
		}
		return tmpValue;
	}
	Value& temporaryValue()
	{
		idName.clear();
		assignMemberContext = nullptr;
		return tmpValue;
	}
	void markAndSweep();
};

#endif // INTERPRETER_H
