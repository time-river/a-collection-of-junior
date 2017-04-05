#include "libfun.h"
#include <stdio.h>

int main(void){
    unsigned int n;
    unsigned long long result;

    puts("the positive n.");
    scanf("%u", &n);

    result = f(n);
    switch(result){
        case 0:
            puts("Overflow.");
            break;
        default:
            printf("Result: %lld.\n", result);
            break;
    }
    return 0;
}
