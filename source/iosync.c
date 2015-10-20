/*
	@Author: gatsby
	@Mail: i-careforu@foxmail.com
	@Comment:　本程序采用自行设计的线程同步方法，避免程序频繁陷入内核态，提高系统吞吐量。
	@Detail: 高效模型中系统锁不适用与线程同步，本系统采用hamming code实现了高性能的用
	户态多并发同步工具。hamming code请参考维基百科
	(https://en.wikipedia.org/wiki/Hamming_weight)
*/

#include <base.h>

/*	
	＠Explanation: 32位CPU采用的32位全加器，无法直接计算64位整形(int64)或者更高位
	数的数据(可采用x86的状态寄存器的AF与CF位实现)。本程序采用数组表示64位以上的数据。	
*/

static uint64_t _status;
// 常量表（用于计算汉明权）
const uint64_t m1  = 0x5555555555555555; //binary: 0101...
const uint64_t m2  = 0x3333333333333333; //binary: 00110011..
const uint64_t m4  = 0x0f0f0f0f0f0f0f0f; //binary:  4 zeros,  4 ones ...
const uint64_t m8  = 0x00ff00ff00ff00ff; //binary:  8 zeros,  8 ones ...
const uint64_t m16 = 0x0000ffff0000ffff; //binary: 16 zeros, 16 ones ...
const uint64_t m32 = 0x00000000ffffffff; //binary: 32 zeros, 32 ones
const uint64_t hff = 0xffffffffffffffff; //binary: all ones
const uint64_t h01 = 0x0101010101010101; //the sum of 256 to the power of 0,1,2,3...

/*
	@brief: 计算整形的汉明权(在具有快速乘法器上效率最高的实现方式，算法复杂度仅为常量级12)。
	@param: x - 整数。
*/
static int popcount(uint64_t x)
{
    x -= (x >> 1) & m1;
    x = (x & m2) + ((x >> 2) & m2);
    x = (x + (x >> 4)) & m4;
    
    return (x * h01)>>56;
}

/*
	@brief: 内联函数置位。
	@param: fd在epoll事件列表的索引。
*/
static inline void io_set(int index)
{
	_status = 1 >> index & _status;
}

/*
	@brief: 等待所有的线程就绪。
	@pram: ready - 要等待的fd数量。
	@pram: timeout - 超时时间（单位：毫秒）
*/
static inline int io_wait(int ready, int timeout)
{	
	return (popcount(_status) == ready) ? 0 : -1;
}

/*
	@brief: 内联函数复位。
	@param: 复位标识位。
*/
static inline void io_reset()
{
	_status = 0;
}
