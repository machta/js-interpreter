#include "parser.h"
#include "interpreter.h"

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

void REPL()
{
	Parser p;
	ValueContext context;

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

		unique_ptr<grok::parser::Expression> e(p.makeAST(line));

		if (e != nullptr)
		{
			try
			{
				Interpreter interpreter(&context);
				e->Accept(&interpreter);

				cout << interpreter.lastStatementValue().print() << endl;
			}
			catch (runtime_error& re)
			{
				cerr << "Execution error: " << re.what() << endl;
			}
		}
		else
		{
			assert(0 && "makAST() failed");
		}
	}
}

} // namespace

// Either execute a script in file argv[1], or launch the REP loop.
int main(int argc, char** argv)
{
	if (argc > 1)
	{
		ifstream file;
		file.exceptions(ifstream::failbit | ifstream::badbit);

		try
		{
			file.open(argv[1]);

			string code((istreambuf_iterator<char>(file)), (istreambuf_iterator<char>()));

			Parser p;
			ValueContext context;

			unique_ptr<grok::parser::Expression> e(p.makeAST(code));

			Interpreter interpreter(&context);
			e->Accept(&interpreter);

			cout << interpreter.lastStatementValue().toString() << endl; // TODO: Remove this after console output is implemented.
			return 0;
		}
		catch (exception& e)
		{
			cerr << "Failed to execute the file: " << e.what() << endl;
			return 1;
		}
	}

	REPL();

	return 0;
}
