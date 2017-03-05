#include <stdio.h>
#include <stdlib.h>
#include "../src/lib.h"

int main(int argc, char *argv[]){
    if(argc != 3){
        fprintf(stderr, "Usage: %s [integer] [location].\n", argv[0]);
        return -1;
    }

    int result;
    int number  = atoi(argv[1]);
    int i       = atoi(argv[2]);

    result = locationtest(number, i);

    if(result != -1)
        fprintf(stdout, "bit is %d\n", result);
    else
        fprintf(stderr, "Error.\n");

    return 0;
}
