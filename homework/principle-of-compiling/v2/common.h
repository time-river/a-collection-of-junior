#ifndef COMMON_H
#define COMMON_H

#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <search.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "xml.h"

#define ROOT "/tmp/river-sql"

enum stmt_t{
    CREATE_STMT,
    DROP_STMT,
    SHOW_STMT,
    USE_STMT,
    EXIT_STMT,
    SELECT_STMT,
    INSERT_STMT,
    UPDATE_STMT,
    DELETE_STMT
};

enum create_opt_t {
    DATABASE_OPT,
    TABLE_OPT
};

struct query_t {
    enum stmt_t stmt;
    enum create_opt_t create_opt;
    char *database_name;
    char *table_name;
    struct column_type_t *column_type;
    struct column_t *column;
    struct column_value_t *column_value;
    struct condition_t *condition;
};

enum datatype_t {
    FLOAT,
    INT,
    STRING
};

struct column_type_t {
    struct column_type_t *prev;
    struct column_type_t *next;
    char *column;
    enum datatype_t datatype;
};

struct column_t {
    struct column_t *prev;
    struct column_t *next;
    char *column;
};

union value_t {
    int numi;
    float numf;
    char *string;
};

struct column_value_t {
    struct column_value_t *prev;
    struct column_value_t *next;
    enum datatype_t datatype;
    char *column;
    union value_t value;
};

struct assign_expr_t {

};

struct condition_t {
    
};

void init(void);
struct query_t *create_query(char *database_name);
void free_query(struct query_t *query);
void hub(const struct query_t *query);
void create_stmt(const struct query_t *query);
void show_stmt(const struct query_t *query);
void use_stmt(const struct query_t *query);
void assign_create_opt(struct query_t *query, enum create_opt_t opt);
void assign_database_name(struct query_t *query, char *database_name);
void assign_table_name(struct query_t *query, char *table_name);
void assign_column_type_list();
void assign_column_list();
void assign_column_value_list();
void assign_assign_expr_list();
void assign_condition();

struct column_type_t *create_column_type(char *column, char *datatype);
void free_column_type(struct column_type_t *node);
struct column_t *create_column(char *column);
void free_column(struct column_t *node);
struct column_value_t *create_column_value(char *column, void *value_ptr, enum datatype_t datatype);
void free_column_value(struct column_value_t *node);

extern char *database;
#endif
