%{
#include <stdio.h>
#include <stdlib.h>
#include "common.h"

#define YYERROR_VERBOSE
#define YYSTYPE char *

int yylex(void);
void yyerror(const char *s);

struct command_t command;
%}

%token CREATE DELETE DROP EXIT INSERT SELECT SHOW UPDATE
%token DATABASE DATABASES FROM INTO SET TABLE TABLES USE WHERE VALUES
%token ID DATATYPE

%start start

%%

start
    : start lines ';' { hub(command); }
    | start ';' { fprintf(stdout, "ERROR: No query specified\n"); }
    | /* empty */
    ;

lines
    : create_stmt   { command.stmt = CREATE_STMT; }
    | drop_stmt     { command.stmt = DROP_STMT; }
    | show_stmt     { command.stmt = SHOW_STMT; }
    | use_stmt      { command.stmt = USE_STMT; }
    | exit_stmt     { command.stmt = EXIT_STMT; }
    | select_stmt   { command.stmt = SELECT_STMT; }
    | insert_stmt   { command.stmt = INSERT_STMT; }
    | update_stmt   { command.stmt = UPDATE_STMT; }
    | delete_stmt   { command.stmt = DELETE_STMT; }
    ;

create_stmt
    : CREATE DATABASE name
    | CREATE TABLE name '(' column_type_list')'
    ;

drop_stmt
    : DROP DATABASE name
    | DROP TABLE name
    ;

show_stmt
    : SHOW DATABASES
    | SHOW TABLES
    ;

use_stmt
    : USE name
    ;

exit_stmt
    : EXIT
    ;

select_stmt
    : SELECT '*' FROM name
    | SELECT column_list FROM name
    | SELECT '*' FROM name WHERE condition
    | SELECT column_list FROM name WHERE condition
    ;

insert_stmt
    : INSERT INTO name VALUES '(' column_list ')'
    | INSERT INTO name '(' column_list ')' VALUES '(' column_list ')'
    ;

update_stmt
    : UPDATE name SET assign_expr WHERE condition
    ;

delete_stmt
    : DELETE FROM name WHERE condition
    ;

column_type_list
    : column_type_list ',' ID DATATYPE
    | ID DATATYPE
    ;

column_list
    : column_list ',' name
    | name
    ;

name
    : ID
    ;

condition
    :
    ;

assign_expr
    : { /* 解决不了，需要语义分析 */ }
    ;

%%

void yyerror(const char *s){
    fprintf(stderr, "Error: %s\n", s);
    return;
}

#include "lex.yy.c"
