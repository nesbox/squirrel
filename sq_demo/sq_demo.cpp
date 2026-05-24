/*  see copyright notice in squirrel.h */

#include <cstdio>
#include <cstdlib>
#include <cstdarg>

#include <vector>
#include <chrono>

#if defined(_MSC_VER) && defined(_DEBUG)
#include <crtdbg.h>
#endif
#include <squirrel.h>
#include <sqstdblob.h>
#include <sqstdsystem.h>
#include <sqstdio.h>
#include <sqstdmath.h>
#include <sqstdstring.h>
#include <sqstdaux.h>

#ifdef SQUNICODE
#define scfprintf fwprintf
#define scvprintf vfwprintf
#else
#define scfprintf fprintf
#define scvprintf vfprintf
#endif

#if defined(_MSC_VER) && defined(_DEBUG)
int MemAllocHook( int allocType, void *userData, size_t size, int blockType,
   long requestNumber, const unsigned char *filename, int lineNumber)
{
    //if(requestNumber==769)_asm int 3;
    return 1;
}
#endif

void printfunc(HSQUIRRELVM SQ_UNUSED_ARG(v),const SQChar *s,...)
{
    va_list vl;
    va_start(vl, s);
    scvprintf(stdout, s, vl);
    va_end(vl);
}

void errorfunc(HSQUIRRELVM SQ_UNUSED_ARG(v),const SQChar *s,...)
{
    va_list vl;
    va_start(vl, s);
    scvprintf(stderr, s, vl);
    va_end(vl);
}

void sq_register_function(HSQUIRRELVM vm, const SQChar* name, SQFUNCTION func, SQInteger nparamscheck, const SQChar* typemask)
{
    sq_pushroottable(vm);
    sq_pushstring(vm, name, -1);
    sq_newclosure(vm, func, 0);
    sq_setnativeclosurename(vm, -1, _SC(name));
    sq_setparamscheck(vm, nparamscheck, typemask);
    sq_createslot(vm, -3);
    sq_pop(vm, 1);
}

struct Timeout
{
    HSQOBJECT callback;
    SQInteger delay;
    SQInteger timestamp;
};

static std::vector<Timeout> timeouts;

static SQInteger GetTickCount()
{
    using namespace std::chrono;

    uint64_t ms =
        duration_cast<milliseconds>(
            steady_clock::now().time_since_epoch()
        ).count();

    return SQInteger(ms);
}

static SQRESULT sq_set_timeout(HSQUIRRELVM vm)
{
    HSQOBJECT callback;
    sq_getstackobj(vm, 2, &callback);
    sq_addref(vm, &callback);

    SQInteger delay;
    sq_getinteger(vm, 3, &delay);

    timeouts.push_back({
        .callback = callback,
        .delay = delay,
        .timestamp = GetTickCount() + delay
    });
    return 0;
}

int main(int argc, char* argv[])
{
    HSQUIRRELVM v;

#if defined(_MSC_VER) && defined(_DEBUG)
    _CrtSetAllocHook(MemAllocHook);
#endif

    v=sq_open(1024);
    sq_setprintfunc(v,printfunc,errorfunc);

    sq_pushroottable(v);

    sqstd_register_bloblib(v);
    sqstd_register_iolib(v);
    sqstd_register_systemlib(v);
    sqstd_register_mathlib(v);
    sqstd_register_stringlib(v);

    //aux library
    //sets error handlers
    sqstd_seterrorhandlers(v);

    sq_register_function(v, "setTimeout", sq_set_timeout, 3, ".cn");

    sqstd_dofile(v, "main.nut", SQFalse, SQTrue);

    while (1)
    {
        const auto now = GetTickCount();

        for (auto& timeout : timeouts)
        {
            if (now < timeout.timestamp)
                continue;

            sq_pushobject(v, timeout.callback);
            sq_pushroottable(v);

            sq_call(v, 1, SQFalse, SQTrue);
            sq_poptop(v);

            timeout.timestamp = GetTickCount() + timeout.delay;
        }
    }

#if defined(_MSC_VER) && defined(_DEBUG)
    _CrtMemDumpAllObjectsSince( NULL );
#endif

    sq_close(v);

    return 0;
}

