/* a simple calculator program without building warning
 *      and more error information: <28-04-17, river>
 *   source code from 《编译原理》 P184
 *   Bison Version 3.0.4
 * Be care of the differences of grammer, and think about it
 * References:
 *   more error information
 *     https://www.ibm.com/developerworks/cn/linux/l-flexbison.html
 */

%{
#include <ctype.h>
#include <stdio.h>

#define YYERROR_VERBOSE

int yylex(void);
void yyerror(const char *s);
%}

%token DIGIT

%%
line    :   line expr '\n'       { printf("%d\n", $1); }
        |   line '\n'
        |
        ;
expr    :   expr '+' term   { printf("+ -- $1: %d $3: %d\n", $1, $3); $$ = $1 + $3; }
        |   term            { printf("term -- %d\n", $1); }
        ;
term    :   term '*' factor { printf("* -- $1: %d $3: %d\n", $1, $3); $$ = $1 * $3; }
        |   factor          { printf("factor -- %d\n", $1); }
        ;
factor  :   '(' expr ')'    { printf("expr -- %d\n", $2); $$ = $2; }
        |   DIGIT           { printf("DIGIT -- %d\n", $1); }
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
