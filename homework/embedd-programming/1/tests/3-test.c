#include <stdio.h>
#include <stdlib.h>
#include "../src/lib.h"

#define LENGTH sizeof(int)*8

int main(int argc, char *argv[]){
    if(argc != 2){
        fprintf(stderr, "Usage: %s [integer].\n", argv[0]);
        return -1;
    }

    int number = atoi(argv[1]);
    char result[LENGTH+1] = {0};

    inttob(number, LENGTH, result);

    printf("%d's binary is ", number);
    for(int i=0; i<=LENGTH; i++){
        if(i%4 == 0)
            putchar(' ');
        putchar(result[i]);
    }
    putchar('\n');

    return 0;
}
