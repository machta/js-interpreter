#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "valuecontext.h"

#include "parser/astvisitor.h"

#include <iostream>
#include <stack>
#include <cassert>

class Interpreter : public grok::parser::ASTVisitor {
public:
	Interpreter(ValueContext* context)
	{
		contextStack.push(context);
	}

	std::string lastStatementToString()
	{
		return returnValue.toString();
	}
public:
#define DECLARE_VISITOR_METHOD(type) void Visit(grok::parser::type *) override;
AST_NODE_LIST(DECLARE_VISITOR_METHOD)
#undef DECLARE_VISITOR_METHOD

private:
	std::stack<ValueContext*> contextStack;
	Value returnValue;
	std::string returnVarName;
	ValueContext* returnVarContext = nullptr;

	ValueContext& context()
	{
		assert(contextStack.size() > 0);
		return *contextStack.top();
	}
	void contextPush()
	{
		contextStack.push(new ValueContext(&context()));
	}
	void contextPop()
	{
		delete &context();
		contextStack.pop();
	}
};

#endif // INTERPRETER_H
