#include "interpreter.h"

#include <cmath>

using namespace std;
using namespace grok::parser;

#define UNDEFINED nullptr

#define NOT_SUPPORTED throw runtime_error("not supported")

void Interpreter::Visit(NullLiteral *literal)
{
	NOT_SUPPORTED;
//	os() << "null";
}

void Interpreter::Visit(UndefinedLiteral *literal)
{
	NOT_SUPPORTED;
//	os() << "undefined";
}

void Interpreter::Visit(ThisHolder *holder)
{
	NOT_SUPPORTED;
//	os() << "this";
}

void Interpreter::Visit(IntegralLiteral *literal)
{
	returnValue(new NumberValue(literal->value()));
//	os() << literal->value();
}

void Interpreter::Visit(StringLiteral *literal)
{
	returnValue(literal->string());
//	os() << literal->string();
}

void Interpreter::Visit(ArrayLiteral *literal)
{
	NOT_SUPPORTED;
//	ProxyArray &arr = literal->exprs();

//	os() << "[ ";
//	for (auto &expr : arr) {
//		expr->Accept(this);
//		os() << ", ";
//	}
//	os() << "]";
}

void Interpreter::Visit(ObjectLiteral *literal)
{
	NOT_SUPPORTED;
//	ProxyObject &obj = literal->proxy();

//	os() << "{ ";
//	for (auto &p : obj) {
//		os() << '\'' << p.first << "': ";
//		p.second->Accept(this);
//		os() << ", ";
//	}
//	os() << "}";
}

void Interpreter::Visit(Identifier *id)
{
	auto var = context().namedValue(id->GetName());
	returnValue(var.second); // TODO: Handle undefined names.
	returnVarName = id->GetName();
	returnVarContext = var.first;

//	os() << id->GetName();
}

void Interpreter::Visit(BooleanLiteral *literal)
{
	returnValue(literal->pred());
//	os() << std::boolalpha << literal->pred();
}

void Interpreter::Visit(RegExpLiteral *reg)
{
	NOT_SUPPORTED; // I could use regex but it's too much work... :)
//	os() << '/' << '/';
}

void Interpreter::Visit(ArgumentList *args)
{
	NOT_SUPPORTED;
//	auto list = args->args();
//	os() << "(";
//	if (!list) {
//		os() << ")";
//		return;
//	}

//	auto b = list->begin();
//	auto e = list->end() - 1;

//	for (; b != e; ++b) {
//		(*b)->Accept(this);
//		os() << ", ";
//	}
//	(*e)->Accept(this);
//	os() << ")";
}

void Interpreter::Visit(CallExpression *expr)
{
	NOT_SUPPORTED;
//	expr->expr()->Accept(this);

//	switch (expr->kind()) {
//	case MemberAccessKind::kCall:
//		expr->member()->Accept(this);
//		break;
//	case MemberAccessKind::kDot:
//		os() << ".";
//		expr->member()->Accept(this);
//		break;
//	case MemberAccessKind::kIndex:
//		os() << "[";
//		expr->member()->Accept(this);
//		os() << "]";
//		break;
//	default:
//		throw std::runtime_error("");
//	}
}

void Interpreter::Visit(MemberExpression *expr)
{
	NOT_SUPPORTED;
//	expr->expr()->Accept(this);

//	switch (expr->kind()) {
//	case MemberAccessKind::kCall:
//		expr->member()->Accept(this);
//		break;
//	case MemberAccessKind::kDot:
//		os() << ".";
//		expr->member()->Accept(this);
//		break;
//	case MemberAccessKind::kIndex:
//		os() << "[";
//		expr->member()->Accept(this);
//		os() << "]";
//		break;
//	default:
//		throw std::runtime_error("");
//	}
}

void Interpreter::Visit(NewExpression *expr)
{
	NOT_SUPPORTED;
//	os() << "new ";
//	expr->member()->Accept(this);
}

