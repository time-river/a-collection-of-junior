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
            fprintf(stderr, "ERROR: %s, no permission.\n", ROOT);
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

struct query_t *create_query(char *database_name){
    struct query_t *query = NULL;
    
    // 不需要指定数据库的操作 database_name == ROOT
    if(database_name == NULL){
        fprintf(stderr, "ERROR: No database selected\n");
    }
    else{
        query = (struct query_t *)malloc(sizeof(struct query_t));
        if(query == NULL){
            fprintf(stderr, "%s LINE %d: %s\n", __FILE__, __LINE__, strerror(errno));
        }
        query->database_name = strdup(database_name);
        query->table_name = NULL;
        query->column_type = NULL;
        query->column_value = NULL;
        query->condition = NULL;
    }

    return query;
}

void free_query(struct query_t *query){
    struct column_type_t *column_type = NULL;

    if(query != NULL){
        if(query->database_name != NULL)
            free(query->database_name);
        if(query->table_name != NULL)
            free(query->table_name);
        if(query->column_type != NULL){
            int i=0;
            while(query->column_type->next != query->column_type) {
                column_type = query->column_type;
                query->column_type = column_type->next;
                remque(column_type);
                free_column_type(column_type);
            }
            free_column_type(query->column_type);
        }
        free(query);
    }
    return;
}

