Dependencies
------------
None, other than make, Python, and a working compiler.

Demo
----
tl;dr: `make` then `python demo.py`.

Here we're compiling the C into a shared object (namely `libdemo.so`) which we can load dynamically from Python.
Then, in Python we declare the argument and return types of the C function `add_two_numbers`, and call it from the shared object.