void Interpreter::Visit(PrefixExpression *expr)
{
	expr->expr()->Accept(this);
	Value* val = returnValue();
	string varName = returnVarName;
	returnVarName = "";
	ValueContext* varContext = returnVarContext;
	assert(varContext != nullptr);

	switch (expr->op()) {
	case PrefixOperation::kIncrement:
	{
		double d = val->toNumber() + 1;
		varContext->addNamedValue(varName, new NumberValue(d));
		returnValue(d);
		return;
	}
	case PrefixOperation::kDecrement:
	{
		double d = val->toNumber() - 1;
		varContext->addNamedValue(varName, new NumberValue(d));
		returnValue(d);
		return;
	}
//	case PrefixOperation::kTypeOf:
//		os() << "typeof ";
//		break;
//	case PrefixOperation::kDelete:
//		os() << "delete ";
//		break;
	case PrefixOperation::kBitNot:
	{
		int i = ~static_cast<int>(val->toNumber());
		varContext->addNamedValue(varName, new NumberValue(i));
		returnValue(i);
		return;
	}
	case PrefixOperation::kNot:
	{
		double b = ~val->toBoolean();
		varContext->addNamedValue(varName, new BooleanValue(b));
		returnValue(b);
		return;
	}
//	case PrefixOperation::kVoid:
//		os() << "void ";
//		break;
	}

	throw runtime_error("invalid prefix operator");

//	switch (expr->op()) {
//	case PrefixOperation::kIncrement:
//		os() << "++";
//		break;
//	case PrefixOperation::kDecrement:
//		os() << "--";
//		break;
//	case PrefixOperation::kTypeOf:
//		os() << "typeof ";
//		break;
//	case PrefixOperation::kDelete:
//		os() << "delete ";
//		break;
//	case PrefixOperation::kBitNot:
//		os() << "~";
//		break;
//	case PrefixOperation::kNot:
//		os() << "!";
//		break;
//	case PrefixOperation::kVoid:
//		os() << "void ";
//		break;
//	default:
//		throw std::runtime_error("invalid prefix operator");
//	}
//	expr->expr()->Accept(this);
}

void Interpreter::Visit(PostfixExpression *expr)
{
	expr->expr()->Accept(this);
	Value* val = returnValue();
	string name = returnVarName;
	returnVarName = "";
	ValueContext* varContext = returnVarContext;
	assert(varContext != nullptr);
	double d = val->toNumber();

	switch (expr->op()) {
	case PostfixOperation::kIncrement:
		varContext->addNamedValue(name, new NumberValue(d + 1));
		returnValue(d);
		return;
	case PostfixOperation::kDecrement:
		varContext->addNamedValue(name, new NumberValue(d - 1));
		returnValue(d);
		return;
	}

	throw runtime_error("invalid prefix operator");

//	expr->expr()->Accept(this);
//	switch (expr->op()) {
//	case PostfixOperation::kIncrement:
//		os() << "++";
//		break;
//	case PostfixOperation::kDecrement:
//		os() << "--";
//		break;
//	default:
//		throw std::runtime_error("invalid postfix operator");
//	}
}

