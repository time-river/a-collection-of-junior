#ifndef COMMON_H
#define COMMON_H

#include <math.h>
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
    struct value_t *value;
    struct assign_expr_t *assign_expr;
    struct condition_expr_t *condition;
};

enum datatype_t {
    FLOAT = 0,
    INT = 1,
    STRING = 2
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

union _value_t {
    int numi;
    float numf;
    char *string;
};

struct value_t {
    struct value_t *prev;
    struct value_t *next;
    enum datatype_t datatype;
    union _value_t value;
};

struct assign_expr_t {
    struct assign_expr_t *prev;
    struct assign_expr_t *next;
    char *column;
    enum datatype_t datatype;
    union _value_t value;
};


void init(void);
struct query_t *create_query(char *database_name);
void free_query(struct query_t *query);
void hub(const struct query_t *query);

void create_stmt(const struct query_t *query);
void drop_stmt(const struct query_t *query);
void show_stmt(const struct query_t *query);
void use_stmt(const struct query_t *query);
void select_stmt(const struct query_t *query);
void insert_stmt(const struct query_t *query);
void update_stmt(const struct query_t *query);
void delete_stmt(const struct query_t *query);

void assign_create_opt(struct query_t *query, enum create_opt_t opt);
void assign_database_name(struct query_t *query, char *database_name);
void assign_table_name(struct query_t *query, char *table_name);
void assign_column_type_list(struct query_t *query, struct column_type_t * column_type);
void assign_column_list(struct query_t *query, struct column_t *column);
void assign_value_list(struct query_t *query, struct value_t *value);
void assign_assign_expr_list(struct query_t *query, struct assign_expr_t *assign_expr);

void assign_value(union _value_t *node, void *value_ptr, enum datatype_t datatype);

struct column_type_t *create_column_type(const char *column, char *datatype);
void free_column_type(struct column_type_t *node);
void free_column_type_list(struct column_type_t *node);

struct column_t *create_column(char *column);
void free_column(struct column_t *node);
void free_column_list(struct column_t *node);

struct value_t *create_value(void *value_ptr, enum datatype_t datatype);
void free_value(struct value_t *node);
void free_value_list(struct value_t *node);

struct assign_expr_t *create_assign_expr(char *column, void *value_ptr, enum datatype_t datatype);
void free_assign_expr(struct assign_expr_t *node);
void free_assign_expr_list(struct assign_expr_t *node);

extern char *database;
extern int nextinstr;

#include "xml.h"
#endif
