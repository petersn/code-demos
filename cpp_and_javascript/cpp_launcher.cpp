// Interacting C++ and Javascript.

#include <v8.h>
#include <sys/stat.h>
#include <assert.h>
#include <iostream>

// By default the Javascript side has no ability to access the outside world, so we give it a print function.
v8::Handle<v8::Value> print_function(const v8::Arguments& x) {
	// We get the number of arguments this function was passed.
	int length = x.Length();
	// Then iterate over the arguments, cast them to strings, and print them out.
	for (int ii=0; ii<length; ii++) {
		v8::String::AsciiValue argstr(x[ii]);
		std::cout << *argstr;
		if (ii<length-1)
			std::cout << " ";
	}
	// Print a newline at the end.
	std::cout << std::endl;
	// Finally, return a null back out into Javascript land.
	v8::Local<v8::Value> result;
	return result;
}

// Here's a simple example showing how to extract numerical arguments, and return numbers back into Javascript.
v8::Handle<v8::Value> add_two_numbers(const v8::Arguments& x) {
	// Demand that we have exactly two arguments.
	assert(x.Length() == 2);
	int first_number  = x[0]->Int32Value();
	int second_number = x[1]->Int32Value();
	return v8::Integer::New(first_number + second_number);
}

int main(int argc, char* argv[]) {
	// Print a usage message and exit if we weren't passed one argument.
	if (argc != 2) {
		std::cerr << "Usage: ./cpp_launcher code.js" << std::endl;
		return 1;
	}
	// Stat the input file to get its length.
	struct stat sb;
	if (stat(argv[1], &sb) == -1) {
		std::cerr << "Couldn't stat input file." << std::endl;
		return 1;
	}
	// Read it into a single continuous buffer.
	char* js_source_buffer = new char[sb.st_size];
	FILE* fd = fopen(argv[1], "rb");
	size_t read_bytes = fread(js_source_buffer, 1, sb.st_size, fd);
	if (read_bytes != (size_t)sb.st_size) {
		std::cerr << "Couldn't read the number of bytes we expected from our input file!" << std::endl;
		std::cerr << "Continuing anyway. Maybe some weird race condition happened?" << std::endl;
	}
	fclose(fd);

	// ========== Here begins interfacing with V8 ==========

	// Create a stack-allocated handle scope.
	v8::HandleScope handle_scope;
	// Create a template for the global object and set the built-in global functions.
	v8::Handle<v8::ObjectTemplate> global = v8::ObjectTemplate::New();
	// Assign references to our two functions into this namespace.
	global->Set(v8::String::New("print_function"), v8::FunctionTemplate::New(print_function));
	global->Set(v8::String::New("add_two_numbers"), v8::FunctionTemplate::New(add_two_numbers));
	// Each processor gets its own context so different processors do not affect each other.
	v8::Persistent<v8::Context> context = v8::Context::New(NULL, global);
	// Enter the created context for compiling and running the game script.
	v8::Context::Scope context_scope(context);
	// Create a string containing the Javascript source code.
	v8::Handle<v8::String> source = v8::String::New(js_source_buffer, read_bytes);
	// Compile the source code.
	v8::Handle<v8::Script> script = v8::Script::Compile(source);
	// Run the script to get the result.
	v8::Handle<v8::Value> result = script->Run();
	// Dispose of the persistent context.
	context.Dispose();

	return 0;
}

