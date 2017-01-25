#include "interpreter.h"

#include "object.h"
#include "memory.h"
#include "builtinfunction.h"

#include <cmath>

using namespace std;
using namespace jast;

namespace
{

#define UNDEFINED Value()

#define NOT_IMPLEMENTED throw runtime_error("feature not implemented")
//#define NOT_SUPPORTED assert(0)

void registerObject(Memory* memory, Object* o)
{
	memory->registerObject(o);
}

} // namespace

void Interpreter::Visit(NullLiteral *literal)
{
	temporaryValue() = Value(ValueType::Null);
//	os() << "null";
}

void Interpreter::Visit(UndefinedLiteral *literal)
{
	temporaryValue() = Value(ValueType::Undefined);
//	os() << "undefined";
}

void Interpreter::Visit(ThisHolder *holder)
{
	NOT_IMPLEMENTED;
//	os() << "this";
}

void Interpreter::Visit(IntegralLiteral *literal)
{
	temporaryValue() = Value(literal->value());
//	os() << literal->value();
}

void Interpreter::Visit(StringLiteral *literal)
{
	// Strip the quotes from the literal first.
	string str = literal->string();
	temporaryValue() = Value(str.c_str(), str.length());

//	os() << "'" << literal->string() << "'";
//	os() << literal->string();
}

void Interpreter::Visit(ArrayLiteral *literal)
{
	ProxyArray &arr = literal->exprs();

	int size = arr.size();
	Value* array = new Value[size];

	for (int i = 0; i < size; i++)
	{
		arr[i]->Accept(this);
		array[i] = returnValue();
	}

	Object* o = new Object(array, size);
	registerObject(memory, o);
	temporaryValue() = Value(o);

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
	ProxyObject &obj = literal->proxy();

	ValueContext* objectContext = new ValueContext();

	for (auto& p : obj)
	{
		p.second->Accept(this);
		objectContext->addNamedValue(p.first, returnValue());
	}

	Object* o = new Object(objectContext);
	registerObject(memory, o);
	temporaryValue() = Value(o);

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
//#ifndef NDEBUG
	temporaryValue() = Value(); // Omitting this causes an error.
//#endif
	idName = id->GetName();

//	os() << id->GetName();
}

void Interpreter::Visit(BooleanLiteral *literal)
{
	temporaryValue() = Value(literal->pred());
//	os() << std::boolalpha << literal->pred();
}

void Interpreter::Visit(RegExpLiteral *reg)
{
	NOT_IMPLEMENTED; // I could use regex but it's too much work... :)
//	os() << '/' << '/';
}

