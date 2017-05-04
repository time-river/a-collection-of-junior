#ifndef COMMON_H
#define COMMON_H

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/queue.h>

#define ROOT "/tmp/sql"

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

struct command_t {
    enum stmt_t stmt;
    char *database_name;
    char *table_name;
    struct column_type_t *column_type;
    struct column_t *column_list;
    struct column_value_t *column_value_list;
    struct condition_t *condition;
};

enum datatype_t {
    FLOAT,
    INT,
    STRING
};

struct column_type_t {
    enum datatype_t datatype;
    char *column;
    void *data;
    SIMPLEQ_ENTRY(column_type_t) node;
};

struct column_t {
    char *column;
    SIMPLEQ_ENTRY(column_t) node;
};

struct column_value_t {
    enum datatype_t datatype;
    char *column;
    void *data;
    SIMPLEQ_ENTRY(column_value_t) node;
};

struct assign_expr_t {

};

struct condition_t {
    
};

void init(void);
struct command_t *create_command(char *database_name);
void free_command(struct command_t *command);
void hub(const struct command_t *command);
void use_stmt(const char *database_name);
void assign_database_name(struct command_t *command, char *database_name);
void assign_table_name(struct command_t *command, char *table_name);
void assign_column_type_list();
void assign_column_list();
void assign_column_value_list();
void assign_assign_expr_list();
void assign_condition();

extern char *database;
#endif
