#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>

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
    char *name;
};

void hub(const struct command_t command);

#endif
