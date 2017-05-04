#include "common.h"

/* 创建文件夹 ROOT */
/* 检查是否存在
 *   是
 *     检查是否有 rwx 权限
 *       是
 *         删除
 *       否
 *         报错退出
 * 创建文件夹 ROOT
 */
void init(void){
    int iresult;
    char command[BUFSIZ];

    iresult = access(ROOT, F_OK&07);
    if(iresult == 0){
        iresult = access(ROOT, (R_OK|W_OK|X_OK)&07);
        if(iresult == 0){
            sprintf(command, "rm -rf %s", ROOT);
            if(system(command) != 0){
                fprintf(stderr, "%s LINE %d: %s\n", __FILE__, __LINE__, strerror(errno));
            }
        }
        else{
            fprintf(stderr, "%s, no permission.\n", ROOT);
            exit(EXIT_FAILURE);
        }
    }
    iresult = mkdir(ROOT, ~(S_IWGRP|S_IWOTH)&0777);
    if(iresult == -1){
        fprintf(stderr, "%s LINE %d: %s\n", __FILE__, __LINE__, strerror(errno));
        exit(EXIT_FAILURE);
    }

    database = NULL;
    return;
}

struct command_t *create_command(char *database_name){
    struct command_t *command = NULL;
    
    if(database_name == NULL){
        fprintf(stderr, "No database selected\n");
    }
    else{
        command = (struct command_t *)malloc(sizeof(struct command_t));
        if(command == NULL){
            fprintf(stderr, "Malloc error: %s\n", strerror(errno));
        }
        command->database_name = strdup(database_name);
        command->table_name = NULL;
        /* other init */
    }

    return command;
}

void free_command(struct command_t *command){
    free(command->database_name);
    free(command->table_name);
    free(command);

    return;
}
void hub(const struct command_t *command){
    switch(command->stmt){
        case CREATE_STMT:
            break;
        case DROP_STMT:
            break;
        case SHOW_STMT:
            break;
        case USE_STMT:
            use_stmt(command->database_name);
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

void use_stmt(const char *database_name){
    char path[BUFSIZ] = {0};
    snprintf(path, sizeof(path)-1, "%s/%s", ROOT, database_name);

    if(access(path, (R_OK|W_OK|X_OK)&07) != 0){
        fprintf(stderr, "Access denied for user to database '%s'\n", database_name);
    }
    else{
        free(database);
        database = strdup(path);
        fprintf(stdout, "Database changed\n");
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

void assign_column_type_list(struct command_t *command, struct column_type_t * column_type){

}

void assign_column_list(struct command_t *command, struct column_t *column){
}

void assign_column_value_list(struct command_t *command, struct column_value_t *column_value){
}

void assign_assign_expr_list(struct command_t *command, struct assign_expr_t assign_expr){

}

void assign_condition(){
}
