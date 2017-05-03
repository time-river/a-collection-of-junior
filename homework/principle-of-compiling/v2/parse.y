%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

#define YYERROR_VERBOSE
#define YYSTYPE char *

int yylex(void);
void yyerror(const char *s);

struct command_t instruct = {
    .database_name = NULL,
    .table_name = NULL
};
struct command_t *command = &instruct;

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
    : create_stmt   { command->stmt = CREATE_STMT; }
    | drop_stmt     { command->stmt = DROP_STMT; }
    | show_stmt     { command->stmt = SHOW_STMT; }
    | use_stmt      { command->stmt = USE_STMT; }
    | exit_stmt     { command->stmt = EXIT_STMT; }
    | select_stmt   { command->stmt = SELECT_STMT; }
    | insert_stmt   { command->stmt = INSERT_STMT; }
    | update_stmt   { command->stmt = UPDATE_STMT; }
    | delete_stmt   { command->stmt = DELETE_STMT; }
    ;

create_stmt
    : CREATE DATABASE database_name { assign_database_name(command, $3); }
    | CREATE TABLE table_name '(' column_type_list')' { assign_table_name(command, $3); assign_column_type_list(command, $4); }
    ;

drop_stmt
    : DROP DATABASE database_name   { assign_database_name(command, $3); }
    | DROP TABLE table_name         { assign_table_name(command, $3); }
    ;

show_stmt
    : SHOW DATABASES
    | SHOW TABLES
    ;

use_stmt
    : USE database_name { assign_database_name(command, $2); }
    ;

exit_stmt
    : EXIT
    ;

select_stmt
    : SELECT '*' FROM table_name    { assign_column_list(command, $2); assign_table_name(command, $4); }
    | SELECT column_list FROM table_name    { assign_column_list(command, $2); assign_table_name(command, $4); }
    | SELECT '*' FROM table_name WHERE condition    { assign_column_list(command, $2); assign_table_name(command, $4); assign_condition(command, $6); }
    | SELECT column_list FROM table_name WHERE condition    { assign_column_list(command, $2); assign_table_name(command, $4); assign_condition(command, $6); }
    ;

insert_stmt
    : INSERT INTO table_name VALUES '(' value_column_list ')' { assign_table_name(command, $3); assign_column_list(command, NULL); assign_value_column_list(command, $5); }
    | INSERT INTO table_name '(' column_list ')' VALUES '(' value_column_list ')' { assign_table_name(command, $3); assign_column_list(command, $5); assign_value_column(command, $9); }
    ;

update_stmt
    : UPDATE table_name SET assign_expr WHERE condition { assign_table_name(command, $2); assign_assign_expr(command, $4); assign_condition(command, $6); }
    ;

delete_stmt
    : DELETE FROM table_name WHERE condition { assign_table_name(command, $3); assign_condition(command, $5); }
    ;

column_type_list
    : column_type_list ',' ID DATATYPE
    | ID DATATYPE
    ;

column_list
    : column_list ',' name
    | name
    ;

value_column_list
    : value_column_list ',' name
    | name
    ;

database_name
    : name
    ;

table_name
    : name
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
