/**
 * Read the LICENSE file for the licensing information.
 * Author: hansl@google.com (Hans Larsen)
 */

%{
  #include <stdarg.h>
  #include <stdlib.h>
  #include <stdio.h>

  #include "pcl.h"
%}

%{
  // String declaration. The maximum size for a string is only for the string
  // literal. You can still concatenate two strings together, for example.
  // This contraints both type of strings: standard literals and """..."""
  // multiline ones.
  // A syntax error happens when STR_MAX_SIZE is reached.
  static const int STR_MAX_SIZE = 4095;
  static char str_buffer[STR_MAX_SIZE + 1];
  static int buffer_index = 0;

  static void str_add(char c) {
    if (buffer_index > STR_MAX_SIZE) {
      yyerror("String constant too long.");
    }
    str_buffer[buffer_index++] = c;
  }
  static void str_reset() {
    buffer_index = 0;
  }
  static const char* str_get() {
    str_add(0);
    return strdup(str_buffer);
  }

%}
%x ST_STRING
%x ST_ML_STRING
%x ST_COMMENT

  /* Floats definitions */
dseq      ([[:digit:]]+)
dseq_opt  ([[:digit:]]*)
frac      (({dseq_opt}"."{dseq})|{dseq}".")
exp       ([eE][+-]?{dseq})
exp_opt   ({exp}?)
fsuff     [flFL]
fsuff_opt ({fsuff}?)
hpref     (0[xX])
hdseq     ([[:xdigit:]]+)
hdseq_opt ([[:xdigit:]]*)
hfrac     (({hdseq_opt}"."{hdseq})|({hdseq}"."))
bexp      ([pP][+-]?{dseq})
dfc       (({frac}{exp_opt}{fsuff_opt})|({dseq}{exp}{fsuff_opt}))
hfc       (({hpref}{hfrac}{bexp}{fsuff_opt})|({hpref}{hdseq}{bexp}{fsuff_opt}))

%%

  /* Comments */

#.*[\n]              { ll_newline(); }

  /* Multiline comments */
"/*"                 { BEGIN(ST_COMMENT); }
<ST_COMMENT>"*/"     { BEGIN(0); }
<ST_COMMENT>[^*\n]+  { }
<ST_COMMENT>"*"[^/]  { }
<ST_COMMENT>\n       { ll_newline(); }

  /* Multi-Line String Literals */
\"\"\"               { BEGIN(ST_ML_STRING); str_reset(); }
<ST_ML_STRING>\"\"\" { BEGIN(0); yylval.s = str_get(); return STRING; }
<ST_ML_STRING>\n     { str_add(*yytext); ll_newline(); }
<ST_ML_STRING>.      { str_add(*yytext); }

  /* String Literals */
\"                  { BEGIN(ST_STRING); str_reset(); }
<ST_STRING>\\n      { str_add('\n'); }
<ST_STRING>\\t      { str_add('\t'); }
<ST_STRING>\\\"     { str_add('\"'); }
<ST_STRING>\"       { BEGIN(0); yylval.s = str_get(); return STRING; }
<ST_STRING>\n       { yyerror("String literals cannot contain new lines."); }
<ST_STRING>.        { str_add(*yytext); }

  /* Ignore whitespaces */
[ \t]+ ;
[\n]  { ll_newline(); }

  /* INTEGERS */
([[:digit:]]{-}[0])[[:digit:]]* { yylval.i = strtol(yytext, NULL, 10);
                                  return INTEGER;
                                }
0[xX][[:xdigit:]]+              { yylval.i = strtol(yytext, NULL, 16);
                                  return INTEGER;
                                }
0[[:xdigit:]]+                  { yylval.i = strtol(yytext, NULL, 8);
                                  return INTEGER;
                                }

  /* FLOATS */
({dfc}|{hfc})                   { yylval.d = strtod(yytext, NULL);
                                  return DOUBLE;
                                }

  /* Keywords */
@import                         { return IMPORT; }
@namespace                      { return NAMESPACE; }
@experiment                     { return EXPERIMENT; }
@function                       { return FUNCTION; }
@const                          { return CONST; }
@param                          { return PARAM; }
@dictionary                     { return NAMESPACE; }
@variant                        { return VARIANT; }
@criteria                       { return CRITERIA; }

  /* Types and Constants */
@int                            { return TYPE_INTEGER; }
@string                         { return TYPE_STRING; }
@double                         { return TYPE_DOUBLE; }
@bool                           { return TYPE_BOOL; }
@true                           { return BOOL_TRUE; }
@false                          { return BOOL_FALSE; }

  /* Multi-character comparison */
">="          return GE;
"<="          return LE;
"=="          return EQ;
"!="          return NE;
"||"          return OR;
"&&"          return AND;

  /* Criterias Symbols */
[%][\.A-Za-z_]+                 { yylval.s = strdup(yytext);
                                  return CRITERIA_SYMBOL;
                                }
  /* Symbols */
[A-Za-z_][\.A-Za-z0-9_]*        { yylval.s = strdup(yytext); return SYMBOL; }
\.[\.A-Za-z_][\.A-Za-z0-9_]*    { yylval.s = strdup(yytext); return SYMBOL; }

  /* Single Characters Operators/Keywords */
[-+*/&=:;|!(){}\[\]><]          { return *yytext; }

  /* Anything else is a syntax error. */
.                               { yyerror("Unknown character '%c' (%d).",
                                          *yytext, *yytext);
                                }

%%
// This function
int yywrap(void) {
  return ll_eof();
}

void yyerror(const char* str, ...) {
  static char buffer[1024];
  va_list args;
  va_start(args, str);
  vsnprintf(buffer, sizeof(buffer) / sizeof(char), str, args);
  va_end(args);

  ll_error(buffer);
}
