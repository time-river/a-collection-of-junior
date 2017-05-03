/* SQL Interpreter Version 1.0:  <02-05-17, river>
 *   grammar analysis with bison 3.0.4
 */

%{
#include "common.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define YYERROR_VERBOSE
#define YYSTYPE char *

int yylex(void);
void yyerror(const char *s);
%}

%token KEYWORD IDENTIFIER
%token DBTB DBTBS

%start lines

%%

lines
    : lines program ';'     { printf("lines program: %s %s ;\n", $1, $2); }
    | lines ';'             { printf("lines: %s ;\n", $1); }
    | ';'                   { puts("ERROR: No query specified"); }
    |                       { puts("Empty"); }
    ;
program
    : KEYWORD DBTB  name    { printf("program 1: %s %s %s\n", $1, $2, $3); create_drop($1, $2, $3); }
    | KEYWORD name          { printf("program 2: %s %s\n", $1, $2); use($1, $2); }
    | KEYWORD DBTBS         { printf("program 3: $1 %s $2 %s\n", $1, $2); show($1, $2); }
    | KEYWORD               { printf("program 4: %s\n", $1); puts("Bye bye~"); exit(EXIT_SUCCESS); }
    ;
name
    : IDENTIFIER
    ;

%%
#include "lex.yy.c"

int main(int argc, char *argv[]){
    yyparse();
    return 0;
}
