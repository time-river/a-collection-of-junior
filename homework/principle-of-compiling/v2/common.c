#include "common.h"

void hub(const struct command_t *command){
    switch(command->stmt){
        case CREATE_STMT:
            break;
        case DROP_STMT:
            break;
        case SHOW_STMT:
            break;
        case USE_STMT:
            break;
        case EXIT_STMT:
            fprintf(stdout, "Bye bye~\n");
            exit(EXIT_SUCCESS);
            break;
        case SELECT_STMT:
            break;
        case INSERT_STMT:
            break;
        case UPDATE_STMT:
            break;
        case DELETE_STMT:
            break;
    }
    return;
}

void assign_database_name(struct command_t *command, char *database_name){
    if(command->database_name != NULL)
        free(command->database_name); // avoid memory leak
    command->database_name = strdup(database_name);

    return;
}

void assign_table_name(struct command_t *command, char *table_name){
    if(command->table_name != NULL)
        free(command->table_name); // avoid memory leak
    command->table_name = strdup(table_name);

    return;
}
