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

#define ROOT "/tmp/sql"

char  current[BUFSIZ];

void init(void);
void create_drop(char *keyword, char *term, char *name);
void create(char *term, char *name);
void drop(char *term, char *name);
void show(char *keyword, char *term);
void use(char *keyword, char *database);
#endif
