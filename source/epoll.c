#include <base.h>

#define _SIZE 256
#define WAIT 10

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

/* 定时器回调函数 */
typedef void (STDCALL *cb_timer)(int);

/* 事件循环(只允许主线程调用该函数) */
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
									// rtenv->peer_cnt++;
									
									/* 调试信息：打印远程主机信息 */
									#ifndef NDEBUG
									printf("\e[32m[accept new connection]: \"peer://%s:%d\"\e[0m\n", \
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
							epoll_ctl(inst, EPOLL_CTL_DEL, (list+i)->data.fd, NULL);
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
