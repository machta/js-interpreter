#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "valuecontext.h"

#include "parser/astvisitor.h"

#include <iostream>
#include <stack>
#include <cassert>

class Interpreter : public grok::parser::ASTVisitor {
public:
	Interpreter(ValueContext* context) : globalContext(context)
	{
		contextStack.push(context);
	}

	Value lastStatementValue()
	{
		return returnValue;
	}
public:
#define DECLARE_VISITOR_METHOD(type) void Visit(grok::parser::type *) override;
AST_NODE_LIST(DECLARE_VISITOR_METHOD)
#undef DECLARE_VISITOR_METHOD

private:
	ValueContext* globalContext;
	std::stack<ValueContext*> contextStack;
	Value returnValue;
	std::string returnVarName;
	ValueContext* returnVarContext = nullptr;
	bool returnStatement = false;
	bool breakStatement = false;
	bool continueStatement = false;
	Value* assignArray = nullptr;

	ValueContext& context()
	{
		assert(contextStack.size() > 0);
		return *contextStack.top();
	}
	void contextPush()
	{
		contextPush(new ValueContext(&context()));
	}
	void contextPush(ValueContext* context)
	{
		contextStack.push(context);
	}
	void contextPop()
	{
		delete &context();
		contextStack.pop();
	}
};

#endif // INTERPRETER_H
