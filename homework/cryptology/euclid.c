/* expand euclid algorithm:  <08-07-17, river> */

#include <stdio.h>

struct result_t {
    int d;
    int x;
    int y;
};

struct result_t expand_euclid(int a, int b);

int main(void){
    int a, b;
    struct result_t result;

    while(fscanf(stdin, "%d %d", &a, &b) != EOF){
        result = expand_euclid(a, b);
        fprintf(stdout, "d: %d  x: %d  y: %d\n", result.d, result.x, result.y);   
    }
    return 0;
}

struct result_t expand_euclid(int a, int b){
    static int x[2] = {1, 0};
    static int y[2] = {0, 1};

    int r, q, x_n, y_n;

    if(b == 0){
        struct result_t result = {
            .d = a,
            .x = x[0],
            .y = y[0]
        };
        return result;
    }
    r = a % b;
    q = a / b;
    x_n = x[0] - q * x[1];
    y_n = y[0] - q * y[1];
    x[0] = x[1];
    y[0] = y[1];
    x[1] = x_n;
    y[1] = y_n;

    printf("x: %d y: %d\n", x[1], y[1]);
    return expand_euclid(b, r);
}