void Interpreter::Visit(BinaryExpression *expr)
{
	expr->lhs()->Accept(this);
	Value* lhs = returnValue();
	ValueType lhsType = lhs->getType();

	expr->rhs()->Accept(this);
	Value* rhs = returnValue();
	ValueType rhsType = rhs->getType();

	if (lhsType == ValueType::String || rhsType == ValueType::String)
	{
		if (expr->op() == BinaryOperation::kAddition)
		{
			returnValue(lhs->toString() + rhs->toString());
		}
		else
		{
			throw runtime_error("invalid binary operation");
		}

		return;
	}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wswitch"

	//double l = dynamic_cast<NumberValue*>(lhs)->value;
	//double r = dynamic_cast<NumberValue*>(rhs)->value;
	double l = lhs->toNumber();
	double r = rhs->toNumber();
	int li = l, ri = r;

	switch (expr->op()) {
	case BinaryOperation::kAddition:
		returnValue(l + r); return;
	case BinaryOperation::kMultiplication:
		returnValue(l * r); return;
	case BinaryOperation::kSubtraction:
		returnValue(l - r); return;
	case BinaryOperation::kDivision:
		returnValue(l / r); return;
	case BinaryOperation::kMod:
		returnValue(fmod(l, r)); return;
	case BinaryOperation::kShiftRight:
		returnValue(li >> ri); return;
	case BinaryOperation::kShiftLeft:
		returnValue(li << ri); return;
	case BinaryOperation::kLessThan:
		returnValue(l < r); return;
	case BinaryOperation::kGreaterThan:
		returnValue(l > r); return;
	case BinaryOperation::kLessThanEqual:
		returnValue(l <= r); return;
	case BinaryOperation::kGreaterThanEqual:
		returnValue(l >= r); return;
	case BinaryOperation::kEqual:
		returnValue(l == r); return;
	case BinaryOperation::kNotEqual:
		returnValue(l != r); return;
	case BinaryOperation::kStrictEqual:
		returnValue(l == r && lhs->getType() == rhs->getType()); return;
	case BinaryOperation::kStrictNotEqual:
		returnValue(l != r || lhs->getType() != rhs->getType()); return;
//	case BinaryOperation::kAnd:
//		os() << "&&";
//		break;
//	case BinaryOperation::kOr:
//		os() << "||";
//		break;
	case BinaryOperation::kBitAnd:
		returnValue(li & ri); return;
	case BinaryOperation::kBitOr:
		returnValue(li | ri); return;
	case BinaryOperation::kBitXor:
		returnValue(li ^ ri); return;
//	case BinaryOperation::kInstanceOf:
//		os() << "instanceof";
//		break;
	}

	bool lb = lhs->toBoolean();
	bool rb = rhs->toBoolean();

	switch (expr->op()) {
	case BinaryOperation::kAnd:
		returnValue(lb && rb); return;
	case BinaryOperation::kOr:
		returnValue(lb || rb); return;
	}

#pragma GCC diagnostic pop

	throw runtime_error("invalid binary operation");

//	expr->lhs()->Accept(this);
//	os() << " ";
//	switch (expr->op()) {
//	case BinaryOperation::kAddition:
//		os() << "+";
//		break;
//	case BinaryOperation::kMultiplication:
//		os() << "*";
//		break;
//	case BinaryOperation::kSubtraction:
//		os() << "-";
//		break;
//	case BinaryOperation::kDivision:
//		os() << "/";
//		break;
//	case BinaryOperation::kMod:
//		os() << "%";
//		break;
//	case BinaryOperation::kShiftRight:
//		os() << ">>";
//		break;
//	case BinaryOperation::kShiftLeft:
//		os() << "<<";
//		break;
//	case BinaryOperation::kLessThan:
//		os() << "<";
//		break;
//	case BinaryOperation::kGreaterThan:
//		os() << ">";
//		break;
//	case BinaryOperation::kLessThanEqual:
//		os() << "<=";
//		break;
//	case BinaryOperation::kGreaterThanEqual:
//		os() << ">=";
//		break;
//	case BinaryOperation::kEqual:
//		os() << "==";
//		break;
//	case BinaryOperation::kNotEqual:
//		os() << "!=";
//		break;
//	case BinaryOperation::kStrictEqual:
//		os() << "===";
//		break;
//	case BinaryOperation::kStrictNotEqual:
//		os() << "!==";
//		break;
//	case BinaryOperation::kAnd:
//		os() << "&&";
//		break;
//	case BinaryOperation::kOr:
//		os() << "||";
//		break;
//	case BinaryOperation::kBitAnd:
//		os() << "&";
//		break;
//	case BinaryOperation::kBitOr:
//		os() << "|";
//		break;
//	case BinaryOperation::kBitXor:
//		os() << "^";
//		break;
//	case BinaryOperation::kInstanceOf:
//		os() << "instanceof";
//		break;
//	default: throw std::runtime_error("invalid binary operation");
//	}
//	os() << " ";
//	expr->rhs()->Accept(this);
}

