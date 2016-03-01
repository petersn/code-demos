
CPPFLAGS=-g -Wall

all: libdemo.so

libdemo.so: demo.o
	$(CXX) -shared -Wl,-soname,$@ -o $@ $<

clean:
	rm -f demo.o libdemo.so

.PHONY: all clean

