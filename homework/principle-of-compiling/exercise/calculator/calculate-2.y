/* a simple and more useful calculator program without building warning: <28-04-17, river>
 *   source code from 《编译原理》 P186
 *   Bison Version 3.0.4
 */

%{
#include <ctype.h>
#include <stdio.h>

#define YYSTYPE double /* double type for Yacc stack */

int yylex(void);
void yyerror(const char *s);
%}

%token NUMBER

%left   '+' '-'
%left   '*' '/'
%right  UMINUS

%%
lines   :   lines expr '\n'       { printf("%g\n", $2); }
        |   lines '\n'
        |   /* empty */
        ;
expr    :   expr '+' expr   { $$ = $1 + $3; }
        |   expr '-' expr   { $$ = $1 - $3; }
        |   expr '*' expr   { $$ = $1 * $3; }
        |   expr '/' expr   { $$ = $1 / $3; }
        |   '(' expr ')'    { $$ = $2; }
        |   '-' expr %prec UMINUS { $$ = - $2; } /* %prec UMINUS 用于解决优先级问题. 思考: 8*-5 这种到底对不对? */
        |   '+' expr %prec UMINUS { $$ = $2; }         /* 二含义性文法问题? */
        |   NUMBER
        ;

%%
int yylex(void){
    int c;
    while((c=getchar()) == ' ');
    if((c == '.' || isdigit(c))){
        ungetc(c, stdin);
        scanf("%lf", &yylval);
        return NUMBER;
    }
    return c;
}
