#ifndef VALUECONTEXT_H
#define VALUECONTEXT_H

#include <string>
#include <unordered_map>

enum class ValueType
{
	Reference, Boolean, Number, String
};

// TODO: Possibly change this into an union.
class Value
{
	ValueType type;

public:
	Value(ValueType type) : type(type)
	{}
	virtual ~Value()
	{}

	ValueType getType()
	{
		return type;
	}

	//toReference() = 0;
	virtual bool toBoolean() = 0;
	virtual double toNumber() = 0;
	virtual std::string toString() = 0;
};

/*class ReferenceValue : public Value
{
	//...

public:
	ReferenceValue() : Value(ValueType::Reference)
	{}
};*/

class BooleanValue : public Value
{
public:
	bool value;

	BooleanValue(bool value) : Value(ValueType::Boolean), value(value)
	{}

	virtual bool toBoolean() override
	{
		return value;
	}
	virtual double toNumber() override
	{
		return value ? 1 : 0;
	}
	virtual std::string toString() override
	{
		return value ? "true" : "false";
	}
};

class NumberValue : public Value
{
public:
	double value;

	NumberValue(double value) : Value(ValueType::Number), value(value)
	{}

	virtual bool toBoolean() override
	{
		return value == 1;
	}
	virtual double toNumber() override
	{
		return value;
	}
	virtual std::string toString() override
	{
		return std::to_string(value);
	}
};

class StringValue : public Value
{
public:
	std::string value;

	StringValue(const std::string& value) : Value(ValueType::String), value(value)
	{}

	virtual bool toBoolean() override
	{
		return value.size() > 0;
	}
	virtual double toNumber() override
	{
		double d;
		try
		{
			d = stod(value);
		}
		catch (...)
		{
			d = 0; // TODO: Fix this according to reference.
		}
		return d;
	}
	virtual std::string toString() override
	{
		return value;
	}
};

class ValueContext
{
	ValueContext* parent;
	std::unordered_map<std::string, Value*> map;

public:
	ValueContext(ValueContext* parent = nullptr) : parent(parent)
	{}
	~ValueContext();

	std::pair<ValueContext*, Value*> namedValue(const std::string& name);
	void addNamedValue(const std::string& name, Value* value);
};

#endif // VALUECONTEXT_H
