/* lexical analysis with flex 2.6.0:  <17-04-17, river> */

%option yylineno
%option noyywrap

%top{
#include <stdlib.h>
#include <string.h>
#include "y.tab.h"
%}

/* definition */
/* arithmetic operator
 * relational operator
 * logical    operator
 * assignment operator
 */

BRACKET         "("|")"
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
#ifdef DEBUG
    printf("Line %d: (KEY, %s)\n", yylineno, yytext);
#endif
    yylval = strdup(yytext);
    return KEYWORD;
}   /* keyword */
{ID}        {
#ifdef DEBUG
printf("Line %d: (ID, %s)\n", yylineno, yytext);
#endif
    yylval = strdup(yytext);
    return ID;
}    /* id */
{INT}       {
#ifdef DEBUG
    printf("Line %d: (INT: %s)\n", yylineno, yytext);
#endif
    yylval = atoi(yytext);
    return INT;
}   /* integer */
{FLOAT}     {
#ifdef DEBUG
    printf("Line %d: (FLOAT: %s)\n", yylineno, yytext);
#endif
    yylval = strtof(yytext, NULL);
    return FLOAT;
} /* float */
{SYM}       {
#ifdef DEBUG
    printf("Line %d: (SYM, %s)\n", yylineno, yytext);
#endif
    yylval = strdup(yytext);
    return SYM;
}   /* operator */
{STR}       {
#ifdef DEBUG
    printf("Line %d: (STR %s)\n", yylineno, yytext);
#endif
    yylval = strdup(yytext);
    return STR;
}    /* string */

[[:digit:]]([[:alpha:]]|[[:digit:]])* {
    printf("Line %d: illegal variable identifier %s\n", yylineno, yytext);
    yyterminate();
}   /* illegal variable identifier */
.   {
    if(*yytext == '{' || *yytext == '\'')
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
