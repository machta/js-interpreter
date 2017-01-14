#include "valuecontext.h"

using namespace std;

ValueContext::~ValueContext()
{
	for (auto e : map)
	{
		delete e.second;
	}
}

pair<ValueContext*, Value*> ValueContext::namedValue(const string& name)
{
	if (map.find(name) != map.end())
		return make_pair(this, map.at(name));

	if (parent != nullptr)
		return parent->namedValue(name);

	return make_pair(nullptr, nullptr); // TODO: Return undefined instead.
}

void ValueContext::addNamedValue(const string& name, Value* value)
{
	if (map.find(name) != map.end())
		delete map[name];
	map[name] = value;
}
