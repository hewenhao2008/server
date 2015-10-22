/*
    @Author: gatsby
    @Data: 2015-10-22
    @Mail: i-careforu@foxmail.com
    @Comment: 网络IO同本地IO的实现。
*/

#include <base.h>

/* @Detail:　为了性能，应用层协议采用固定首部提升性能（算法一定的情况下，性能与存储空间总是成反比），类比lua字节码与x86机器码，lua字节码为固定长度，运行性能高，但占用空间大，x86机器码采用哈夫曼编码，空间占用小，但性能相对降低。 */

/* 设置线程默认向内存存取数据的大小@内核缓冲区默认大小8KB */
/* @Note: 采用线程局部存储(TLS)，所有api均是线程安全的(thread-safe)。 */
int setdef(size_t size)
{
    return 0;
}

/* 高效内存拷贝函数的实现 */
/* @Note: 频繁的数据拷贝是服务器的性能瓶颈之一，本文件提供了基于汇编的高效实现方式 */
/* @Note: 定义为内联函数减少函数调用的开销（参数、返回地址、寄存器入栈出栈，指令跳转降低
CPU Cache命中率的问题）。 */
extern inline void *_memcpy(const void *src, void *dst, size_t size)
{
   #ifdef _X86_
   __asm__ __volatile__(
        /* 汇编语言 */
   );
   #endif 
   return NULL;
}

/* 读socket@一直读直至内核缓冲区没数据为止 */
/* ＠Note: 用户态陷入系统态涉及大量数据拷贝，是性能瓶颈之一，所以要减少系统调用 */
int rdsock(int sock, char *buffer)
{
    return 0;
}

/* 写socket@一直写直至无数据 */
/* @Note: 同rdsock函数一致 */
int wrsock(int sock, char *buffer, int bytes)
{
    return 0;
}
