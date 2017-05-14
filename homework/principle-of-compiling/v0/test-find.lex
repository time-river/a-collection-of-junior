/* lexical analysis with flex 2.6.0:  <17-04-17, river>
 * string regex
 *   http://stackoverflow.com/questions/2039795/regular-expression-for-a-string-literal-in-flex-lex
 */

%option yylineno
%option noyywrap

%top{
#include <stdlib.h>
#include <string.h>
}

/* definition */
/* arithmetic operator
 * relational operator
 * logical    operator
 * assignment operator
 */

BRACKET         "{"|"}"|"("|")"
ARITHMETIC      "+"|"-"|"*"|"/"|"%"
RELATIONAL      "=="|"!="|">"|"<"|">="|"<="
LOGICAL         "&&"|"||"|"!"
ASSIGNMENT      "="|"+="|"-="|"*="|"/="|"%="
SYM             ","|";"|{BRACKET}|{ARITHMETIC}|{RELATIONAL}|{LOGICAL}|{ASSIGNMENT}

KEYWORD         (?i:create|use|show|insert|select|update|delete|drop|exit)
ID              ([[:alpha:]_][[:alpha:][:digit:]]*)
INT             ([[:digit:]]+)
FLOAT           ([[:digit:]]+\.[[:digit:]]+)
ONESTR          \"([^\\\"\t\r\n]|\\.)*\"
TWOSTR           '([^\\\'\t\r\n]|\\.)*'
STR             {ONESTR}|{TWOSTR}

%%

[ \t\r]+    {} /* blankspace */
\n          {} /* newline */
--[.]*      {} /* comment */

{KEYWORD}   { 
    printf("Line %d: (KEY, %s)\n", yylineno, yytext);
}   /* keyword */
{ID}        {
    printf("Line %d: (ID, %s)\n", yylineno, yytext);
}    /* id */
{INT}       {
    printf("Line %d: (INT: %s)\n", yylineno, yytext);
}   /* integer */
{FLOAT}     {
    printf("Line %d: (FLOAT: %s)\n", yylineno, yytext);
} /* float */
{SYM}       {
    printf("Line %d: (SYM, %s)\n", yylineno, yytext);
}   /* operator */
{STR}       {
    printf("Line %d: (STR %s)\n", yylineno, yytext);
}    /* string */

[[:digit:]]([[:alpha:]]|[[:digit:]])* {
    printf("Line %d: illegal variable identifier %s\n", yylineno, yytext);
    yyterminate();
}   /* illegal variable identifier */
.   {
    if(*yytext == '\'')
        printf("Line %d: missing the right part of %s\n",
                yylineno, yytext);
    else
        printf("Line %d: illegal character %s\n",
                yylineno, yytext);
    yyterminate();
}

%%

int main(int argc, char *argv[]){
    yylex();
    return 0;
}
