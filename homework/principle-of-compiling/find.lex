/* lexical analysis with flex 2.6.0:  <17-04-17, river> */

%option yylineno
%option noyywrap

/* definition */
/* arithmetic operator
 * relational operator
 * logical operator
 * assignment operator
 */

ARITHMETIC  "+"|"-"|"*"|"/"|"%"
RELATIONAL  "=="|"!="|">"|"<"|">="|"<="
LOGICAL     "&&"|"||"|"!"
ASSIGNMENT  "="|"+="|"-="|"*="|"/="|"%="
SYMBOL      {ARITHMETIC}|{RELATIONAL}|{LOGICAL}|{ASSIGNMENT}

%%

[ \t]+  {} /* blankspace */
\n      {} /* newline */
--[.]*  {} /* comment */
[[:alpha:]|_][[:alpha:]|[:digit:]]* { printf("Line %d: (ID, %s)\n", yylineno, yytext); } /* word, ignore case */
[-+]?[:digit:]+ { printf("Line %d: (INT: %s)\n", yylineno, yytext); } /* integer */
[-+]?[:digit:]+\.[:digit:]+ { printf("Line: %d: (FLOAT: %s)\n", yylineno, yytext); } /* float */
{SYMBOL}  { printf("Line %d: (SYM, %s)\n", yylineno, yytext); }

%%

int main(int argc, char *argv[]){
    yylex();
    return 0;
}
