/*  see copyright notice in squirrel.h */
#ifndef _SQLEXER_H_
#define _SQLEXER_H_

#ifdef SQUNICODE
typedef SQChar LexChar;
#else
typedef unsigned char LexChar;
#endif

struct SQLexer
{
    SQLexer();
    ~SQLexer();
    void Init(SQSharedState *ss,SQLEXREADFUNC rg,SQUserPointer up,CompilerErrorFunc efunc,void *ed);
    void Error(const SQChar *err);
    SQInteger Lex();
    const SQChar *Tok2Str(SQInteger tok);
private:
    SQInteger GetIDType(const SQChar *s,SQInteger len);
    SQInteger ReadString(SQInteger ndelim,bool verbatim);
    SQInteger ReadNumber();
    void LexBlockComment();
    void LexLineComment();
    SQInteger ReadID();
    void Next();
    LexChar PeekNextChar(); // New: Declaration for peek function
#ifdef SQUNICODE
#if WCHAR_SIZE == 2
    SQInteger AddUTF16(SQUnsignedInteger ch);
#endif
#else
    SQInteger AddUTF8(SQUnsignedInteger ch);
#endif
    SQInteger ProcessStringHexEscape(SQChar *dest, SQInteger maxdigits);
    SQInteger LexTemplateStringContent();   // New: for lexing inside ``
    SQInteger LexTemplateExpressionContent(); // New: for lexing inside ${}
    enum TemplateLexState {
        TLS_NONE,
        TLS_IN_STRING,
        TLS_IN_EXPRESSION
    };
    SQInteger _curtoken;
    SQTable *_keywords;
    SQBool _reached_eof;
public:
    SQInteger _prevtoken;
    SQInteger _currentline;
    SQInteger _lasttokenline;
    SQInteger _currentcolumn;
    const SQChar *_svalue;
    SQInteger _nvalue;
    SQFloat _fvalue;
    SQLEXREADFUNC _readf;
    SQUserPointer _up;
    LexChar _currdata;
    LexChar _nextdata; // New member for one-character lookahead
    SQSharedState *_sharedstate;
    sqvector<SQChar> _longstr;
    TemplateLexState _template_lex_state; // New member for template string lexing state
    CompilerErrorFunc _errfunc;
    void *_errtarget;
};

#endif
