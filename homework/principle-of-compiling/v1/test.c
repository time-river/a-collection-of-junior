#include <stdio.h>
#include "common.h"

#define DEBUG

int main(int argc, char *argv[]){
    init();
    create_drop("create", "database", "test");
    create_drop("create", "table", "test");
    use("use", "test");
    create_drop("create", "table", "test");
    show("show", "databases");
    show("show", "tables");
    create_drop("drop", "table", "test");
    show("show", "tables");
    create_drop("drop", "database", "test");
    show("show", "databases");

    return 0;
}
