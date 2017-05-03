#include "common.h"

void hub(const struct command_t command){
    switch(command.stmt){
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
