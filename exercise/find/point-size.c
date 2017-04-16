#include <stdio.h>

size_t foo(int bar[]){
    return sizeof(bar);
}

int main(void){
    int a[4];
    printf("a: %zu\n", sizeof(a));
    printf("foo(a): %zd\n", foo(a));
    printf("sizeof(int *): %zu\n", sizeof(int *));
    return 0;
}

/*
me@me-U24:/tmp$ gcc test.c  -m32
test.c: In function ‘foo’:
test.c:4:18: warning: ‘sizeof’ on array function parameter ‘bar’ will return size of ‘int *’ [-Wsizeof-array-argument]
     return sizeof(bar);
                  ^
test.c:3:16: note: declared here
 size_t foo(int bar[]){
                ^
me@me-U24:/tmp$ ./a.out
a: 16
foo(a): 4
sizeof(int *): 4
*/

/*
me@me-U24:/tmp$ gcc test.c  -m64
test.c: In function ‘foo’:
test.c:4:18: warning: ‘sizeof’ on array function parameter ‘bar’ will return size of ‘int *’ [-Wsizeof-array-argument]
     return sizeof(bar);
                  ^
test.c:3:16: note: declared here
 size_t foo(int bar[]){
                ^
me@me-U24:/tmp$ ./a.out 
a: 16
foo(a): 8
sizeof(int *): 8
*/
