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
    struct value_t *value;
    struct assign_expr_t *assign_expr;
    struct condition_t *condition;
}

%token CREATE DELETE DROP EXIT INSERT SELECT SHOW UPDATE
%token DATABASE DATABASES FROM INTO SET TABLE TABLES USE WHERE VALUES
%token <string> ID DATATYPE STR
%token <numi>   NUMI
%token <numf>   NUMF
%type  <query> lines create_stmt drop_stmt show_stmt use_stmt exit_stmt
%type  <query> select_stmt insert_stmt update_stmt delete_stmt
%type  <string> database_name table_name column name
%type  <column_type> column_type_list
%type  <column>  column_list
%type  <value> value_list
%type  <numi> expr_int
%type  <numf> expr_float
%type  <assign_expr>  assign_expr_list
%type  <condition>  condition

%destructor { free($$); } DATATYPE STR
%destructor { free($$); } database_name table_name column

%left   '+' '-'
%left   '*' '/'
%right  UMINUS
%right  '^'

%start start

%%

start
    : start lines ';' { hub($2); free_query($2); }
    | start ';' { fprintf(stderr, "ERROR: No query specified\n"); }
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
                assign_create_opt($$, DATABASE_OPT);
                assign_database_name($$, $3);
            }
        }
    | CREATE TABLE table_name '(' column_type_list')' { 
            $$ = create_query(database);
            if($$ != NULL){
                assign_create_opt($$, TABLE_OPT);
                assign_table_name($$, $3);
                assign_column_type_list($$, $5);
            }
        }
    | CREATE TABLE table_name {
            $$ = create_query(database);
            if($$ != NULL){
                assign_create_opt($$, TABLE_OPT);
                assign_table_name($$, $3);
                assign_column_type_list($$, NULL);
            }
        }
    ;

drop_stmt
    : DROP DATABASE database_name   {
            $$ = create_query(ROOT);
            if($$ != NULL)
                assign_database_name($$, $3);
        }
    | DROP TABLE table_name         {
            $$ = create_query(database);
            if($$ != NULL)
                assign_table_name($$, $3);
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
        }
    | SELECT column_list FROM table_name    {
            $$ = create_query(database);
            if($$ != NULL){
                assign_column_list($$, $2);
                assign_table_name($$, $4);
            }
        }
    | SELECT '*' FROM table_name WHERE condition    {
            $$ = create_query(database);
            if($$ != NULL){
                assign_table_name($$, $4);
                assign_condition($$, $6);
            }
        }
    | SELECT column_list FROM table_name WHERE condition    {
            $$ = create_query(database);
            if($$ != NULL){
                assign_column_list($$, $2);
                assign_table_name($$, $4);
                assign_condition($$, $6);
            }
        }
    ;

insert_stmt
    : INSERT INTO table_name VALUES '(' value_list ')' {
            $$ = create_query(database);
            if($$ != NULL){
                assign_table_name($$, $3);
                assign_column_list($$, NULL);
                assign_value_list($$, $6);
            }
        }
    | INSERT INTO table_name '(' column_list ')' VALUES '(' value_list ')' {
            $$ = create_query(database);
            if($$ != NULL){
                assign_table_name($$, $3);
                assign_column_list($$, $5);
                assign_value_list($$, $9);
            }
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
        }
    ;

delete_stmt
    : DELETE FROM table_name WHERE condition {
            $$ = create_query(database);
            if($$ != NULL){
                assign_table_name($$, $3);
                assign_condition($$, $5);
            }
        }
    ;

column_type_list
    : column_type_list ',' column DATATYPE {
            struct column_type_t *node = NULL;
            node = create_column_type($3, $4);
            if(node != NULL){
                insque(node, $1); // bug, 重复命名问题
                $$ = node;
            }
            else
                $$ = $1;
        }
    | column DATATYPE   {
            struct column_type_t *node = NULL;
            node = create_column_type($1, $2);
            if(node != NULL)
                insque(node, node);
            $$ = node;
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
        }
    | column  {
            struct column_t *node = NULL;
            node = create_column($1);
            if(node != NULL)
                insque(node, node);
            $$ = node;
        }
    ;

