# js-interpreter
A simple JavaScript interpreter for the subject MI-RUN

```
Usage:
  js-interpreter script.js
  
  Execute without arguments to start the REPL.
```

Build instructions:
``` bash
./download-libraries.sh
mkdir build && cd build
cmake ..
make
./unit-test/unit-test
```

Unsupported language features:
* var in a for statement: for(**var** i = 0;;)
* for-loops with "in"
* switch statement
* +=, *=, >>=, ...
* this
* new
* throw, try/catch
* regular expressions
* comma expression, template literal (whatever that is...)
* accessing arrays with negative index
* property access with square brackets
* explicit conversion (cast operator)

