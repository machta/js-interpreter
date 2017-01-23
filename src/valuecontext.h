#ifndef VALUECONTEXT_H
#define VALUECONTEXT_H

#include <cstring>
#include <string>
#include <unordered_map>
#include <cassert>

class Object;

enum class ValueType
{
	Undefined, Null, Reference, Boolean, Number, String // TODO: possibly change Undefined to null
};

class Value
{
	ValueType type = ValueType::Undefined;

public:
	// TODO: Make a union out of these and possibly make them private.
	Object* reference;
	bool booleanValue;
	double numberValue;
	char* stringValue = nullptr;

	Value(ValueType type = ValueType::Undefined) : type(type) {}
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
		destroy();
	}	
	void destroy()
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
	std::string print();
	Value builtInProperty(const std::string& name);

	void mark();

private:
	void copyString(const char* value, int length);
	void copy(const Value& v);
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
	void mark()
	{
		for (auto& e : map)
			e.second.mark();
	}
};

#endif // VALUECONTEXT_H
