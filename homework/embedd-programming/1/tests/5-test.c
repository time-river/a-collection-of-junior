#include <stdio.h>
#include "../src/lib.h"

int main(void){
    if(test_endian() == LITTLE)
        puts("Little Endian.");
    else
        puts("Big Endian.");

    return 0;
}
