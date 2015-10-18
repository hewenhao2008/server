/*
	@Author: gatsby
	@Mail: i-careforu@foxmail.com
	@Comment: 实用的工具函数集合。
*/

#include <base.h>
#include <sys/sysinfo.h>

static HENV _h = NULL;

typedef struct __RTENV
{
	ulong sys_alive;
	ulong alive;
}RTENV;


// 获取系统全局的RTE
HENV get_rte(void)
{
	assert(_h != NULL);
	return _h;
}

//　初始化系统全局RTE
HENV init_rte(void)
{
	if(!_h)
	{
		RTENV *rte = (RTENV *)malloc(sizeof(RTENV));
		assert(rte != NULL); // 
		if(!rte)
		{	
			memset((void *)rte, sizeof(RTENV), 0);
			// 获取系统启动时间
			struct sysinfo _info;	
			ZEROMEMORY(_info);
			sysinfo(&_info);
			rte->sys_alive = _info.uptime;
			rte->alive = 0;
			
			return (HENV)rte;
		}
		// 分配内存失败，退出
		abort();
	}
	
	return _h;
}