void Interpreter::Visit(ArgumentList *args)
{
	auto list = args->args();

	FunctionDeclaration* fun;
	if (returnValue().reference->objectType() == ObjectType::BuiltIn)
		fun = returnValue().reference->builtInFunction->declaration;
	else
		fun = returnValue().reference->functionDeclaration;

	ValueContext* fc = functionContext;

	if (!list)
	{
		for (unsigned int i = 0; i < fun->arguments.size(); i++)
			fc->addNamedValue(fun->arguments[i], Value());
		return;
	}

	auto it = list->begin();

	for (unsigned int i = 0; i < fun->arguments.size(); i++)
	{
		if (it != list->end())
			(*it)->Accept(this);
		else
			temporaryValue() = Value();

		fc->addNamedValue(fun->arguments[i], returnValue());

		it++;
	}

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
{ // TODO: Find out why this is not needed.
	NOT_IMPLEMENTED;
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
	expr->expr()->Accept(this);
	Value val = returnValue();

	switch (expr->kind())
	{
	case MemberAccessKind::kCall:
	{
		ValueContext* fc = new ValueContext(globalContext);
		functionContext = fc;
		expr->member()->Accept(this);

		contextPush(fc);
		functionContext = nullptr;

		if (val.reference->objectType() == ObjectType::BuiltIn)
			temporaryValue() = val.reference->builtInFunction->body(&context());
		else
			val.reference->functionBody->Accept(this);

		contextPop(true);
		break;
	}
	case MemberAccessKind::kDot:
	{
		expr->member()->Accept(this);

		Value res = val.builtInProperty(idName);
		if (res.valueType() != ValueType::Undefined) // TODO: Possibly change undefined to null.
		{
			temporaryValue() = res;
		}
		else
		{
			auto var = val.reference->objectContext->namedValue(idName);
			string name = idName;
			temporaryValue() = var.second;
			idName = name;
			assignMemberContext = var.first;
		}
		//contextPush();
		//contextPop(false);
		break;
	}
	case MemberAccessKind::kIndex: // TODO: Fix property access with the square brackets.
	{
		expr->member()->Accept(this);
		int index = returnValue().toNumber();
		if (0 <= index && index < val.reference->arrayLength)
		{
			temporaryValue() = val.reference->array[index];
			assignArray = val.reference->array + index;
			//returnVarContext = nullptr;
		}
		else
		{
			throw std::runtime_error("array index out of bounds");
		}
		break;
	}
	default:
		throw std::runtime_error("bad member expression");
	}

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
	NOT_IMPLEMENTED;
//	os() << "new ";
//	expr->member()->Accept(this);
}

// TODO: Add missing prefix unary - operator.
void Interpreter::Visit(PrefixExpression *expr)
{
	expr->expr()->Accept(this);

	switch (expr->op())
	{
	case PrefixOperation::kIncrement:
	{
		auto var = context().namedValue(idName);
		double d = var.second.toNumber() + 1;
		var.first->addNamedValue(idName, Value(d));
		temporaryValue() = Value(d);
		return;
	}
	case PrefixOperation::kDecrement:
	{
		auto var = context().namedValue(idName);
		double d = var.second.toNumber() - 1;
		var.first->addNamedValue(idName, Value(d));
		temporaryValue() = Value(d);
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
		int i = ~static_cast<int>(returnValue().toNumber());
		temporaryValue() = Value(i);
		return;
	}
	case PrefixOperation::kNot:
	{
		bool b = !returnValue().toBoolean();
		temporaryValue() = Value(b);
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
	string name = idName;
	assert(name.length() > 0);
	auto var = context().namedValue(idName);
	idName = "";
	assert(var.first != nullptr);
	double d = var.second.toNumber();

	switch (expr->op())
	{
	case PostfixOperation::kIncrement:
		var.first->addNamedValue(name, Value(d + 1));
		temporaryValue() = Value(d);
		return;
	case PostfixOperation::kDecrement:
		var.first->addNamedValue(name, Value(d - 1));
		temporaryValue() = Value(d);
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
	Value lhs = returnValue();
	ValueType lhsType = lhs.valueType();

	expr->rhs()->Accept(this);
	Value rhs = returnValue();
	ValueType rhsType = rhs.valueType();

	if (lhsType == ValueType::String || rhsType == ValueType::String)
	{
		if (expr->op() == BinaryOperation::kAddition)
		{
			string tmp = lhs.toString() + rhs.toString();
			temporaryValue() = Value(tmp.c_str(), tmp.length());
			return;
		}
	}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wswitch"

	if (lhsType == ValueType::String && rhsType == ValueType::String)
	{
		string l = lhs.toString();
		string r = rhs.toString();

		switch (expr->op())
		{
		case BinaryOperation::kLessThan:
			temporaryValue() = Value(l < r); return;
		case BinaryOperation::kGreaterThan:
			temporaryValue() = Value(l > r); return;
		case BinaryOperation::kLessThanEqual:
			temporaryValue() = Value(l <= r); return;
		case BinaryOperation::kGreaterThanEqual:
			temporaryValue() = Value(l >= r); return;
		case BinaryOperation::kEqual:
			temporaryValue() = Value(l == r); return;
		case BinaryOperation::kNotEqual:
			temporaryValue() = Value(l != r); return;
//		case BinaryOperation::kStrictEqual:
//			temporaryValue() = Value(l == r && lhs.valueType() == rhs.valueType()); return;
//		case BinaryOperation::kStrictNotEqual:
//			temporaryValue() = Value(l != r || lhs.valueType() != rhs.valueType()); return;
		}
	}

	double l = lhs.toNumber();
	double r = rhs.toNumber();
	int li = l, ri = r;

	switch (expr->op())
	{
	case BinaryOperation::kAddition:
		temporaryValue() = Value(l + r); return;
	case BinaryOperation::kMultiplication:
		temporaryValue() = Value(l * r); return;
	case BinaryOperation::kSubtraction:
		temporaryValue() = Value(l - r); return;
	case BinaryOperation::kDivision:
		temporaryValue() = Value(l / r); return;
	case BinaryOperation::kMod:
		temporaryValue() = Value(fmod(l, r)); return;
	case BinaryOperation::kShiftRight:
		temporaryValue() = Value(li >> ri); return;
	case BinaryOperation::kShiftZeroRight:
		temporaryValue() = Value(static_cast<int>(static_cast<unsigned int>(li) >> ri)); return;
	case BinaryOperation::kShiftLeft:
		temporaryValue() = Value(li << ri); return;
	case BinaryOperation::kLessThan:
		temporaryValue() = Value(l < r); return;
	case BinaryOperation::kGreaterThan:
		temporaryValue() = Value(l > r); return;
	case BinaryOperation::kLessThanEqual:
		temporaryValue() = Value(l <= r); return;
	case BinaryOperation::kGreaterThanEqual:
		temporaryValue() = Value(l >= r); return;
	case BinaryOperation::kEqual:
		temporaryValue() = Value(l == r); return;
	case BinaryOperation::kNotEqual:
		temporaryValue() = Value(l != r); return;
	case BinaryOperation::kStrictEqual:
		temporaryValue() = Value(l == r && lhs.valueType() == rhs.valueType()); return;
	case BinaryOperation::kStrictNotEqual:
		temporaryValue() = Value(l != r || lhs.valueType() != rhs.valueType()); return;
//	case BinaryOperation::kAnd:
//		os() << "&&";
//		break;
//	case BinaryOperation::kOr:
//		os() << "||";
//		break;
	case BinaryOperation::kBitAnd:
		temporaryValue() = Value(li & ri); return;
	case BinaryOperation::kBitOr:
		temporaryValue() = Value(li | ri); return;
	case BinaryOperation::kBitXor:
		temporaryValue() = Value(li ^ ri); return;
//	case BinaryOperation::kInstanceOf:
//		os() << "instanceof";
//		break;
	}

	bool lb = lhs.toBoolean();
	bool rb = rhs.toBoolean();

	switch (expr->op())
	{
	case BinaryOperation::kAnd:
		temporaryValue() = Value(lb && rb); return;
	case BinaryOperation::kOr:
		temporaryValue() = Value(lb || rb); return;
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

// TODO: Implement += and similar assignments.
void Interpreter::Visit(AssignExpression *expr)
{
	expr->rhs()->Accept(this);
	Value rhs = returnValue();
	if (assignArray)
		assignArray = nullptr;

	expr->lhs()->Accept(this);

	if (assignMemberContext)
	{
		assignMemberContext->addNamedValue(idName, rhs);
	}
	else
	{
		if (assignArray != nullptr)
		{
			*assignArray = rhs;
		}
		else
		{
			auto var = context().namedValue(idName);

			if (var.first == nullptr)
			{
				context().addNamedValue(idName, rhs);
			}
			else
			{
				var.first->addNamedValue(idName, rhs);
			}
		}
	}

	//returnVarContext = nullptr;
	assignArray = nullptr;
	assignMemberContext = nullptr;

//	expr->lhs()->Accept(this);
//	os() << " = ";
//	expr->rhs()->Accept(this);
}

void Interpreter::Visit(TernaryExpression *expr)
{
	expr->first()->Accept(this);
	if (returnValue().toBoolean())
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
	NOT_IMPLEMENTED;
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

		if (assignArray)
			assignArray = nullptr;
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
	assert (contextStack.size() > 0);

	for (auto &expr : *list)
	{
		// Mark & Sweep
		// TODO: Move this where it makes more sense.
		Memory::mark(contextStack.begin(), contextStack.end());
		memory->sweep();

		expr->Accept(this);

		if (returnStatement)
		{
			returnStatement = false;
			break;
		}
		if (breakStatement || continueStatement)
			break;
	}

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
		//contextPush(); // TODO: Maybe turn this back on to support "var i = 0" with local scope
		stmt->init()->Accept(this);
	}

	bool condition = stmt->condition();
	bool update = stmt->update();

	while (1)
	{
		if (condition)
		{
			stmt->condition()->Accept(this);
			if (returnValue().toBoolean() == false)
				break;
		}

		stmt->body()->Accept(this);

		if (breakStatement)
		{
			breakStatement = false;
			break;
		}
		if (continueStatement)
			continueStatement = false;

		if (update)
		{
			stmt->update()->Accept(this);
		}
	}

	if (stmt->init())
	{
		//contextPop();
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
		if (returnValue().toBoolean() == false)
			break;

		stmt->body()->Accept(this);

		if (breakStatement)
		{
			breakStatement = false;
			break;
		}
		if (continueStatement)
			continueStatement = false;
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
		if (returnValue().toBoolean() == false)
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
	breakStatement = true;

//	os() << "break";
//	if (stmt->label()) {
//		os() << " ";
//		stmt->label()->Accept(this);
//	}
//	os() << ";\n";
}

void Interpreter::Visit(ContinueStatement *stmt)
{
	continueStatement = true;

//	os() << "continue";
//	if (stmt->label()) {
//		os() << " ";
//		stmt->label()->Accept(this);
//	}
//	os() << ";\n";
}

void Interpreter::Visit(ThrowStatement *stmt)
{
	NOT_IMPLEMENTED;

//	os() << "throw ";
//	stmt->expr()->Accept(this);
//	os() << ";\n";
}

void Interpreter::Visit(TryCatchStatement *stmt)
{
	NOT_IMPLEMENTED;

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
	NOT_IMPLEMENTED;

//	os() << stmt->label() << ":\n";
//	stmt->expr()->Accept(this);
//	os() << "\n";
}

void Interpreter::Visit(CaseClauseStatement *stmt)
{
	NOT_IMPLEMENTED;

//	os() << "case ";
//	stmt->clause()->Accept(this);
//	os() << ":\n";
//	stmt->stmt()->Accept(this);
//	os() << "\n";
}

void Interpreter::Visit(SwitchStatement *stmt)
{
	NOT_IMPLEMENTED;

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
	FunctionDeclaration* fun = new FunctionDeclaration(proto->GetName());

	for (const auto& arg : proto->GetArgs())
	{
		fun->arguments.push_back(arg);
	}

	Object* o = new Object(fun);
	registerObject(memory, o);
	temporaryValue() = Value(o);

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
	returnValue().reference->functionBody = stmt->body();

//	stmt->proto()->Accept(this);
//	os() << " {\n";
//	stmt->body()->Accept(this);
//	os() << "}\n";
}

void Interpreter::Visit(IfStatement *stmt)
{
	stmt->condition()->Accept(this);
	if (returnValue().toBoolean())
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
	if (returnValue().toBoolean())
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
	if (stmt->expr())
		stmt->expr()->Accept(this);

	tmpValue = returnValue();
	idName.clear();

	returnStatement = true;

//	os() << "return ";
//	if (stmt->expr())
//		stmt->expr()->Accept(this);
//	os() << ";\n";
}

void Interpreter::Visit(TemplateLiteral*)
{
	NOT_IMPLEMENTED;
}
