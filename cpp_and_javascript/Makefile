
CPPFLAGS=-g -Wall

all: cpp_launcher

cpp_launcher: cpp_launcher.o
	$(CXX) -o $@ $< -lv8

clean:
	rm -f cpp_launcher *.o

.PHONY: clean all

