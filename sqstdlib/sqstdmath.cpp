/* see copyright notice in squirrel.h */
#include <squirrel.h>
#include <math.h>
#include <stdlib.h>
#include <sqstdmath.h>
#include <random>

#define SINGLE_ARG_FUNC(_funcname) static SQInteger math_##_funcname(HSQUIRRELVM v){ \
    SQFloat f; \
    sq_getfloat(v,2,&f); \
    sq_pushfloat(v,(SQFloat)_funcname(f)); \
    return 1; \
}

#define TWO_ARGS_FUNC(_funcname) static SQInteger math_##_funcname(HSQUIRRELVM v){ \
    SQFloat p1,p2; \
    sq_getfloat(v,2,&p1); \
    sq_getfloat(v,3,&p2); \
    sq_pushfloat(v,(SQFloat)_funcname(p1,p2)); \
    return 1; \
}


static SQRESULT sq_cmp_vargv(HSQUIRRELVM vm, SQInteger size, SQInteger cmp) {
	for (int i = 0; i < size - 1; ++i) {
		SQInteger result = sq_cmp(vm);
		if (result == -2) {
			return SQ_ERROR;
		}

		if (result == cmp) {
			sq_pop(vm, 1);
		}
		else {
			sq_remove(vm, -2);
		}
	}

	return 1;
}

static SQRESULT sq_cmp_array(HSQUIRRELVM vm, SQInteger cmp) {
	if (sq_gettype(vm, 2) != OT_ARRAY) {
		return sq_throwerror(vm, "invalid type tag");
	}

	if (sq_getsize(vm, 2) == 0) {
		return sq_throwerror(vm, "empty array");
	}

	sq_pushnull(vm); // iterator
	sq_next(vm, -2); // fetch first element

	HSQOBJECT value;
	sq_getstackobj(vm, -1, &value);
	sq_pop(vm, 2);

	while (SQ_SUCCEEDED(sq_next(vm, -2))) {
		sq_pushobject(vm, value);

		SQInteger result = sq_cmp(vm);
		if (result == -2) {
			return SQ_ERROR;
		}

		if (result == cmp) {
			// New value
			sq_getstackobj(vm, -2, &value);
		}

		sq_pop(vm, 3);
	}

	sq_pop(vm, 1); // pop iterator
	sq_pushobject(vm, value);

	return 1;
}

static SQRESULT math_min(HSQUIRRELVM vm)
{
	SQInteger top = sq_gettop(vm);
	if (top > 2) {
		return sq_cmp_vargv(vm, top - 1, 1);
	}
	else {
		return sq_cmp_array(vm, 1);
	}
}

static SQRESULT math_max(HSQUIRRELVM vm)
{
	SQInteger top = sq_gettop(vm);
	if (top > 2) {
		return sq_cmp_vargv(vm, top - 1, -1);
	}
	else {
		return sq_cmp_array(vm, -1);
	}
}

static SQRESULT math_clamp(HSQUIRRELVM vm)
{
	switch (sq_gettype(vm, 2))
	{
		case OT_INTEGER:
		{
			SQInteger x;
			sq_getinteger(vm, 2, &x);

			SQInteger min;
			sq_getinteger(vm, 3, &min);

			SQInteger max;
			sq_getinteger(vm, 4, &max);

			if (x < min)
				sq_pushinteger(vm, min);
			else if (x > max)
				sq_pushinteger(vm, max);
			else
				sq_pushinteger(vm, x);

			break;
		}

		case OT_FLOAT:
		{
			SQFloat x;
			sq_getfloat(vm, 2, &x);

			SQFloat min;
			sq_getfloat(vm, 3, &min);

			SQFloat max;
			sq_getfloat(vm, 4, &max);

			if (x < min)
				sq_pushfloat(vm, min);
			else if (x > max)
				sq_pushfloat(vm, max);
			else
				sq_pushfloat(vm, x);

			break;
		}

		default:
		{
			sq_pushnull(vm);
			break;
		}
			
	}

	return 1;
}

static SQRESULT math_round(HSQUIRRELVM vm)
{
	SQInteger top = sq_gettop(vm);
	if (top > 3)
		return sq_throwerror(vm, "wrong number of parameters");

	SQFloat x;
	sq_getfloat(vm, 2, &x);

	SQInteger digits = 0;
	if (top == 3)
		sq_getinteger(vm, 3, &digits);

	float to_int = pow(10.0f, float(digits));
	float result = floor(x * to_int + 0.5f) / to_int;

	sq_pushfloat(vm, result);
	return 1;
}

#ifdef _SQ64
static std::mt19937_64 random_engine;
#else
static std::mt19937 random_engine;
#endif

