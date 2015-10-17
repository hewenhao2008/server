#include <assert.h>
#include <sys/epoll.h>
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
#include <pthread.h>
#include <stdlib.h>
#define _SIZE 256
#define WAIT 10
/* 用零初始化数据结构 */
#define ZEROMEMORY(o) memset((void *)&o, sizeof(o), 0)
/* 跳出错误处理结构 */
#define JUMP(o) if(o == -1){break; perror("error:");}
/* 将文件描述符设置为异步模式 */
#define ASYNCFD(fd) do{ \
int _flags = fcntl(fd, F_GETFL, 0); \
if(_flags != -1){ \
	_flags = fcntl(fd, F_SETFL, _flags | O_NONBLOCK); \
	assert(_flags != -1); \
}}while(0)

int ready_for_loop()
{
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
			addr.sin_port 			= htons(9000); // 监听端口9000
			addr.sin_addr.s_addr 	= INADDR_ANY;  // 绑定所有网卡
			
			if(!bind(sock, (struct sockaddr *)&addr, sizeof(struct sockaddr)))
			{
				listen(sock, WAIT);
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
							int size;
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
									
									/* 调试信息：打印远程主机信息 */
									#ifndef NDEBUG
									printf("\e[32m[accept new connection]: \"pda://%s:%d\"\e[0m\n", \
										inet_ntoa(host.sin_addr), ntohs(host.sin_port));
									#endif
								}
								else if((errno == EWOULDBLOCK) || (errno == EAGAIN))
								{
									break;
								}
								else
								{	
									exit(-1);
								}
							}
						}
						else if((list+i)->events & EPOLLRDHUP)
						{
							/* 关闭连接 */
							#ifndef NDEBUG
							printf("remote host disconnected...\n");
							#endif
						}
						else if((list+i)->events & EPOLLIN)
						{
							#ifndef NDEBUG
							//printf("cnt:%d\n", cnt);
							char data[1024];
							ZEROMEMORY(data);
							recv((list+i)->data.fd, data, 1024, 0);
							printf("数据:%s\n", data);
							#endif
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
