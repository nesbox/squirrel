/* see copyright notice in squirrel.h */
#ifdef SQ_UNICODE
#include <wctype.h>
#else
#include <ctype.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

int scisspace(int c)
{
#ifdef SQ_UNICODE
	return iswspace(c);
#else
	return isspace(c < 0 ? c + 256 : c);
#endif
}

int scisdigit(int c)
{
#ifdef SQ_UNICODE
	return iswdigit(c);
#else
	return isdigit(c < 0 ? c + 256 : c);
#endif
}

int scisprint(int c)
{
#ifdef SQ_UNICODE
	return iswprint(c);
#else
	return isprint(c < 0 ? c + 256 : c);
#endif
}

int scisxdigit(int c)
{
#ifdef SQ_UNICODE
	return iswxdigit(c);
#else
	return isxdigit(c < 0 ? c + 256 : c);
#endif
}

int sciscntrl(int c)
{
#ifdef SQ_UNICODE
	return iswcntrl(c);
#else
	return iscntrl(c < 0 ? c + 256 : c);
#endif
}

int scisalpha(int c)
{
#ifdef SQ_UNICODE
	return iswalpha(c);
#else
	return isalpha(c < 0 ? c + 256 : c);
#endif
}

int scisalnum(int c)
{
#ifdef SQ_UNICODE
	return iswalnum(c);
#else
	return isalnum(c < 0 ? c + 256 : c);
#endif
}

#ifdef __cplusplus
} /*extern "C"*/
#endif