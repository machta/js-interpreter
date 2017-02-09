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
* +=, *=, >>=, ...
* this
* new
* throw, try/catch
* switch
* regular expressions
* comma expression, template literal (whatever that is...)
