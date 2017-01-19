#ifndef VALUECONTEXT_H
#define VALUECONTEXT_H

#include <cstring>
#include <string>
#include <unordered_map>
#include <cassert>

class Object;

enum class ValueType
{
	Undefined, Reference, Boolean, Number, String // TODO: possibly change Undefined to null
};

class Value
{
	ValueType type;

public:
	// TODO: Make a union out of these and possibly make them private.
	Object* reference;
	bool booleanValue;
	double numberValue;
	char* stringValue = nullptr;

	Value() : type(ValueType::Undefined) {}
	//Value(ValueType type) : type(type) {}
	Value(Object* value) : type(ValueType::Reference), reference(value) {}
	Value(bool value) : type(ValueType::Boolean), booleanValue(value) {}
	Value(double value) : type(ValueType::Number), numberValue(value) {}
	Value(int value) : type(ValueType::Number), numberValue(value) {}
	Value(const char* value, int length) : type(ValueType::String)
	{
		copyString(value, length);
	}

	~Value()
	{
		if (type == ValueType::String)
		{
			delete[] stringValue;
			stringValue = nullptr;
		}
	}

	Value(const Value& v)
	{
		copy(v);
	}
	Value& operator=(const Value& v)
	{
		copy(v);
		return *this;
	}

	ValueType valueType() const { return type; }

	//toReference(){}
	bool toBoolean();
	double toNumber();
	std::string toString();

	Value builtInProperty(const std::string& name);

private:
	void copyString(const char* value, int length)
	{
		delete[] stringValue;
		stringValue = new char[length + 1];
		memcpy(stringValue, value, length);
		stringValue[length] = 0;
	}
	void copy(const Value& v)
	{
		type = v.valueType();
		switch (type)
		{
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
};

class ValueContext
{
	ValueContext* parent;
	std::unordered_map<std::string, Value> map;

public:
	ValueContext(ValueContext* parent = nullptr) : parent(parent)
	{}
	~ValueContext()
	{}

	std::pair<ValueContext*, Value> namedValue(const std::string& name); // TODO: make this const
	void addNamedValue(const std::string& name, const Value& value);
};

#endif // VALUECONTEXT_H
