#include "interpreter.h"

#include <cmath>

using namespace std;
using namespace grok::parser;

#define UNDEFINED Value()

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
	returnValue = Value(literal->value());
//	os() << literal->value();
}

void Interpreter::Visit(StringLiteral *literal)
{
	returnValue = Value(literal->string().c_str(), literal->string().length());
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
	auto var = context().namedValue(id->GetName()); // TODO: Handle undefined names.
	returnValue = var.second;
	returnVarName = id->GetName();
	returnVarContext = var.first;

//	os() << id->GetName();
}

void Interpreter::Visit(BooleanLiteral *literal)
{
	returnValue = Value(literal->pred());
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
	string varName = returnVarName;
	returnVarName = "";
	ValueContext* varContext = returnVarContext;
	assert(varContext != nullptr);

	switch (expr->op()) {
	case PrefixOperation::kIncrement:
	{
		double d = returnValue.toNumber() + 1;
		varContext->addNamedValue(varName, Value(d));
		returnValue = Value(d);
		return;
	}
	case PrefixOperation::kDecrement:
	{
		double d = returnValue.toNumber() - 1;
		varContext->addNamedValue(varName, Value(d));
		returnValue = Value(d);
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
		int i = ~static_cast<int>(returnValue.toNumber());
		varContext->addNamedValue(varName, Value(i));
		returnValue = Value(i);
		return;
	}
	case PrefixOperation::kNot:
	{
		double b = ~returnValue.toBoolean();
		varContext->addNamedValue(varName, Value(b));
		returnValue = Value(b);
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
	string name = returnVarName;
	returnVarName = "";
	ValueContext* varContext = returnVarContext;
	assert(varContext != nullptr);
	double d = returnValue.toNumber();

	switch (expr->op()) {
	case PostfixOperation::kIncrement:
		varContext->addNamedValue(name, Value(d + 1));
		returnValue = Value(d);
		return;
	case PostfixOperation::kDecrement:
		varContext->addNamedValue(name, Value(d - 1));
		returnValue = Value(d);
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
	Value lhs = returnValue;
	ValueType lhsType = lhs.valueType();

	expr->rhs()->Accept(this);
	Value rhs = returnValue;
	ValueType rhsType = rhs.valueType();

	if (lhsType == ValueType::String || rhsType == ValueType::String)
	{
		if (expr->op() == BinaryOperation::kAddition)
		{
			string tmp = lhs.toString() + rhs.toString();
			returnValue = Value(tmp.c_str(), tmp.length());
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
	double l = lhs.toNumber();
	double r = rhs.toNumber();
	int li = l, ri = r;

	switch (expr->op()) {
	case BinaryOperation::kAddition:
		returnValue = Value(l + r); return;
	case BinaryOperation::kMultiplication:
		returnValue = Value(l * r); return;
	case BinaryOperation::kSubtraction:
		returnValue = Value(l - r); return;
	case BinaryOperation::kDivision:
		returnValue = Value(l / r); return;
	case BinaryOperation::kMod:
		returnValue = Value(fmod(l, r)); return;
	case BinaryOperation::kShiftRight:
		returnValue = Value(li >> ri); return;
	case BinaryOperation::kShiftLeft:
		returnValue = Value(li << ri); return;
	case BinaryOperation::kLessThan:
		returnValue = Value(l < r); return;
	case BinaryOperation::kGreaterThan:
		returnValue = Value(l > r); return;
	case BinaryOperation::kLessThanEqual:
		returnValue = Value(l <= r); return;
	case BinaryOperation::kGreaterThanEqual:
		returnValue = Value(l >= r); return;
	case BinaryOperation::kEqual:
		returnValue = Value(l == r); return;
	case BinaryOperation::kNotEqual:
		returnValue = Value(l != r); return;
	case BinaryOperation::kStrictEqual:
		returnValue = Value(l == r && lhs.valueType() == rhs.valueType()); return;
	case BinaryOperation::kStrictNotEqual:
		returnValue = Value(l != r || lhs.valueType() != rhs.valueType()); return;
//	case BinaryOperation::kAnd:
//		os() << "&&";
//		break;
//	case BinaryOperation::kOr:
//		os() << "||";
//		break;
	case BinaryOperation::kBitAnd:
		returnValue = Value(li & ri); return;
	case BinaryOperation::kBitOr:
		returnValue = Value(li | ri); return;
	case BinaryOperation::kBitXor:
		returnValue = Value(li ^ ri); return;
//	case BinaryOperation::kInstanceOf:
//		os() << "instanceof";
//		break;
	}

	bool lb = lhs.toBoolean();
	bool rb = rhs.toBoolean();

	switch (expr->op()) {
	case BinaryOperation::kAnd:
		returnValue = Value(lb && rb); return;
	case BinaryOperation::kOr:
		returnValue = Value(lb || rb); return;
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
	Value rhs = returnValue;

	expr->lhs()->Accept(this);
	if (returnVarContext == nullptr)
	{
		context().addNamedValue(returnVarName, Value());
		returnVarContext = &context();
	}

	returnVarContext->addNamedValue(returnVarName, rhs);

	returnVarName = "";
	returnVarContext = nullptr;

//	expr->lhs()->Accept(this);
//	os() << " = ";
//	expr->rhs()->Accept(this);
}

void Interpreter::Visit(TernaryExpression *expr)
{
	expr->first()->Accept(this);
	if (returnValue.toBoolean())
	{
		expr->second()->Accept(this);
	}
	else
	{
		expr->third()->Accept(this);
	}

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
		context().addNamedValue(decl->name(), returnValue);
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

	contextPush();
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
		contextPush();
		stmt->init()->Accept(this);
	}

	bool condition = stmt->condition();
	bool update = stmt->update();

	while (1)
	{
		if (condition)
		{
			stmt->condition()->Accept(this);
			if (returnValue.toBoolean() == false)
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
		if (returnValue.toBoolean() == false)
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
		if (returnValue.toBoolean() == false)
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
	NOT_SUPPORTED;

//	stmt->proto()->Accept(this);
//	os() << " {\n";
//	stmt->body()->Accept(this);
//	os() << "}\n";
}

void Interpreter::Visit(IfStatement *stmt)
{
	stmt->condition()->Accept(this);
	if (returnValue.toBoolean())
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
	if (returnValue.toBoolean())
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
