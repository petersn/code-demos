#!/usr/bin/python

# Import ctypes, which is Python's foreign function interface library.
import ctypes

# Load up the shared object.
dll = ctypes.CDLL("./libdemo.so")

# Pull out a handle to the symbol "add_two_numbers" from the shared object.
add_two_numbers = dll.add_two_numbers
# Declare that this function takes in two ints.
add_two_numbers.argtypes = [ctypes.c_int, ctypes.c_int]
# Declare that this function returns an int.
add_two_numbers.restype = ctypes.c_int

# Congradulations, this C function is now callable from Python.
result = add_two_numbers(10, 17)
print "An addition:", result

