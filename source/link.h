#ifndef __LINK_H_
#define __LINK_H_

#include <base.h>

typedef void * HCHAIN; // 调用链句柄
typedef ulong (STDCALL *HANDLER)(ulong data); // 回调函数类型

HCHAIN chain(void);
int join(HCHAIN hchain, void *so, HANDLER cb);
int chain_call(const HCHAIN hchain, int data);

#endif
