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
		return returnValueCopy ? returnValueCopy->toString() : "";
	}

protected:
	//*************************************
	std::ostream &os() { return os_; }
	int &tab() { return tab_; }
	bool tabs_or_spaces() { return tab_or_spaces_; }
	//*************************************

public:
#define DECLARE_VISITOR_METHOD(type) void Visit(grok::parser::type *) override;
AST_NODE_LIST(DECLARE_VISITOR_METHOD)
#undef DECLARE_VISITOR_METHOD

private:
	std::stack<ValueContext*> contextStack;
	Value* returnValueCopy = nullptr;
	std::string returnVarName;
	ValueContext* returnVarContext;

	ValueContext& context()
	{
		assert(contextStack.size() > 0);
		return *contextStack.top();
	}

	void contextPop()
	{
		delete &context();
		contextStack.pop();
	}

	void returnValue(Value* v)
	{
		//delete returnValuePointer; // TODO: Fix leak.
		//returnValuePointer = v;

		if (v == nullptr)
		{
			returnValueCopy = nullptr;
			return;
		}

		switch (v->getType())
		{
		case ValueType::Boolean:
			returnValueCopy = new BooleanValue(*dynamic_cast<BooleanValue*>(v)); return;
		case ValueType::Number:
			returnValueCopy = new NumberValue(*dynamic_cast<NumberValue*>(v)); return;
		case ValueType::String:
			returnValueCopy = new StringValue(*dynamic_cast<StringValue*>(v)); return;
		};
	}
	void returnValue(bool b)
	{
		returnValue(new BooleanValue(b));
	}
	void returnValue(double d)
	{
		returnValue(new NumberValue(d));
	}
	void returnValue(int i)
	{
		returnValue(new NumberValue(i));
	}
	void returnValue(const std::string& s)
	{
		returnValue(new StringValue(s));
	}
	Value* returnValue()
	{
		assert(returnValueCopy != nullptr);
		auto tmp = returnValueCopy;
		returnValueCopy = nullptr;
		return tmp;
	}

	//*************************************
	std::ostream &os_ = std::cout;
	int tab_ = 0;
	bool tab_or_spaces_ = false;
	//*************************************
};

#endif // INTERPRETER_H
