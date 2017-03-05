#include <stdio.h>
#include <stdlib.h>
#include "../src/lib.h"

int main(int argc, char *argv[]){
    if(argc != 4){
        fprintf(stderr, "Usage: %s [integer] [location] [flag].\n", argv[0]);
        return -1;
    }

    unsigned int result;
    int number  = atoi(argv[1]);
    int i       = atoi(argv[2]);
    int flag    = atoi(argv[3]);
    if(replacebit(number, &result, i, flag) == 0)
        fprintf(stdout, "Original number is %d, after replacing, %u\n", number, result);
    else
        fprintf(stderr, "Error.\n");
    return 0;
}
