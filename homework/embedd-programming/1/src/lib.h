#ifndef _LIB_H
#define _LIB_H
#endif

// 检测当前计算机是大端机还是小端机
union endian {
    int     num;
    char    ch[sizeof(int)];
};

enum endian_t {
    LITTLE,
    BIG
};

// 一个宏, 将 4 个 unsigned char 型变量合成一个 unsigned 型变量
typedef union {
    unsigned char   ch[4];
    unsigned int    num;
} uint_4;

// 将输入的一个无符号整数的第 i 位置 0 或 1
int replacebit(int number, unsigned int *result, int i, int flag);
// 检测一个无符号整数的第 i 位置是 0 还是 1
int locationtest(unsigned int number, int i);
// 在屏幕上输出一个整数的二进制表示
void inttob(int number, int length, char *result);
// 将一个 16 bits 整数转化为 BCD 码表示
unsigned int inttobcd(int num);
// 检测当前计算机是大端机还是小端机
int test_endian(void);

// 一个宏, 将 4 个 unsigned char 型变量合成一个 unsigned 型变量
#define MIXTURE(ch, number, n)  {\
    if(test_endian() == LITTLE){ \
        for(int i=1; i<= n; i++){ \
            number.ch[n-i] = ch[i-1]; \
        } \
    } \
    else { \
        for(int i=0; i< n; i++){ \
            number.ch[i] = ch[i]; \
        } \
    } \
}
