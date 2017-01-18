#include "valuecontext.h"

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
