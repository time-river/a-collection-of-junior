#include "common.h"

/* 判断根目录是否存在
 *   若存在，判断是否有权限删除
 *     可以删除则删除
 *     不可以删除则报错推出
 * 创建根目录
 * 使用根目录
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
    use("use", "\0");

    return;
}

void create_drop(char *keyword, char *term, char *name){
    if(strcmp(keyword, "create") == 0 || strcmp(keyword, "CREATE") == 0){
        create(term, name);
    }
    else if(strcmp(keyword, "drop") == 0 || strcmp(keyword, "DROP") == 0){
        drop(term, name);
    }
    else{
        fprintf(stderr, "syntax error: %s\n", keyword);
    }

    return;
}

/* create directory or file according to term
 * 一个数据库一个文件夹, 一个表一个文件
 */
void create(char *term, char *name){
    int iresult;
    FILE *f = NULL;
    char file[BUFSIZ] = {0};

    if(strcmp(term, "database") == 0){
        sprintf(file, "%s/%s", ROOT, name);
        if(access(file, F_OK&07) == 0){ // file exists
            fprintf(stderr, "error: database %s exists.\n", name);
        }
        else{ // file not exists, create it
            iresult = mkdir(file, ~(S_IWGRP|S_IWOTH)&0777);
            if(iresult == -1){
                fprintf(stderr, "%s LINE %d: %s\n", __FILE__, __LINE__, strerror(errno));
                exit(EXIT_FAILURE);
            }
        }
    }
    else if(strcmp(term, "table") == 0){
        if(strcmp(current, ROOT) == 0){
            fprintf(stderr, "no database selected.\n");
        }
        else{
            sprintf(file, "%s/%s", current, name);
            if(access(file, F_OK&07) == 0){ // file exists
                fprintf(stderr, "error: table %s exists.\n", name);
            }
            else{ // file not exists, create it
                f = fopen(file, "w");
                if(f == NULL){
                    fprintf(stderr, "%s LINE %d: %s\n", __FILE__, __LINE__, strerror(errno));
                }
                else
                    fclose(f);
            }
        }
    }
    else{
        fprintf(stderr, "syntax error: %s\n", term);
    }

    return;
}

void drop(char *term, char *name){
    int iresult;
    char file[BUFSIZ] = {0};
    char command[BUFSIZ] = {0};

    if(strcmp(term, "database") == 0){
        snprintf(file, sizeof(file)-1, "%s/%s", ROOT, name);
        if(access(file, F_OK&07) != 0){
            fprintf(stderr, "error: database %s does not exist.\n", name);
        }
        else{
            snprintf(command, sizeof(command)-1, "rm -rf %s", file);
            if(system(command) != 0){
                fprintf(stderr, "%s LINE %d: %s\n", __FILE__, __LINE__, strerror(errno));
            }
        }
    }
    else if(strcmp(term, "table") == 0){
        if(strcmp(ROOT, current) == 0){
            fprintf(stderr, "no database selected.\n");
        }
        else{
            snprintf(file, sizeof(file)-1, "%s/%s", current, name);
            if(access(file, F_OK) == 0){
                snprintf(command, sizeof(command)-1, "rm -rf %s", file);
                if(system(command) != 0){
                    fprintf(stderr, "%s LINE %d: %s\n", __FILE__, __LINE__, strerror(errno));
                }
            }
            else{
                fprintf(stderr, "table %s does not exist.\n", name);
            }
        }
    }
    else{
        fprintf(stderr, "syntax error: %s\n", term);
    }

    return;
}
/* use database by means of a global variable */
void use(char *keyword, char *database){
    if(strcmp(keyword, "use") == 0 || strcmp(keyword, "USE") == 0){
        memset(current, 0, sizeof(current));
        snprintf(current, sizeof(current)-1, "%s/%s", ROOT, database);

        if(access(current, (R_OK|W_OK|X_OK)&07) != 0){
            fprintf(stderr, "%s, not exists or no permissions.", current);
        }
    }
    else{
        fprintf(stderr, "syntax error: %s\n", keyword);
    }
    return;
}

/* show directory or file according to term */
void show(char *keyword, char *term){
    char command[BUFSIZ] = {0};

    if(strcmp(keyword, "show") == 0 || strcmp(keyword, "SHOW") == 0){
        if(strcmp(term, "databases") == 0){
            snprintf(command, sizeof(command)-1, "ls -l %s | grep '^d' | awk  '{ print $9}'", ROOT);
            puts("\n------databases------");
            if(system(command) != 0){
                fprintf(stderr, "%s LINE %d: %s\n", __FILE__, __LINE__, strerror(errno));
            }
            puts("---------------------\n");
        }
        else if(strcmp(term, "tables") == 0){
            if(strcmp(current, ROOT) == 0){
                fprintf(stderr, "no database selected.\n");
            }
            else{
                snprintf(command, sizeof(command)-1, "ls -l %s | grep '^-' | awk  '{ print $9}'", current);
                puts("\n------tables------");
                if(system(command) != 0){
                    fprintf(stderr, "%s LINE %d: %s\n", __FILE__, __LINE__, strerror(errno));
                }
                puts("------------------\n");
            }
        }
        else{
            fprintf(stderr, "syntax error: %s %s\n", keyword, term);
        }
    }
    else{
        fprintf(stderr, "syntax error: %s\n", keyword);
    }

    return;
}
