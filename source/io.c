/*
    @Author: gatsby
    @Data: 2015-10-22
    @Mail: i-careforu@foxmail.com
    @Comment: 网络IO同本地IO的实现。
*/

#include <base.h>

/* @Detail:　为了性能，应用层协议采用固定首部提升性能（算法一定的情况下，性能与存储空
间总是成反比），类比lua字节码与x86机器码，lua字节码为固定长度，运行性能高，但占用空间
大，x86机器码采用哈夫曼编码，空间占用小，但性能相对降低。 */

/* TLS-KEY */
static pthread_key_t key;

/* 回调函数 */
void CALLBACK cb_destructor(void *_pkey)
{
    #ifdef DEBUG
    #endif
    return ;
}

/* 设置线程默认接收（写入）数据的大小@内核缓冲区默认大小8KB */
/* @Note: 采用线程局部存储(TLS)，所有api均是线程安全的(thread-safe)。 */
int setdef(size_t size)
{
    int _res;
    if((_res = pthread_key_create(&key, cb_destructor)) != -1)
    {
        _res = pthread_setspecific(key, (void *)size);
        #ifdef DEBUG
        #endif
    }
    return _res;
}

/* 高效内存拷贝函数的实现 */
/* @Note: 频繁的数据拷贝是服务器的性能瓶颈之一，本文件提供了基于汇编的高效实现方式定义
为内联函数减少函数调用的开销（参数、返回地址、寄存器入栈出栈，指令跳转降低CPU Cache命中率的问题）。 */
extern inline void *_memcpy(const void *src, void *dst, size_t size)
{
    /* AT&T汇编语言 */
   __asm__ __volatile__(
        ":::memory"
    );

   return dst;
}

extern inline void *_zero(void *src, size_t size)
{
    /* AT&T汇编语言 */
    __asm__ __volatile(
        "cli;"
        "rep stosd;"
        ::"s"(src), "c"(size << ALIGN)
        :"%%ecx", "%%esi"
    );

    return src;
}

/* 读socket@一直读直至内核缓冲区没数据为止 */
/* ＠Note: 用户态陷入系统态涉及大量数据拷贝，是性能瓶颈之一，所以要减少系统调用 */
int rdsock(int sock, char *buffer)
{
    // int _res, n = 0; // 读取的字节数
    return 0;
}

/* 写socket@一直写直至无数据 */
/* @Note: 同rdsock函数一致 */
int wrsock(int sock, char *buffer, int bytes)
{
    // int n; //　写入的字节数    
    return 0;
}
