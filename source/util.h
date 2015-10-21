#ifndef __UTIL_H_
#define __UTIL_H_

typedef struct __RTENV
{
	ulong sys_alive;	// OS运行时间
	ulong alive;		// 系统持续运行时间
	int peercnts;		// 当前连接的客户端数
	ulong tcnts;		// 线程数量（等于CPU核数）
}RTENV;

HENV get_rte(void);
HENV init_rte(void);

#endif
