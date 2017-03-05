#include <stdio.h>
#include <stdlib.h>
#include "../src/lib.h"

int main(int argc, char *argv[]){
    if(argc != 2){
        fprintf(stderr, "Usage: %s [integer].\n", argv[0]);
        return -1;
    }

    int number = atoi(argv[1]);
    if(number < 0){
        fprintf(stderr, "Error, BCD code must be positive number.\n");
        return -1;
    }

    unsigned int result = inttobcd(number);
    printf("%d's BCD code's binary is 0x%x\n", number, result);

    return 0;
}
