#include <emscripten.h>

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include <squirrel.h>
#include <sqstdblob.h>
#include <sqstdsystem.h>
#include <sqstdio.h>
#include <sqstdmath.h>
#include <sqstdstring.h>
#include <sqstdaux.h>

static void js_clear_output()
{
	EM_ASM({
		document.getElementById("output").value = "";
	});
}

static void js_append_output(const char* message)
{
	EM_ASM({
		document.getElementById("output").value += UTF8ToString($0);
		document.getElementById("output").value += "\n";
	}, message);
}

static void sq_printfunc(HSQUIRRELVM vm, const SQChar* s, ...)
{
	va_list args;
	va_start(args, s);

	va_list args_tmp;
	va_copy(args_tmp, args);
	size_t buffer_size = vsnprintf(NULL, 0, s, args_tmp) + 1;
	va_end(args_tmp);

	char* buffer = (char*)sq_malloc(buffer_size);
	vsnprintf(buffer, buffer_size, s, args);
	va_end(args);

	js_append_output(buffer);

	sq_free(buffer, buffer_size);
}

static void sq_errorfunc(HSQUIRRELVM vm, const SQChar* s, ...)
{
	va_list args;
	va_start(args, s);

	va_list args_tmp;
	va_copy(args_tmp, args);
	size_t buffer_size = vsnprintf(NULL, 0, s, args_tmp) + 1;
	va_end(args_tmp);

	char* buffer = (char*)sq_malloc(buffer_size);
	vsnprintf(buffer, buffer_size, s, args);
	va_end(args);

	js_append_output(buffer);

	sq_free(buffer, buffer_size);
}

EMSCRIPTEN_KEEPALIVE
void sq_execute(const char* code)
{
	js_clear_output();

	HSQUIRRELVM vm = sq_open(1024);
	sq_setprintfunc(vm, sq_printfunc, sq_errorfunc);

	sq_pushroottable(vm);

	sqstd_register_bloblib(vm);
	sqstd_register_iolib(vm);
	sqstd_register_systemlib(vm);
	sqstd_register_mathlib(vm);
	sqstd_register_stringlib(vm);

	sqstd_seterrorhandlers(vm);

	if (SQ_SUCCEEDED(sq_compilebuffer(vm, code, strlen(code), "REPL", SQTrue)))
	{
		sq_pushroottable(vm);
		sq_call(vm, 1, SQFalse, SQTrue);
	}

	sq_close(vm);
}