static SQRESULT math_random(HSQUIRRELVM vm)
{
	SQInteger top = sq_gettop(vm);
	if (top > 3)
		return sq_throwerror(vm, "wrong number of parameters");

	if (top == 1)
	{
		std::uniform_real_distribution<SQFloat> distribution(0.0f, 1.0f);
		sq_pushfloat(vm, distribution(random_engine));

		return 1;
	}

	SQInteger begin;
	sq_getinteger(vm, 2, &begin);

	SQInteger end = begin;
	if (top == 3)
		sq_getinteger(vm, 3, &end);

	if (end < begin)
		return sq_throwerror(vm, "invalid range");

	std::uniform_int_distribution<SQInteger> distribution(begin, end);
	sq_pushinteger(vm, distribution(random_engine));

	return 1;
}

static SQRESULT math_randomseed(HSQUIRRELVM vm)
{
	SQInteger seed;
	sq_getinteger(vm, 2, &seed);

	random_engine.seed(seed);
	return 0;
}

static SQInteger math_srand(HSQUIRRELVM v)
{
    SQInteger i;
    if(SQ_FAILED(sq_getinteger(v,2,&i)))
        return sq_throwerror(v,_SC("invalid param"));
    srand((unsigned int)i);
    return 0;
}

static SQInteger math_rand(HSQUIRRELVM v)
{
    sq_pushinteger(v,rand());
    return 1;
}

static SQInteger math_abs(HSQUIRRELVM v)
{
    SQInteger n;
    sq_getinteger(v,2,&n);
    sq_pushinteger(v,(SQInteger)abs((int)n));
    return 1;
}

SINGLE_ARG_FUNC(sqrt)
SINGLE_ARG_FUNC(fabs)
SINGLE_ARG_FUNC(sin)
SINGLE_ARG_FUNC(cos)
SINGLE_ARG_FUNC(asin)
SINGLE_ARG_FUNC(acos)
SINGLE_ARG_FUNC(log)
SINGLE_ARG_FUNC(log10)
SINGLE_ARG_FUNC(tan)
SINGLE_ARG_FUNC(atan)
TWO_ARGS_FUNC(atan2)
TWO_ARGS_FUNC(pow)
SINGLE_ARG_FUNC(floor)
SINGLE_ARG_FUNC(ceil)
SINGLE_ARG_FUNC(exp)

#define _DECL_FUNC(name,nparams,tycheck) {_SC(#name),math_##name,nparams,tycheck}
static const SQRegFunction mathlib_funcs[] = {
	_DECL_FUNC(min,-2,_SC(".n")),
	_DECL_FUNC(max,-2,_SC(".n")),
	_DECL_FUNC(clamp, 4,_SC(".nnn")),
	_DECL_FUNC(random, -1,_SC(".nn")),
	_DECL_FUNC(randomseed, 2,_SC(".n")),
	_DECL_FUNC(round, -2,_SC(".fi")),
	_DECL_FUNC(sqrt,2,_SC(".n")),
    _DECL_FUNC(sin,2,_SC(".n")),
    _DECL_FUNC(cos,2,_SC(".n")),
    _DECL_FUNC(asin,2,_SC(".n")),
    _DECL_FUNC(acos,2,_SC(".n")),
    _DECL_FUNC(log,2,_SC(".n")),
    _DECL_FUNC(log10,2,_SC(".n")),
    _DECL_FUNC(tan,2,_SC(".n")),
    _DECL_FUNC(atan,2,_SC(".n")),
    _DECL_FUNC(atan2,3,_SC(".nn")),
    _DECL_FUNC(pow,3,_SC(".nn")),
    _DECL_FUNC(floor,2,_SC(".n")),
    _DECL_FUNC(ceil,2,_SC(".n")),
    _DECL_FUNC(exp,2,_SC(".n")),
    _DECL_FUNC(srand,2,_SC(".n")),
    _DECL_FUNC(rand,1,NULL),
    _DECL_FUNC(fabs,2,_SC(".n")),
    _DECL_FUNC(abs,2,_SC(".n")),
    {NULL,(SQFUNCTION)0,0,NULL}
};
#undef _DECL_FUNC

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

SQRESULT sqstd_register_mathlib(HSQUIRRELVM v)
{
    SQInteger i=0;
    while(mathlib_funcs[i].name!=0) {
        sq_pushstring(v,mathlib_funcs[i].name,-1);
        sq_newclosure(v,mathlib_funcs[i].f,0);
        sq_setparamscheck(v,mathlib_funcs[i].nparamscheck,mathlib_funcs[i].typemask);
        sq_setnativeclosurename(v,-1,mathlib_funcs[i].name);
        sq_newslot(v,-3,SQFalse);
        i++;
    }
    sq_pushstring(v,_SC("RAND_MAX"),-1);
    sq_pushinteger(v,RAND_MAX);
    sq_newslot(v,-3,SQFalse);
    sq_pushstring(v,_SC("PI"),-1);
    sq_pushfloat(v,(SQFloat)M_PI);
    sq_newslot(v,-3,SQFalse);
    return SQ_OK;
}
