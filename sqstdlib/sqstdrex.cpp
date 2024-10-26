/* see copyright notice in squirrel.h */
#include <squirrel.h>
#include <string.h>
#include <ctype.h>
#include <sqstdstring.h>
#include <string>
#include <regex>

struct SQRex {
    std::regex regex;
    std::cmatch matches;
};

/* public api */
SQRex *sqstd_rex_compile(const SQChar *pattern,const SQChar **error)
{
    SQRex* self = new SQRex();

    try
    {
        self->regex = std::move(std::regex(pattern));
    }
    catch (std::regex_error& err)
    {
        static std::string errorMsg;
        errorMsg = err.what();

        *error = errorMsg.c_str();

       delete self;
       self = nullptr;
    }

    return self;
}

void sqstd_rex_free(SQRex *exp)
{
    if(exp)
        delete exp;
}

SQBool sqstd_rex_match(SQRex* exp,const SQChar* text)
{
    return std::regex_match(text, exp->regex);
}

SQBool sqstd_rex_searchrange(SQRex* exp,const SQChar* text_begin,const SQChar* text_end,const SQChar** out_begin, const SQChar** out_end)
{
    std::cmatch matches;
    if (!std::regex_search(text_begin, text_end, matches, exp->regex))
        return SQFalse;

    exp->matches = matches;

    if (out_begin) *out_begin = matches[0].first;
    if (out_end) *out_end = matches[0].second;

    return SQTrue;
}

SQBool sqstd_rex_search(SQRex* exp,const SQChar* text, const SQChar** out_begin, const SQChar** out_end)
{
    return sqstd_rex_searchrange(exp,text,text + scstrlen(text),out_begin,out_end);
}

SQInteger sqstd_rex_getsubexpcount(SQRex* exp)
{
    return exp->regex.mark_count() + 1;
}

SQUIRREL_API SQBool sqstd_rex_getsubexp(SQRex* exp, SQInteger n, SQRexMatch* subexp)
{
    if (n < 0 || n >= exp->matches.size()) return SQFalse;

    subexp->begin = exp->matches[n].matched ? exp->matches[n].first : nullptr;
    subexp->len = exp->matches[n].matched ? exp->matches[n].second - exp->matches[n].first : -1;

    return SQTrue;
}