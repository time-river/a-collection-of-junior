#ifndef _LIB_H
#include "lib.h"
#endif

// 将输入的一个无符号整数的第 i 位置 0 或 1
int replacebit(int number, unsigned int *result, int i, int flag){
    unsigned int mask;

    if(i > 0 && i < 256)
        mask = 1U << (i-1);
    else{
        return -1;
    }

    switch(flag){
        case 0:
            *result = number & (~mask);
            break;
        case 1:
            *result = number | mask;
            break;
        default:
            return -1;
    }

    return 0;
}

// 检测一个无符号整数的第 i 位置是 0 还是 1
int locationtest(unsigned int number, int i){
    if(i < 0 || i > 32)
        return -1;

	unsigned int mask, result;

	mask = 1U << (i-1);
	result = number & mask;

	return result == 0 ? 0 : 1;
}

// 在屏幕上输出一个整数的二进制表示
void inttob(int number, int length, char *result){

	unsigned long long mask = 1LU << length; // 0x1 0000 0000;

	while(mask >>= 1){
		*result++ = !!(mask & number) + '0'; // the !! ensure that we are adding either a 0 or a 1 to '0' 
	}

	return;
}

// 将一个 16 bits 整数转化为 BCD 码表示
unsigned int inttobcd(int num){
	unsigned int result = 0U;

	while(num > 0){
		result <<= 4;
		result |= ((num%10) & 0xff);
		num /= 10;
	}

	return result;
}

// 检测当前计算机是大端机还是小端机
int test_endian(void){
	union endian test;

	test.num = 0x12345678;

	if(test.ch[0] == 0x1)
		return BIG;
	else
		return LITTLE;
}
