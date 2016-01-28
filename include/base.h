/* 
	@Author: gatsby
	@Mail: i-careforu＠foxmail.com
    ＠Comment: 基本的数据结构与宏定义。
*/

#ifndef __BASE_H
#define __BASE_H

/* 如果未定义DEBUG宏或者_DEBUG，则定义NDEBUG（assert根据此宏决定是否生成代码） */
#if !defined(DEBUG) && !defined(_DEBUG)
#define NDEBUG
#endif

/* 结构体内存对齐大小 */
/* @Note: 如果定义了_X86_则结构体默认按照四字节对齐 */
#if defined(_X86_)
#define ALIGN 0x04
#define SHIFT 0x02
/* @Note: 如果定义了_X64_则结构体默认按照八字节对齐 */
#elif defined(_X64_)
#define ALIGN 0x08
#define SHIFT 0x03
#endif

/* windows平台下报错 */
#if defined(WIN32) || defined(_WIN32)
#error("only released under linux/unix.")
/* @Note: 标准调用约定(规定了参数传递、参数入栈顺序、栈平衡的规则) */
/* @Note: 暂时未实现windows平台所以默认都为空 */
// #define STDCALL __stdcall
// #define CALLBACK STDCALL
#endif

/* 函数调用约定 */
#define STDCALL
#define PASCAL
#define CDEL 
#define CALLBACK STDCALL

/* GCC中修饰不返回的函数特性 */
#if defined(__GNUC__)
#define NORETURN __attribute__((noreturn))
#else
#define NORETURN
#endif

/* 功能性宏定义 */

/* 进入错误处理结构 */
#define ENTER() do{

/* 离开错误处理结构 */
#define LEAVE() }while(0)

/* 判断是否出错 */
/* @Note: JUDGE宏必须在ENTER与LEAVE宏之间 */
#define JUDGE(x) if(x == -1) break

/* 安全释放内存 */
/* @Note: 会将野指针赋值NULL */
#define SAFE_DELETE(ptr) \
do{ \
    if(ptr != NULL){ \
	    free(ptr); \
        ptr = NULL; \
}}while(0)

/* 初始化结构体 */
/* @Note: 将结构体的所有成员全部初始为0(typeof是gcc扩展的关键字) */
#define ZEROMEMORY(o) memset((void *)&o, sizeof(typeof(o)), 0)

// 将文件描述符设置为异步模式
#define ASYNCFD(fd) do{ \
int _flags = fcntl(fd, F_GETFL, 0); \
if(_flags != -1){ \
	_flags = fcntl(fd, F_SETFL, _flags | O_NONBLOCK); \
	assert(_flags != -1); \
}}while(0)
// 跳出错误处理结构
#define JUMP(o) if(o == -1){break; perror("error:");}


/* 数据类型声明 */
typedef void *HENV;
typedef unsigned long ulong;

/* 包含基本的头文件 */
#include <assert.h>
#include <sys/epoll.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <pthread.h>

#endif

