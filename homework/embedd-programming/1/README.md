相关函数位于 src 目录下，测试代码位于 tests 文件夹下. 

* 1-test.c -- 将输入的一个无符号整数的第 i 位置置 0 或置 1
* 2-test.c -- 检测一个无符号整数的第 i 位置是 0 还是 1
* 3-test.c -- 在屏幕上输出一个整数的二进制表示
* 4-test.c -- 将一个 16 bits 整数转化为 BCD 码表示(十六进制输出)
* 5-test.c -- 检测当前计算机是大端机还是小端机
* 6-test.c -- 编写一个 C 语言的宏函数，将 4 个 `unsigned char` 型变量合成一个 `usigned int` 类型变量

测试实例:

```bash
me@me-U24:~/homework/embedd/14030110047-付林/tests$ make
cc    -c -o ../src/lib.o ../src/lib.c
cc     1-test.c ../src/lib.o   -o 1-test
cc     2-test.c ../src/lib.o   -o 2-test
cc     3-test.c ../src/lib.o   -o 3-test
cc     4-test.c ../src/lib.o   -o 4-test
cc     5-test.c ../src/lib.o   -o 5-test
cc     6-test.c ../src/lib.o   -o 6-test
me@me-U24:~/homework/embedd/14030110047-付林/tests$ ./1-test 0 1 1
Original number is 0, after replacing, 1
me@me-U24:~/homework/embedd/14030110047-付林/tests$ ./2-test 0 1
bit is 0
me@me-U24:~/homework/embedd/14030110047-付林/tests$ ./3-test 0
0's binary is  0000 0000 0000 0000 0000 0000 0000 0000 
me@me-U24:~/homework/embedd/14030110047-付林/tests$ ./4-test 1
1's BCD code's binary is 0x1
me@me-U24:~/homework/embedd/14030110047-付林/tests$ ./5-test 
Little Endian.
me@me-U24:~/homework/embedd/14030110047-付林/tests$ ./6-test 1234
After combining, 1234 is 0x31323334
me@me-U24:~/homework/embedd/14030110047-付林/tests$ make clean
rm -rf 1-test 2-test 3-test 4-test 5-test 6-test ../src/lib.o
```
