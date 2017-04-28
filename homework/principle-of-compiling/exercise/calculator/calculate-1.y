/* a simple calculator program without building warning: <28-04-17, river>
 *   source code from 《编译原理》 P184
 *   Bison Version 3.0.4
 */

%{
#include <ctype.h>
#include <stdio.h>

int yylex(void);
void yyerror(const char *s);
%}

%token DIGIT

%%
line    :   expr '\n'       { printf("%d\n", $1); }
        ;
expr    :   expr '+' term   { $$ = $1 + $3; }
        |   term
        ;
term    :   term '*' factor { $$ = $1 * $3; }
        |   factor
        ;
factor  :   '(' expr ')'    { $$ = $2; }
        |   DIGIT
        ;

%%
int yylex(void){
    int c;
    c = getchar();
    if(isdigit(c)){
        yylval = c - '0';
        return DIGIT;
    }
    return c;
}