void Interpreter::Visit(AssignExpression *expr)
{
	// TODO: Handle declarations without var (for example in for statements)?

	expr->rhs()->Accept(this);
	Value* rhs = returnValue();

	expr->lhs()->Accept(this);
	if (returnVarContext == nullptr)
	{
		context().addNamedValue(returnVarName, nullptr);
		returnVarContext = &context();
	}

	switch (rhs->getType())
	{
	case ValueType::Boolean:
		returnVarContext->addNamedValue(returnVarName, new BooleanValue(rhs->toBoolean())); return;
	case ValueType::Number:
		returnVarContext->addNamedValue(returnVarName, new NumberValue(rhs->toNumber())); return;
	case ValueType::String:
		returnVarContext->addNamedValue(returnVarName, new StringValue(rhs->toString())); return;
	};

	returnVarName = "";
	returnVarContext = nullptr;

//	expr->lhs()->Accept(this);
//	os() << " = ";
//	expr->rhs()->Accept(this);
}

void Interpreter::Visit(TernaryExpression *expr)
{
	NOT_SUPPORTED;
//	expr->first()->Accept(this);
//	os() << " ? ";
//	expr->second()->Accept(this);
//	os() << " : ";
//	expr->third()->Accept(this);
}

void Interpreter::Visit(CommaExpression *expr)
{
	NOT_SUPPORTED;
//	auto exprs = expr->exprs();
//	if (!exprs->Size())
//		return;
//	auto b = exprs->begin();
//	auto e = exprs->end() - 1;

//	for (; b != e; ++b) {
//		(*b)->Accept(this);
//		os() << ", ";
//	}

//	(*e)->Accept(this);
}

void Interpreter::Visit(Declaration *decl)
{
	if (decl->expr())
	{
		decl->expr()->Accept(this);
		context().addNamedValue(decl->name(), returnValue());
	}
	else
	{
		context().addNamedValue(decl->name(), UNDEFINED);
	}

//	os() << "var " << decl->name();

//	if (decl->expr()) {
//		os() << " = ";
//		decl->expr()->Accept(this);
//	}
//	os() << ";\n";
}

void Interpreter::Visit(DeclarationList *decl_list)
{
	auto &list = decl_list->exprs();

	for (auto& decl : list)
	{
		decl->Accept(this);
	}
}

void Interpreter::Visit(BlockStatement *stmt)
{
	auto list = stmt->statements();
	contextStack.push(new ValueContext(&context()));

	for (auto &expr : *list)
	{
		expr->Accept(this);
	}

	contextPop();

//	auto list = stmt->statements();

//	os() << " {\n";
//	tab()++;
//	for (auto &expr : *list) {
//		expr->Accept(this);
//		os() << ";\n";
//	}
//	tab()--;
//	os() << " }\n";
}

void Interpreter::Visit(ForStatement *stmt)
{
	// TODO: check in for loops with "in".
	// TODO: hande break and continue
	if (stmt->init())
	{
		contextStack.push(new ValueContext(&context()));
		stmt->init()->Accept(this);
	}

	bool condition = stmt->condition();
	bool update = stmt->update();

	while (1)
	{
		if (condition)
		{
			stmt->condition()->Accept(this);
			if (returnValue()->toBoolean() == false)
				break;
		}

		stmt->body()->Accept(this);

		if (update)
		{
			stmt->update()->Accept(this);
		}
	}

	if (stmt->init())
	{
		contextPop();
	}

//	os() << "for (";
//	if (stmt->init())
//		stmt->init()->Accept(this);

//	if (stmt->condition()) {
//		if (stmt->kind() == ForKind::kForIn) {
//			os() << " in ";
//		} else {
//			os() << "; ";
//		}
//		stmt->condition()->Accept(this);
//	} else {
//		os() << ";";
//	}

//	if (stmt->update()) {
//		os() << "; ";
//		stmt->update()->Accept(this);
//	} else {
//		os() << ";";
//	}
//	os() << ")\n";
//	stmt->body()->Accept(this);
}

void Interpreter::Visit(WhileStatement *stmt)
{
	while (1)
	{
		stmt->condition()->Accept(this);
		if (returnValue()->toBoolean() == false)
			break;

		stmt->body()->Accept(this);
	}

//	os() << "while (";
//	stmt->condition()->Accept(this);
//	os() << ")";

//	stmt->body()->Accept(this);
//	os() << "\n";
}

