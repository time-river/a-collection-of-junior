#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../src/lib.h"

#define LENGTH 4

int main(int argc, char *argv[]){
    if(argc != 2){
        fprintf(stderr, "Usage: [unsigned char[%d]].\n", LENGTH);
        return -1;
    }
    
    uint_4 number;
    char ch[LENGTH+1] = {0};
    strncpy(ch, argv[1], LENGTH);

    if(strlen(ch) != LENGTH){
        fprintf(stderr, "Error.\n");
        return -1;
    }

    MIXTURE(ch, number, LENGTH);
    printf("After combining, %s is 0x%x\n", ch, number.num);
    
    return 0;
}
