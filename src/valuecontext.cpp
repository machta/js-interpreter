#include "valuecontext.h"

#include "object.h"
#include "functiondeclaration.h"
#include "memory.h"

#include <limits>
#include <cmath>
#include <iostream>

using namespace std;

namespace
{

const double NaN = numeric_limits<double>::quiet_NaN();

class Console_log : public BuiltInFunction
{
public:
	Console_log()
	{
		declaration = new FunctionDeclaration("log");
		declaration->arguments.push_back("message");
	}

	virtual Value body(ValueContext* context) override
	{
		Value message = context->namedValue("message").second;
		cout << message.toString() << endl;
		return Value();
	}
};

Value makeConsole(Memory* memory)
{
	ValueContext* context = new ValueContext();
	context->addNamedValue("log", new Object(new Console_log()));

	Object* o = new Object(context);
	memory->registerObject(o);

	return Value(o);
}

class Math_sqrt : public BuiltInFunction
{
public:
	Math_sqrt()
	{
		declaration = new FunctionDeclaration("sqrt");
		declaration->arguments.push_back("n");
	}

	virtual Value body(ValueContext* context) override
	{
		Value n = context->namedValue("n").second;
		return Value(sqrt(n.toNumber()));
	}
};

Value makeMath(Memory* memory)
{
	ValueContext* context = new ValueContext();
	context->addNamedValue("sqrt", new Object(new Math_sqrt()));

	Object* o = new Object(context);
	memory->registerObject(o);

	return Value(o);
}

} // namespace

bool Value::toBoolean()
{
	switch (type)
	{
	case ValueType::Undefined:
		return false;
	case ValueType::Null:
		return false;
	case ValueType::Reference:
		return false;
	case ValueType::Boolean:
		return booleanValue;
	case ValueType::Number:
		return numberValue == 1;
	case ValueType::String:
		return strlen(stringValue) > 0;
	default:
		assert(0); return false;
	}
}

double Value::toNumber()
{
	switch (type)
	{
	case ValueType::Undefined:
		return NaN; // TODO: Check this.
	case ValueType::Null:
		return 0;
	case ValueType::Reference:
		return -1; // TODO: Check this.
	case ValueType::Boolean:
		return booleanValue ? 1 : 0;
	case ValueType::Number:
		return numberValue;
	case ValueType::String:
		double d;
		try
		{
			d = stod(stringValue);
		}
		catch (...)
		{
			d = NaN;
		}
		return d;
	default:
		assert(0); return 0;
	}
}

string Value::toString()
{
	switch (type)
	{
	case ValueType::Undefined:
		return "undefined"; // TODO: Check this.
	case ValueType::Null:
		return "null";
	case ValueType::Reference:
		return ""; // TODO: Check this. return something like nodejs '[object Object]'
	case ValueType::Boolean:
		return booleanValue ? "true" : "false";
	case ValueType::Number:
		double intpart;
		return modf(numberValue, &intpart) == 0.0 ? to_string(static_cast<int>(intpart)) : to_string(numberValue);
	case ValueType::String:
		return stringValue;
	default:
		assert(0); return "";
	}
}

string Value::print()
{
	switch (type)
	{
	case ValueType::Undefined:
		return "undefined";
	case ValueType::Reference: // TODO: Perhaps print object contents recursively.
	case ValueType::Boolean:
	case ValueType::Number:
		return toString();
	case ValueType::String:
		return '\'' + toString() + '\'';
	default:
		assert(0); return "";
	}
}

Value Value::builtInProperty(const string& name)
{
	if (type == ValueType::String)
	{
		if (name == "length")
			return Value(static_cast<int>(strlen(stringValue)));
	}
	else if (type == ValueType::Reference && reference->objectType() == ObjectType::Array)
	{
		if (name == "length")
			return Value(static_cast<int>(reference->array->size()));
	}

	return Value();
}

void Value::mark()
{
	if (type == ValueType::Reference)
		if (reference->markFlag == false)
			reference->mark();
}

void Value::copyString(const char* value, int length)
{
	//assert(stringValue == nullptr);
	stringValue = new char[length + 1];
	memcpy(stringValue, value, length);
	stringValue[length] = 0;
}

void Value::copy(const Value& v)
{
	destroy();
	type = v.valueType();
	switch (type)
	{
	case ValueType::Null:
	case ValueType::Undefined:
		break;
	case ValueType::Reference:
		reference = v.reference;
		break;
	case ValueType::Boolean:
		booleanValue = v.booleanValue;
		break;
	case ValueType::Number:
		numberValue = v.numberValue;
		break;
	case ValueType::String:
		copyString(v.stringValue, strlen(v.stringValue));
		break;
	}
}

pair<ValueContext*, Value> ValueContext::namedValue(const string& name)
{
	assert(name.length() > 0);

	if (map.find(name) != map.end())
		return make_pair(this, map.at(name));

	if (parent != nullptr)
		return parent->namedValue(name);

	return make_pair(nullptr, Value());
}

void ValueContext::addNamedValue(const string& name, const Value& value)
{
	assert(name.length() > 0);

	map[name] = value;
}

void ValueContext::initBuiltIn(Memory* memory)
{
	addNamedValue("console", makeConsole(memory));
	addNamedValue("Math", makeMath(memory));
}
