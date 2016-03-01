
CPPFLAGS=-g -Wall

all: cpp_launcher

cpp_launcher: cpp_launcher.o
	g++ -o $@ $< -lv8

.PHONY: clean
clean:
	rm -f cpp_launcher *.o

