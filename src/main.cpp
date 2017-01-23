#include "parser.h"
#include "interpreter.h"
#include "memory.h"

#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

namespace
{

string trim(const string &s)
{
   auto wsfront = find_if_not(s.begin(), s.end(), [](int c){ return isspace(c); });
   auto wsback = find_if_not(s.rbegin(), s.rend(), [](int c){ return isspace(c); }).base();
   return wsback <= wsfront ? string() : string(wsfront, wsback);
}

bool parseAndInterpret(const string& line, Parser& p, Interpreter& interpreter)
{
	string errorMessage;
	unique_ptr<grok::parser::Expression> e(p.makeAST(line, &errorMessage));

	if (e != nullptr)
	{
		try
		{
			e->Accept(&interpreter);

			return true;
		}
		catch (runtime_error& re)
		{
			cerr << "Interpreter error: " << re.what() << endl;
		}
	}
	else
	{
		//cerr << "Parser error: " << errorMessage << endl;
	}
	return false;
}

int REPL()
{
	Parser p;
	ValueContext context;
	Memory memory;
	Interpreter interpreter(&context, &memory);

	string line;

	while (1)
	{
		cout << "> ";
		//cout.flush();

		getline(cin, line);
		if (!cin)
			break;

		line = trim(line);
		if (line.empty())
			continue;

		if (parseAndInterpret(line, p, interpreter))
			cout << interpreter.lastStatementValue().print() << endl;
	}

	return 0;
}

int executeScript(const string& filePath)
{
	try
	{
		ifstream file;
		file.exceptions(ifstream::failbit | ifstream::badbit);

		file.open(filePath);
		string code((istreambuf_iterator<char>(file)), (istreambuf_iterator<char>())); // Read the whole file.

		Parser p;
		ValueContext context;
		Memory memory;
		Interpreter interpreter(&context, &memory);

		return parseAndInterpret(code, p, interpreter) ? 0 : 1;
	}
	catch (exception& e)
	{
		cerr << "Failed to execute the file: " << e.what() << endl;
		return 1;
	}

	return 0;
}

} // namespace

int main(int argc, char** argv)
{
	if (argc <= 1)
		return REPL();
	else
		return executeScript(argv[1]);
}
