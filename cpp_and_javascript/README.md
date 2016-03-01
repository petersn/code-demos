TL;DR
-----
Run: `make` then `./cpp_launcher code.js`.

Dependencies
------------
You'll need V8 installed, such as via `apt-get install libv8-dev`.

This provides a demo of calling Javascript from C++, with the Javascript able to call back into C++.
The file `cpp\_launcher.cpp` compiles into `cpp\_launcher`, which can be run on a Javascript file.
The Javascript is provided with two functions, `print\_function` and `add\_two\_numbers`, and is executed.
In this way you can interface C++ and Javascript.
