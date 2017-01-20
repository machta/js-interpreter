#include "valuecontext.h"

#include <limits>

using namespace std;

pair<ValueContext*, Value> ValueContext::namedValue(const string& name)
{
	assert(name.length() > 0);

	if (map.find(name) != map.end())
		return make_pair(this, map.at(name));

	if (parent != nullptr)
		return parent->namedValue(name);

	return make_pair(nullptr, Value()); // TODO: Return undefined instead.
}

void ValueContext::addNamedValue(const string& name, const Value& value)
{
	assert(name.length() > 0);

	map[name] = value;
}

bool Value::toBoolean()
{
	switch (type)
	{
	case ValueType::Reference:
		return false; // TODO: Check this.
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
			d = numeric_limits<double>::quiet_NaN();
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
		return "undefined";
	case ValueType::Reference:
		return ""; // TODO: Check this.
	case ValueType::Boolean:
		return booleanValue ? "true" : "false";
	case ValueType::Number:
		return to_string(numberValue);
	case ValueType::String:
		return stringValue;
	default:
		assert(0); return "";
	}
}

Value Value::builtInProperty(const string& name)
{
	if (name == "length")
	{
		if (type == ValueType::String)
			return Value(static_cast<int>(strlen(stringValue)));
	}

	return Value();
}

void Value::copyString(const char* value, int length)
{
	delete[] stringValue;
	stringValue = new char[length + 1];
	memcpy(stringValue, value, length);
	stringValue[length] = 0;
}

void Value::copy(const Value& v)
{
	type = v.valueType();
	switch (type)
	{
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
