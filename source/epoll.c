/*
	@Author: wanglw
	@Mail: i-careforu@foxmail.com
	@Comment: 记录epoll技术的高效IO模块，为非线程安全的，所由api均必须由主线程来调用。
*/

#include <base.h>
#include <util.h>
#include <sys/syscall.h>

#define _SIZE 256
#define WAIT 10

/* linux内核默认tcp缓冲区大小 */
extern size_t def_buf_size;

/* 保存指向系统运行环境数据结构的指针 */
static RTENV *rte;

int ready_for_loop(unsigned int ip, unsigned int port)
{
	rte = (RTENV *)get_rte();
	assert(rte != NULL);
	
	int sock = -1;
	if((sock = socket(AF_INET, SOCK_STREAM, 0)) != -1)
	{	
		ASYNCFD(sock); // 异步IO
		do
		{
			struct sockaddr_in addr;
			ZEROMEMORY(addr);
			
			// 绑定本地地址
			addr.sin_family 		= AF_INET;
			addr.sin_port 			= htons(port); // 监听端口9000
			addr.sin_addr.s_addr 	= (ip == 0) ? INADDR_ANY : ip;  // 绑定所有网卡
			
			/* 设置系统默认缓冲区大小 */
			int _res;
			_res = setsockopt(sock, SOL_SOCKET, SO_RCVBUF, (char *)&def_buf_size, sizeof(socklen_t));
			assert(_res != -1);
			_res = setsockopt(sock, SOL_SOCKET, SO_SNDBUF, (char *)&def_buf_size, sizeof(socklen_t));
			assert(_res != -1);
			
			int _r = bind(sock, (struct sockaddr *)&addr, \
					sizeof(struct sockaddr));
			
			/* 绑定失败可能是由无权限或者端口已被绑定造成的 */
			if(!_r && !listen(sock, WAIT))
			{	
				return sock;
			}
			
		}while(0);
		
		perror("ready_for_loop:");
		close(sock);
	}
	return -1;
}
 
/* 事件循环 */
int ioloop(int sock)
{	
	/* 事件循环仅在主线程中可调用 */
	#ifdef DEBUG
	pid_t pid, tid;
	assert(((pid = getpid()) != -1) \
		&& ((tid = syscall(SYS_gettid)) != -1) && (pid == tid));
	#endif
	
	int inst = -1;
	if((inst = epoll_create(_SIZE)) != -1)
	{
		assert(sock != -1);
		int code;
		do
		{	/* 注册感兴趣的事件 */
			struct epoll_event _e;
			ZEROMEMORY(_e);
			_e.events = EPOLLIN | EPOLLET;
			_e.data.fd = sock;
			
			code = epoll_ctl(inst, EPOLL_CTL_ADD, sock, &_e);
			JUMP(code);
			
			struct epoll_event list[_SIZE];
			ZEROMEMORY(list);
			
			/* 事件循环 */
			/* 用epoll的主循环做一个定时器(用最小堆实现) */
			for(;;)
			{
				int cnt;
				if((cnt = epoll_wait(inst, list, _SIZE, 1000)))
				{
					int i;
					for(i=0; i<cnt; i++)
					{
						if((list+i)->data.fd == sock)
						{
							int peer; // 对端FD
							socklen_t size;
							struct sockaddr_in host;
							ZEROMEMORY(host);
							
							for(;;)
							{	/* 循环接受新的连接 */
								peer = accept(sock, (struct sockaddr *)&host, &size);
								if(peer != -1)
								{
									ASYNCFD(peer);
									_e.events = EPOLLIN || EPOLLOUT || EPOLLRDHUP;
									_e.data.fd = peer;
									epoll_ctl(inst, EPOLL_CTL_ADD, peer, &_e);
									
									/* 运行时环境连接计数器加1 */
									rte->peercnts++;
									#ifdef DEBUG
									printf("\e[32m[peer-count]: %d\e[0m\n", rte->peercnts);
									#endif
									
									/* 调试信息：打印远程主机信息 */
									#ifndef NDEBUG
									printf("\e[32m[accept new connection]: \"peer://%s:%d\"\e[0m\n", \
										inet_ntoa(host.sin_addr), ntohs(host.sin_port));
									#endif
								}
								else if((errno == EWOULDBLOCK) || (errno == EAGAIN))
								{
									#ifdef DEBUG
									printf("[accept]: compelte.\n");
									#endif
									break;
								}
								else
								{	
									/* 建立连接出错，记录日志 */
									/* 一定时间内频繁出错，则生成core文件供调试 */
								}
							}
						}
						else if((list+i)->events & EPOLLRDHUP)
						{
							/* 关闭连接 */
							rte->peercnts--;
							epoll_ctl(inst, EPOLL_CTL_DEL, (list+i)->data.fd, NULL);
							#ifdef DEBUG
							printf("\e[32m[peer-count]: %d\e[0m\n", rte->peercnts);
							#endif
							continue;
							
						}
						else if((list+i)->events & EPOLLIN)
						{
							/* 分发至各个CPU核上处理数据 */
							//int fd = (list+i)->data.fd;
							//int _index = i;
						}
						else
						{	
							
						}
					}
				}
			}
		}while(0);
	}
	return 0;
}