void Interpreter::Visit(DoWhileStatement *stmt)
{
	while (1)
	{
		stmt->body()->Accept(this);

		stmt->condition()->Accept(this);
		if (returnValue()->toBoolean() == false)
			break;
	}

//	os() << "do\n";

//	stmt->body()->Accept(this);
//	os() << "while (";
//	stmt->condition()->Accept(this);
//	os() << ");\n";
}

void Interpreter::Visit(BreakStatement *stmt)
{
	NOT_SUPPORTED;

//	os() << "break";
//	if (stmt->label()) {
//		os() << " ";
//		stmt->label()->Accept(this);
//	}
//	os() << ";\n";
}

void Interpreter::Visit(ContinueStatement *stmt)
{
	NOT_SUPPORTED;

//	os() << "continue";
//	if (stmt->label()) {
//		os() << " ";
//		stmt->label()->Accept(this);
//	}
//	os() << ";\n";
}

void Interpreter::Visit(ThrowStatement *stmt)
{
	NOT_SUPPORTED;

//	os() << "throw ";
//	stmt->expr()->Accept(this);
//	os() << ";\n";
}

void Interpreter::Visit(TryCatchStatement *stmt)
{
	NOT_SUPPORTED;

//	os() << "try {\n";
//	stmt->try_block()->Accept(this);
//	os() << "}";
//	if (stmt->catch_expr()) {
//		os() << " catch (" << stmt->catch_expr()->AsIdentifier()->GetName();
//		os() << ") {\n";
//		stmt->catch_block()->Accept(this);
//		os() << "}";
//	}

//	if (stmt->finally()) {
//		os() << " finally {";
//		stmt->finally()->Accept(this);
//		os() << "}\n";
//	}
}

void Interpreter::Visit(LabelledStatement *stmt)
{
	NOT_SUPPORTED;

//	os() << stmt->label() << ":\n";
//	stmt->expr()->Accept(this);
//	os() << "\n";
}

void Interpreter::Visit(CaseClauseStatement *stmt)
{
	NOT_SUPPORTED;

//	os() << "case ";
//	stmt->clause()->Accept(this);
//	os() << ":\n";
//	stmt->stmt()->Accept(this);
//	os() << "\n";
}

void Interpreter::Visit(SwitchStatement *stmt)
{
	NOT_SUPPORTED;

//	os() << "switch (";
//	stmt->expr()->Accept(this);

//	os() << ") {\n";
//	auto list = stmt->clauses();

//	for (auto &clause : *list) {
//		clause->Accept(this);
//	}

//	if (stmt->default_clause()) {
//		os() << "default: ";
//		stmt->default_clause()->Accept(this);
//	}
//	os() << "}\n";
}

void Interpreter::Visit(FunctionPrototype *proto)
{
	NOT_SUPPORTED;

//	os() << "function " << proto->GetName() << "(";

//	std::string out;
//	for (const auto &arg : proto->GetArgs()) {
//		out += arg + ", ";
//	}

//	if (proto->GetArgs().size()) {
//		out.pop_back();
//		out.pop_back();
//		os() << out;
//	}
//	os() << ")";
}

void Interpreter::Visit(FunctionStatement *stmt)
{
	stmt->proto()->Accept(this);
	os() << " {\n";
	stmt->body()->Accept(this);
	os() << "}\n";
}

void Interpreter::Visit(IfStatement *stmt)
{
	stmt->condition()->Accept(this);
	if (returnValue()->toBoolean())
	{
		stmt->body()->Accept(this);
	}

//	os() << "if (";
//	stmt->condition()->Accept(this);
//	os() << ")";
//	stmt->body()->Accept(this);
}

void Interpreter::Visit(IfElseStatement *stmt)
{
	stmt->condition()->Accept(this);
	if (returnValue()->toBoolean())
	{
		stmt->body()->Accept(this);
	}
	else
	{
		stmt->els()->Accept(this);
	}

//	os() << "if (";
//	stmt->condition()->Accept(this);
//	os() << ")";
//	stmt->body()->Accept(this);
//	os() << " else ";
//	stmt->els()->Accept(this);
}

void Interpreter::Visit(ReturnStatement *stmt)
{
	NOT_SUPPORTED;

//	os() << "return ";
//	if (stmt->expr())
//		stmt->expr()->Accept(this);
//	os() << ";\n";
}
