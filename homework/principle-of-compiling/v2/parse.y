%{
#include "common.h"

#define YYERROR_VERBOSE

int yylex(void);
void yyerror(const char *s);

char *database = NULL;
// yyval is global variable, can it be known the first use in some condition? Maybe yes.
%}

%union {
    int   numi;
    float numf;
    char *string;
    struct query_t *query;
    struct column_type_t *column_type;
    struct column_t *column;
    struct column_value_t *column_value;
}


%token <string>  CREATE DELETE DROP EXIT INSERT SELECT SHOW UPDATE
%token <string>  DATABASE DATABASES FROM INTO SET TABLE TABLES USE WHERE VALUES
%token <string>  ID DATATYPE STR
%token <numi>    NUMI
%token <numf>    NUMF
%type  <query> lines create_stmt drop_stmt show_stmt use_stmt exit_stmt
%type  <query> select_stmt insert_stmt update_stmt delete_stmt
%type  <string>  database_name table_name column name
%type  <column_type> column_type_list
%type  <column>  column_list
%type  <column_value> column_value_list

%type  <string>  assign_expr_list
%type  <string>  condition

%start start

%%

start
    : start lines ';' { hub($2); free_query($2); }
    | start ';' { fprintf(stdout, "ERROR: No query specified\n"); }
    | error ';' { yyerrok; } /* Error Recovery: On error, skip until ';' is read.  */
    | /* empty */
    ;

lines
    : create_stmt   { if($1 != NULL) $1->stmt = CREATE_STMT; $$ = $1; }
    | drop_stmt     { if($1 != NULL) $1->stmt = DROP_STMT;   $$ = $1; }
    | show_stmt     { if($1 != NULL) $1->stmt = SHOW_STMT;   $$ = $1; }
    | use_stmt      { if($1 != NULL) $1->stmt = USE_STMT;    $$ = $1; }
    | exit_stmt     { if($1 != NULL) $1->stmt = EXIT_STMT;   $$ = $1; }
    | select_stmt   { if($1 != NULL) $1->stmt = SELECT_STMT; $$ = $1; }
    | insert_stmt   { if($1 != NULL) $1->stmt = INSERT_STMT; $$ = $1; }
    | update_stmt   { if($1 != NULL) $1->stmt = UPDATE_STMT; $$ = $1; }
    | delete_stmt   { if($1 != NULL) $1->stmt = DELETE_STMT; $$ = $1; }
    ;

create_stmt
    : CREATE DATABASE database_name {
            $$ = create_query(ROOT);
            if($$ != NULL){
                printf("create: %s --\n", $1);
                printf("talbe: %s --\n", $2);
                printf("table_name: %s --\n", $3);
                assign_create_opt($$, DATABASE_OPT);
                assign_database_name($$, $3);
            }
            free($3);
        }
    | CREATE TABLE table_name '(' column_type_list')' { 
            $$ = create_query(database);
            if($$ != NULL){
                assign_create_opt($$, TABLE_OPT);
                printf("create: %s --\n", $1);
                printf("talbe: %s --\n", $2);
                printf("table_name: %s --\n", $3);
                assign_table_name($$, $3);
                assign_column_type_list($$, $5);
            }
            free($3);
        }
    | CREATE TABLE table_name {
            $$ = create_query(database);
            if($$ != NULL){
                assign_create_opt($$, TABLE_OPT);
                assign_table_name($$, $3);
                assign_column_type_list($$, NULL);
            }
            free($3);
        }
    ;

drop_stmt
    : DROP DATABASE database_name   {
            $$ = create_query(ROOT);
            if($$ != NULL)
                assign_database_name($$, $3);
            free($3);
        }
    | DROP TABLE table_name         {
            $$ = create_query(database);
            if($$ != NULL)
                assign_table_name($$, $3);
            free($3);
        }
    ;

show_stmt
    : SHOW DATABASES { $$ = create_query(ROOT); }
    | SHOW TABLES {
            $$ = create_query(database);
            if($$ != NULL)
                assign_database_name($$, database);
        }
    ;

use_stmt
    : USE database_name { 
            $$ = create_query(ROOT);
            if($$ != NULL)
                assign_database_name($$, $2);
            free($2);
        }
    ;

exit_stmt
    : EXIT  { $$ = create_query(ROOT); }
    ;