value_list
    : value_list ',' expr_int {
            struct value_t *node = NULL;
            node = create_value(&$3, INT);
            if(node != NULL){
                insque(node, $1);
                $$ = node;
            }
            else
                $$ = $1;
        }
    | value_list ',' expr_float {
            struct value_t *node = NULL;
            node = create_value(&$3, FLOAT);
            if(node != NULL){
                insque(node, $1);
                $$ = node;
            }
            else
                $$ = $1;
        }
    | value_list ',' STR  {
            struct value_t *node = NULL;
            node = create_value($3, STRING);
            if(node != NULL){
                insque(node, $1);
                $$ = node;
            }
            else
                $$ = $1;
        }
    | expr_int   {
            struct value_t *node = NULL;
            node = create_value(&$1, INT);
            if(node != NULL)
                insque(node, node);
            $$ = node;
        }
    | expr_float   {
            struct value_t *node = NULL;
            node = create_value(&$1, FLOAT);
            if(node != NULL)
                insque(node, node);
            $$ = node;
        }
    | STR    {
            struct value_t *node = NULL;
            node = create_value($1, STRING);
            if(node != NULL)
                insque(node, node);
            $$ = node;
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
    :   { $$ = create_condition(); } 
    ;

assign_expr_list
    : assign_expr_list ',' column '=' expr_float {
            struct assign_expr_t *node = NULL;
            node = create_assign_expr($3, &$5, FLOAT);
            if(node != NULL)
                insque(node, $1);
            $$ = node;
        }
    | assign_expr_list ',' column '=' expr_int   {
            struct assign_expr_t *node = NULL;
            node = create_assign_expr($3, &$5, INT);
            if(node != NULL)
                insque(node, $1);
            $$ = node;
        }
    | assign_expr_list ',' column '=' STR   {
            struct assign_expr_t *node = NULL;
            node = create_assign_expr($3, $5, STRING);
            if(node != NULL)
                insque(node, $1);
            $$ = node;
        }
    | column '=' expr_float {
            struct assign_expr_t *node = NULL;
            node = create_assign_expr($1, &$3, FLOAT);
            if(node != NULL)
                insque(node, node);
            $$ = node;
        }
    | column '=' expr_int   {
            struct assign_expr_t *node = NULL;
            node = create_assign_expr($1, &$3, INT);
            if(node != NULL)
                insque(node, node);
            $$ = node;
        }
    | column '=' STR    {
            struct assign_expr_t *node = NULL;
            node = create_assign_expr($1, $3, STRING);
            if(node != NULL)
                insque(node, node);
            $$ = node;
        }
    ;

expr_float
    : NUMF                        { $$ = $1; }
    | expr_float '+' expr_float   { $$ = $1 + $3; }
    | expr_float '+' expr_int     { $$ = $1 + (float)$3; }
    | expr_int   '+' expr_float   { $$ = (float)$1 - $3; }
    | expr_float '-' expr_float   { $$ = $1 - $3; }
    | expr_float '-' expr_int     { $$ = $1 + (float)$3; }
    | expr_int   '-' expr_float   { $$ = (float)$1 - $3; }
    | expr_float '*' expr_float   { $$ = $1 * $3; }
    | expr_float '*' expr_int     { $$ = $1 * (float)$3; }
    | expr_int   '*' expr_float   { $$ = (float)$1 * $3; } 
    | expr_float '/' expr_float   { 
            if($3)
                $$ = $1 / $3;
            else{
                $$ = 1.0f;
                fprintf(stderr, "ERROR: division by zero\n");
            }
        }
    | expr_float '/' expr_int     { 
            if($3)
                $$ = $1 / (float)$3;
            else{
                $$ = 1.0f;
                fprintf(stderr, "ERROR: division by zero\n");
            }
        }
    | expr_int '/' expr_float     { 
            if($3)
                $$ = (float)$1 / $3;
            else{
                $$ = 1.0f;
                fprintf(stderr, "ERROR: division by zero\n");
            }
        }
    | '(' expr_float ')'          { $$ = $2; }
    | '-' expr_float %prec UMINUS { $$ = -$2; }
    | '+' expr_float %prec UMINUS { $$ = $2; }
    | expr_float '^' expr_float   { $$ = powf($1,$3); }
    | expr_float '^' expr_int     { $$ = powf($1,(float)$3); }
    | expr_int   '^' expr_float   { $$ = powf((float)$1, $3); }
    | expr_int   '^' expr_int     { $$ = powf((float)$1, (float)$3); }
    ;

expr_int
    : NUMI
    | expr_int '+' expr_int   { $$ = $1 + $3; }
    | expr_int '-' expr_int   { $$ = $1 - $3; }
    | expr_int '*' expr_int   { $$ = $1 * $3; }
    | expr_int '/' expr_int   { 
            if($3)
                $$ = $1 / $3;
            else{
                $$ = 1;
                fprintf(stderr, "ERROR: division by zero\n");
            }
        }
    | '(' expr_int ')'          { $$ = $2; }
    | '-' expr_int %prec UMINUS { $$ = -$2; }
    | '+' expr_int %prec UMINUS { $$ = $2; }
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