void hub(const struct query_t *query){
    if(query != NULL)
        switch(query->stmt){
            case CREATE_STMT:
                create_stmt(query);
                break;
            case DROP_STMT:
                break;
            case SHOW_STMT:
                show_stmt(query);
                break;
            case USE_STMT:
                use_stmt(query);
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

void create_stmt(const struct query_t *query){
    char path[BUFSIZ] = {0};
    FILE *file = NULL;
    int  iresult;

    switch(query->create_opt){
        case DATABASE_OPT:
            snprintf(path, sizeof(path)-1, "%s/%s", ROOT, query->database_name);
            if(access(path, F_OK&07) == 0){ // file exists
                fprintf(stderr, "ERROR: Can't create database '%s'; database exists\n", query->database_name);
            }
            else{ // file not exists, create it
                iresult = mkdir(path, ~(S_IWGRP|S_IWOTH)&0777);
                if(iresult == -1)
                    fprintf(stderr, "%s LINE %d: %s\n", __FILE__, __LINE__, strerror(errno));
                else
                    fprintf(stdout, "Query OK, 1 row affected\n");
            }
            break;
        case TABLE_OPT:
            if(query->column_type == NULL)
                fprintf(stderr, "ERROR: A table must have at least 1 column\n");
            else{
                snprintf(path, sizeof(path)-1, "%s/%s/%s", ROOT, query->database_name, query->table_name);
                if(access(path, F_OK&07) == 0){ // file exists
                    fprintf(stderr, "ERROR: Can't create table '%s'; table exists\n", query->database_name);
                }
                else{
                    printf("database: %s\n", query->database_name);
                    printf("table: %s\n", query->table_name);
                    printf("path: %s\n", path);
                    file = fopen(path, "w");
                    if(file == NULL)
                        fprintf(stderr, "%s LINE %d: %s\n", __FILE__, __LINE__, strerror(errno));
                    else{
                        create_xml(query, file);
                        fclose(file);
                    }
                }
            }
            break;
    }
    return;
}

void drop_stmt(const struct query_t *query){
}

void show_stmt(const struct query_t *query){
    char path[BUFSIZ] = {0};
    char command[BUFSIZ] = {0};

    if(strcmp(query->database_name, ROOT) == 0){
        snprintf(path, sizeof(path)-1, "%s", ROOT);
        fprintf(stdout, "Database:\n");
        snprintf(command, sizeof(command)-1, "ls -l %s | grep '^d' | awk  '{ print $9 }'", path);
    }
    else{
        snprintf(path, sizeof(path)-1, "%s/%s", ROOT, query->database_name);
        fprintf(stdout, "Tables_in_'%s'\n", query->database_name);
        snprintf(command, sizeof(command)-1, "ls -l %s | grep '^-' | awk  '{ print $9 }'", path);
    }
    if(access(path, F_OK&07) == 0){
        printf("path: %s\n", path);
        if(system(command) != 0)
            fprintf(stderr, "%s LINE %d: %s\n", __FILE__, __LINE__, strerror(errno));
    }
    else
        fprintf(stderr, "ERROR: You have an error in your SQL syntax\n");
    return;
}

void use_stmt(const struct query_t *query){
    char path[BUFSIZ] = {0};
    snprintf(path, sizeof(path)-1, "%s/%s", ROOT, query->database_name);

    if(access(path, (R_OK|W_OK|X_OK)&07) != 0){
        fprintf(stderr, "ERROR: Access denied for user to database '%s'\n", query->database_name);
    }
    else{
        if(database != NULL)
            free(database);
        database = strdup(query->database_name);
        fprintf(stdout, "Database changed\n");
    }
    return;
}

void assign_create_opt(struct query_t *query, enum create_opt_t opt){
    query->create_opt = opt;

    return;
}

void assign_database_name(struct query_t *query, char *database_name){
    if(query->database_name != NULL)
        free(query->database_name); // avoid memory leak
    query->database_name = strdup(database_name);

    return;
}

void assign_table_name(struct query_t *query, char *table_name){
    if(query->table_name != NULL)
        free(query->table_name); // avoid memory leak
    query->table_name = strdup(table_name);

    return;
}

void assign_column_type_list(struct query_t *query, struct column_type_t * column_type){
    query->column_type = column_type;
    return;
}

void assign_column_list(struct query_t *query, struct column_t *column){
    query->column = column;
    return;
}

void assign_column_value_list(struct query_t *query, struct column_value_t *column_value){
    query->column_value = column_value;
    return;
}

void assign_assign_expr_list(struct query_t *query, struct assign_expr_t assign_expr){

}

void assign_condition(){
}

/* circular queue
 * a b c d e
 * e ->next d ->next c ->next b ->next a ->next e
 * e ->prev a ->prev b ->prev c ->prev d ->prev e
 */
struct column_type_t *create_column_type(char *column, char *datatype){
    struct column_type_t *node = NULL;
    char *str = NULL;

    node = (struct column_type_t *)malloc(sizeof(struct column_type_t));
    if(node == NULL){
        fprintf(stderr, "%s LINE %d: %s\n", __FILE__, __LINE__, strerror(errno));
    }
    else{
        node->prev = node;
        node->next = node;
        node->column = strdup(column);
        str = strdup(datatype);
        for(int i = 0; str[i] != '\0'; i++) // convert all to tolower
            str[i] = tolower(str[i]);
        if(strcmp(str, "int") == 0)
            node->datatype = INT;
        else if(strcmp(str, "float") == 0)
            node->datatype = FLOAT;
        else if(strcmp(str, "string") == 0)
            node->datatype = STRING;
        free(str);
    }

    return node;
}

void free_column_type(struct column_type_t *node){
    if(node != NULL){
        if(node->column != NULL)
            free(node->column);
        free(node);
    }
    return;
}

struct column_t *create_column(char *column){
    struct column_t *node = NULL;

    node = (struct column_t *)malloc(sizeof(struct column_t));
    if(node == NULL){
        fprintf(stderr, "%s LINE %d: %s\n", __FILE__, __LINE__, strerror(errno));
    }
    else{
        node->prev = node;
        node->next = node;
        node->column = strdup(column);
    }

    return node;
}

void free_column(struct column_t *node){
    if(node != NULL){
        if(node->column != NULL)
            free(node->column);
        free(node);
    }
    return;
}

struct column_value_t *create_column_value(char *column, void *value_ptr, enum datatype_t datatype){
    struct column_value_t *node = NULL;

    node = (struct column_value_t *)malloc(sizeof(struct column_value_t));
    if(node == NULL)
            fprintf(stderr, "%s LINE %d: %s\n", __FILE__, __LINE__, strerror(errno));
    else{
        node->prev = node;
        node->next = node;
        node->datatype = datatype;
        node->column = strdup(column);
        switch(datatype){
            case FLOAT:
                node->value.numf = *((float *)value_ptr);
                break;
            case INT:
                node->value.numi = *((int *)value_ptr);
                break;
            case STRING:
                node->value.string = strdup((char *)value_ptr);
                break;
        }
    }
    return node;
}

void free_column_value(struct column_value_t *node){
    if(node != NULL){
        if(node->column != NULL)
            free(node->column);
        if(node->datatype == STRING && node->value.string != NULL)
            free(node->value.string);
        free(node);
    }
}
