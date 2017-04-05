利用 C 语言实现阶乘函数 `f(n) = n!`
1. 将 `f(n)` 封装到静态库中，然后再编写另外一个 C 程序调用 `f(n)`
2. 将 `f(n)` 封装到动态库中，然后再编写另外一个 C 程序调用 `f(n)`

测试:

```bash
me@me-U24:~/git/a-collection-of-junior/homework/embedd-programming/2/src$ ls
call.c  libfun.c  libfun.h  Makefile
me@me-U24:~/git/a-collection-of-junior/homework/embedd-programming/2/src$ make
cc    -c -o call.o call.c
cc    -c -o libfun.o libfun.c
cc -o static call.o libfun.o 
cc -fPIC -shared -o libfun.so libfun.o
cc -o shared call.c -L. -lfun
----------------------------test--------------------------------
/home/me/git/a-collection-of-junior/homework/embedd-programming/2/src/static
the positive n.
4
Result: 6.
/home/me/git/a-collection-of-junior/homework/embedd-programming/2/src/shared
the positive n.
4
Result: 6.
rm -rf *.o static shared libfun.so
```
