#include <limits.h>

unsigned long long f(unsigned int n){
    unsigned long long result = 1;
    for(int i=1; i < n ; i++){
        result *= i;
        if(result > LLONG_MAX)
            return 0; // means overflow
    }
    return result;
}
