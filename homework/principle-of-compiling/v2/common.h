#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

#define list char

struct command_t {
    enum stmt_t stmt;
    char *database_name;
    char *table_name;
    list *column_type;
    list *column_list;
    list *value_column_list;
    list *condition;
};

void hub(const struct command_t *command);
void assign_database_name(struct command_t *command, char *database_name);
void assign_table_name(struct command_t *command, char *table_name);
void assign_column_type_list();
void assign_column_list();
void assign_value_column_list();
void assign_condition();

#endif
