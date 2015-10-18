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

/*
#if defined(WIN32) || defined(_WIN32)
#define LINUX
#endif

#ifdef LINUX
#define STDCALL
#else
#define STDCALL __stdcall
#endif */

#define STDCALL

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

/* 功能性宏 */
// 安全删除指针
#define SAFE_DELETE(ptr) do{ \
if(ptr != NULL){ \
	free(ptr); ptr = NULL; \
}}while(0)
//　初始化结构体
#define ZEROMEMORY(o) memset((void *)&o, sizeof(o), 0)

/* 数据类型声明 */
typedef void *HENV;
typedef unsigned long ulong;

#endif

