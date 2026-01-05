// Source code taken from: https://github.com/mabako/squirrel-compiler

#include <iostream>
#include <squirrel.h>
#include <sqstdio.h>

#ifdef SQUNICODE
#define sccout std::wcout
#define scerr std::wcerr
#else
#define sccout std::cout
#define scerr std::cerr
#endif

#define scendl std::endl

static void compile_error_handler(HSQUIRRELVM v, const SQChar* desc, const SQChar* source, SQInteger line, SQInteger column)
{
	scerr << _SC("Error in ") << source << _SC(" on line ") << line << _SC(" column ") << column << _SC(": ") << desc << scendl;
}

int main(int argc, SQChar** argv)
{
	if (argc < 2) {
		sccout << _SC("Usage: ") << argv[0] << _SC(" [source file] [destination file]") << scendl;
		sccout << _SC("Calling without a destination file will merely do syntax checks.") << scendl;
		return 1;
	}

	// open vm
	HSQUIRRELVM v = sq_open(1024);
	if (!v) {
		sccout << _SC("Error: Could not open Squirrel VM") << scendl;
		return 2;
	}

	// set compile error handler
	sq_setcompilererrorhandler(v, compile_error_handler);

	// compile source file
	if (SQ_FAILED(sqstd_loadfile(v, argv[1], SQTrue))) {
		sccout << _SC("Error: Could not compile source file ") << argv[1] << scendl;
		sq_close(v);
		return 3;
	}

	// only if an output file was passed
	if (argc >= 3)
	{
		// serialize closure containing the source
		if (SQ_FAILED(sqstd_writeclosuretofile(v, argv[2]))) {
			sccout << _SC("Error: Could not serialize closure") << scendl;
		}
	}

	// clean up.
	sq_close(v);
	
	return 0;
}