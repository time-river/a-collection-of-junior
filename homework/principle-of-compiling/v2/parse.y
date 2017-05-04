%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

#define YYERROR_VERBOSE

int yylex(void);
void yyerror(const char *s);

char *database = NULL;
%}

%union {
    int   numi;
    float numf;
    char *string;
    struct command_t *command;
}


%token <string>  CREATE DELETE DROP EXIT INSERT SELECT SHOW UPDATE
%token <string>  DATABASE DATABASES FROM INTO SET TABLE TABLES USE WHERE VALUES
%token <string>  ID DATATYPE
%type  <command> lines create_stmt drop_stmt show_stmt use_stmt exit_stmt
%type  <command> select_stmt insert_stmt update_stmt delete_stmt
%type  <string>  database_name table_name name

%type  <string>  column_type_list column_list column_value_list assign_expr_list
%type  <string>  condition

%start start

%%

start
    : start lines ';' { hub($2); }
    | start ';' { fprintf(stdout, "ERROR: No query specified\n"); }
    | /* empty */
    ;

lines
    : create_stmt   { $1->stmt = CREATE_STMT; $$ = $1; }
    | drop_stmt     { $1->stmt = DROP_STMT;   $$ = $1; }
    | show_stmt     { $1->stmt = SHOW_STMT;   $$ = $1; }
    | use_stmt      { $1->stmt = USE_STMT;    $$ = $1; }
    | exit_stmt     { $1->stmt = EXIT_STMT;   $$ = $1; }
    | select_stmt   { $1->stmt = SELECT_STMT; $$ = $1; }
    | insert_stmt   { $1->stmt = INSERT_STMT; $$ = $1; }
    | update_stmt   { $1->stmt = UPDATE_STMT; $$ = $1; }
    | delete_stmt   { $1->stmt = DELETE_STMT; $$ = $1; }
    ;

create_stmt
    : CREATE DATABASE database_name {
            $$ = create_command(database);
            if($$ != NULL)
                assign_database_name($$, $3);
        }
    | CREATE TABLE table_name '(' column_type_list')' { 
            $$ = create_command(database);
            if($$ != NULL){
                assign_table_name($$, $3);
                assign_column_type_list($$, $5);
            }
        }
    ;

drop_stmt
    : DROP DATABASE database_name   {
            $$ = create_command(database);
            if($$ != NULL)
                assign_database_name($$, $3);
        }
    | DROP TABLE table_name         {
            $$ = create_command(database);
            if($$ != NULL)
                assign_table_name($$, $3);
        }
    ;

show_stmt
    : SHOW DATABASES { $$ = create_command(ROOT); }
    | SHOW TABLES {
            $$ = create_command(database);
            if($$ != NULL)
                assign_database_name($$, database);
        }
    ;

use_stmt
    : USE database_name { 
            $$ = create_command(ROOT);
            if($$ != NULL)
                assign_database_name($$, $2);
        }
    ;

exit_stmt
    : EXIT  { $$ = create_command(ROOT); }
    ;

select_stmt
    : SELECT '*' FROM table_name    {
            $$ = create_command(database);
            if($$ != NULL){
                assign_table_name($$, $4);
            }
        }
    | SELECT column_list FROM table_name    {
            $$ = create_command(database);
            if($$ != NULL){
                assign_column_list($$, $2);
                assign_table_name($$, $4);
            }
        }
    | SELECT '*' FROM table_name WHERE condition    {
            $$ = create_command(database);
            if($$ != NULL){
                assign_table_name($$, $4);
                assign_condition($$, $6);
            }
        }
    | SELECT column_list FROM table_name WHERE condition    {
            $$ = create_command(database);
            if($$ != NULL){
                assign_column_list($$, $2);
                assign_table_name($$, $4);
                assign_condition($$, $6);
            }
        }
    ;

insert_stmt
    : INSERT INTO table_name VALUES '(' column_value_list ')' {
            $$ = create_command(database);
            if($$ != NULL){
                assign_table_name($$, $3);
                assign_column_list($$, NULL);
                assign_column_value_list($$, $6);
            }
        }
    | INSERT INTO table_name '(' column_list ')' VALUES '(' column_value_list ')' {
            $$ = create_command(database);
            if($$ != NULL){
                assign_table_name($$, $3);
                assign_column_list($$, $5);
                assign_column_value_list($$, $9);
            }
        }
    ;

update_stmt
    : UPDATE table_name SET assign_expr_list WHERE condition {
            $$ = create_command(database);
            if($$ != NULL){
                assign_table_name($$, $2);
                assign_assign_expr_list($$, $4);
                assign_condition($$, $6);
            }
        }
    ;

delete_stmt
    : DELETE FROM table_name WHERE condition {
            $$ = create_command(database);
            if($$ != NULL){
                assign_table_name($$, $3);
                assign_condition($$, $5);
            }
        }
    ;

column_type_list
    : column_type_list ',' ID DATATYPE
    | ID DATATYPE
    ;

column_list
    : column_list ',' name
    | name
    ;

column_value_list
    : column_value_list ',' name
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
    : ID
    ;

assign_expr_list
    : { /* 解决不了，需要语义分析 */ }
    ;

%%

void yyerror(const char *s){
    fprintf(stderr, "Error: %s\n", s);
    return;
}

#include "lex.yy.c"

int main(int argc, char *argv[]){
    yyparse();
    return 0;
}
