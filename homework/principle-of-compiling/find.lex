/* lexical analysis with flex 2.6.0:  <17-04-17, river> */

%option yylineno
%option noyywrap

/* definition */
/* arithmetic operator
 * relational operator
 * logical    operator
 * assignment operator
 */

BRACKET     "{"|"}"|"("|")"
ARITHMETIC  "+"|"-"|"*"|"/"|"%"
RELATIONAL  "=="|"!="|">"|"<"|">="|"<="
LOGICAL     "&&"|"||"|"!"
ASSIGNMENT  "="|"+="|"-="|"*="|"/="|"%="
OPERATOR    {BRACKET}|{ARITHMETIC}|{RELATIONAL}|{LOGICAL}|{ASSIGNMENT}

%%

[ \t]+  {} /* blankspace */
\n      {} /* newline */
--[.]*  {} /* comment */
([[:alpha:]]|_)([[:alpha:]]|[[:digit:]])* { printf("Line %d: (ID, %s)\n", yylineno, yytext); } /* word, ignore case */
[-+]?[[:digit:]]+ { printf("Line %d: (INT: %s)\n", yylineno, yytext); } /* integer */
[-+]?[[:digit:]]+\.[[:digit:]]+ { printf("Line %d: (FLOAT: %s)\n", yylineno, yytext); } /* float */
{OPERATOR}  { printf("Line %d: (SYM, %s)\n", yylineno, yytext); }

[[:digit:]]([[:alpha:]]|[[:digit:]])* {
    printf("Line %d: illegal variable identifier %s\n", yylineno, yytext);
    yyterminate();
} /* illegal variable identifier */
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