select_stmt
    : SELECT '*' FROM table_name    {
            $$ = create_query(database);
            if($$ != NULL){
                assign_table_name($$, $4);
            }
            free($4);
        }
    | SELECT column_list FROM table_name    {
            $$ = create_query(database);
            if($$ != NULL){
                assign_column_list($$, $2);
                assign_table_name($$, $4);
            }
            free($4);
        }
    | SELECT '*' FROM table_name WHERE condition    {
            $$ = create_query(database);
            if($$ != NULL){
                assign_table_name($$, $4);
                assign_condition($$, $6);
            }
            free($4);
        }
    | SELECT column_list FROM table_name WHERE condition    {
            $$ = create_query(database);
            if($$ != NULL){
                assign_column_list($$, $2);
                assign_table_name($$, $4);
                assign_condition($$, $6);
            }
            free($4);
        }
    ;

insert_stmt
    : INSERT INTO table_name VALUES '(' column_value_list ')' {
            $$ = create_query(database);
            if($$ != NULL){
                assign_table_name($$, $3);
                assign_column_list($$, NULL);
                assign_column_value_list($$, $6);
            }
            free($3);
        }
    | INSERT INTO table_name '(' column_list ')' VALUES '(' column_value_list ')' {
            $$ = create_query(database);
            if($$ != NULL){
                assign_table_name($$, $3);
                assign_column_list($$, $5);
                assign_column_value_list($$, $9);
            }
            free($3);
        }
    ;

update_stmt
    : UPDATE table_name SET assign_expr_list WHERE condition {
            $$ = create_query(database);
            if($$ != NULL){
                assign_table_name($$, $2);
                assign_assign_expr_list($$, $4);
                assign_condition($$, $6);
            }
            free($3);
        }
    ;

delete_stmt
    : DELETE FROM table_name WHERE condition {
            $$ = create_query(database);
            if($$ != NULL){
                assign_table_name($$, $3);
                assign_condition($$, $5);
            }
            free($3);
        }
    ;

column_type_list
    : column_type_list ',' column DATATYPE {
            struct column_type_t *node = NULL;
            node = create_column_type($3, $4);
            if(node != NULL){
                insque(node, $1);
                $$ = node;
            }
            else
                $$ = $1;
            free($3);
            free($4); // avoid memory leak
        }
    | column DATATYPE   {
            struct column_type_t *node = NULL;
            node = create_column_type($1, $2);
            if(node != NULL)
                insque(node, node);
            $$ = node;
            free($1);
            free($2); // avoid memory leak
        }
    ;

column_list
    : column_list ',' column  {
            struct column_t *node = NULL;
            node = create_column($3);
            if(node != NULL){
                insque(node, $1);
                $$ = node;
            }
            else
                $$ = $1;
            free($3);
        }
    | column  {
            struct column_t *node = NULL;
            node = create_column($1);
            if(node != NULL)
                insque(node, node);
            $$ = node;
            free($1);
        }
    ;

column_value_list
    : column_value_list ',' column '=' NUMI {
            struct column_value_t *node = NULL;
            node = create_column_value($3, &$5, INT);
            if(node != NULL){
                insque(node, $1);
                $$ = node;
            }
            else
                $$ = $1;
            free($3);
        }
    | column_value_list ',' column '=' NUMF {
            struct column_value_t *node = NULL;
            node = create_column_value($3, &$5, FLOAT);
            if(node != NULL){
                insque(node, $1);
                $$ = node;
            }
            else
                $$ = $1;
            free($3);
        }
    | column_value_list ',' column '=' STR  {
            struct column_value_t *node = NULL;
            node = create_column_value($3, $5, STRING);
            if(node != NULL){
                insque(node, $1);
                $$ = node;
            }
            else
                $$ = $1;
            free($3);
            free($5);
        }
    | column '=' NUMI   {
            struct column_value_t *node = NULL;
            node = create_column_value($1, &$3, INT);
            if(node != NULL)
                insque(node, node);
            $$ = node;
            free($1);
        }
    | column '=' NUMF   {
            struct column_value_t *node = NULL;
            node = create_column_value($1, &$3, FLOAT);
            if(node != NULL)
                insque(node, node);
            $$ = node;
            free($1);
        }
    | column '=' STR    {
            struct column_value_t *node = NULL;
            node = create_column_value($1, $3, STRING);
            if(node != NULL)
                insque(node, node);
            $$ = node;
            free($1);
            free($3);
        }
    ;

database_name
    : name  { $$ = $1; }
    ;

table_name
    : name  { $$ = $1; }
    ;

column
    : name  { $$ = $1; }
    ;

name
    : ID    { $$ = $1; }
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
    init();
    yyparse();
    return 0;
}
