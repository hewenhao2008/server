#ifndef __EPOLL_H_
#define __EPOLL_H_

/* 定时器回调函数 - 主要用于维护心跳 */
typedef void (STDCALL *cb_timer)(int);
/* 初始化连接 */
int ready_for_loop(unsigned int ip, unsigned int port);
/* 事件循环 */
int ioloop(int sock);

#endif
