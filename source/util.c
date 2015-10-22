/*
	@Author: gatsby
	@Mail: i-careforu@foxmail.com
	@Comment: 实用的工具函数集合。
*/

#include <base.h>
#include <util.h>
#include <sys/sysinfo.h>

static HENV _h = NULL;
// 性能统计 - 可用于权重计算
// 获取系统全局的RTE
HENV get_rte(void)
{
	if(!_h)
	{
		init_rte();
	}
	return _h;
}

//　初始化系统全局RTE
HENV init_rte(void)
{
	if(!_h)
	{
		RTENV *rte = (RTENV *)malloc(sizeof(RTENV));
		assert(rte != NULL); // 在内存中分配数据结构 
		if(rte)
		{	
			memset((void *)rte, sizeof(RTENV), 0);
			// 获取系统启动时间
			struct sysinfo _info;	
			ZEROMEMORY(_info);
			sysinfo(&_info);
			rte->sys_alive = _info.uptime;
			rte->alive = 0;
			_h = rte;
			
			return (HENV)rte;
		}
		// 分配内存失败，退出
		abort();
	}
	
	return _h;
}

// 程序要使用的环境变量: SERVADDR=127.0.0.1:8000
void parse_env_vars()
{
	;//getenv(_env[0]);
}


