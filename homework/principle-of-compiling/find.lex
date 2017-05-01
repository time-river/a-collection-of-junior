/* lexical analysis with flex 2.6.0:  <17-04-17, river> */

%option yylineno
%option noyywrap

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
OPERATOR        ","|";"|{BRACKET}|{ARITHMETIC}|{RELATIONAL}|{LOGICAL}|{ASSIGNMENT}

/* keyword */
CREATE          (?i:create)
USE             (?i:use)
SHOW            (?i:show)
INSERT          (?i:insert)
SELECT          (?i:select)
UPDATE          (?i:update)
DELETE          (?i:delete)
DROP            (?i:exit)

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

{CREATE}    { 
#ifdef DEBUG
    printf("Line %d: (KEY, %s)\n", yylineno, yytext);
#endif
    yylval = yytext;
    return CREATE;
}   /* create */
{USE}       { 
#ifdef DEBUG
    printf("Line %d: (KEY, %s)\n", yylineno, yytext);
#endif
    yylval = yytext;
    return USE;
}   /* use */
{SHOW}      { 
#ifdef DEBUG
    printf("Line %d: (KEY, %s)\n", yylineno, yytext);
#endif
    yylval = yytext;
    return SHOW;
}   /* show */
{INSERT}    { 
#ifdef DEBUG
    printf("Line %d: (KEY, %s)\n", yylineno, yytext);
#endif
    yylval = yytext;
    return INSERT;
}   /* insesrt */
{SELECT}    { 
#ifdef DEBUG
    printf("Line %d: (KEY, %s)\n", yylineno, yytext);
#endif
    yylval = yytext;
    return SELECT;
}   /* select */
{UPDATE}    { 
#ifdef DEBUG
    printf("Line %d: (KEY, %s)\n", yylineno, yytext);
#endif
    yylval = yytext;
    return UPDATE;
}   /* update */
{DELETE}    { 
#ifdef DEBUG
    printf("Line %d: (KEY, %s)\n", yylineno, yytext);
#endif
    yylval = yytext;
    return DELETE;
}   /* delete */
{DROP}      { 
#ifdef DEBUG
    printf("Line %d: (KEY, %s)\n", yylineno, yytext);
#endif
    yylval = yytext;
    return DELETE;
}   /* delete */
{KEYWORD}   { 
#ifdef DEBUG
    printf("Line %d: (KEY, %s)\n", yylineno, yytext);
#endif
    yylval = yytext;
    return KEYWORD;
}   /* keyword */
{ID}        {
#ifdef DEBUG
printf("Line %d: (ID, %s)\n", yylineno, yytext);
#endif
    yylval = yytext;
    return ID;
}    /* id */
{INT}       {
#ifdef DEBUG
    printf("Line %d: (INT: %s)\n", yylineno, yytext);
#endif
    yylval = yytext;
    return INT;
}   /* integer */
{FLOAT}     {
#ifdef DEBUG
    printf("Line %d: (FLOAT: %s)\n", yylineno, yytext);
#endif
    yylval = yytext;
    return FLOAT;
} /* float */
{OPERATOR}       {
#ifdef DEBUG
    printf("Line %d: (SYM, %s)\n", yylineno, yytext);
#endif
    yylval = yytext;
    return SYM;
}   /* operator */
{STR}       {
#ifdef DEBUG
    printf("Line %d: (STR %s)\n", yylineno, yytext);
#endif
    yylval = yytext;
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
