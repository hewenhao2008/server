/*
	@Author: gatsby
	@Mail: i-careforu@foxmail.com
	@Comment: 实用的工具函数集合。
*/

#include <base.h>
#include <util.h>
#include <sys/sysinfo.h>

static HENV _h = NULL;

/* 获取系统全局rte */
/* @Note: 运行时环境rte(runtime environment) */
HENV get_rte(void)
{
	if(!_h)
	{
		init_rte();
	}
	return _h;
}

/* 初始化全局rte */
/* @Note: 返回rte句柄 */
HENV init_rte(void)
{
	if(!_h)
	{
		RTENV *rte = (RTENV *)malloc(sizeof(RTENV));
		assert(rte != NULL);
		if(rte)
		{	
			memset((void *)rte, sizeof(RTENV), 0);
			/* 获取系统启动时间 */
			struct sysinfo _info;	
			ZEROMEMORY(_info);
			sysinfo(&_info);
			rte->sys_alive = _info.uptime;
			rte->alive = 0;
			_h = rte;
			
			return (HENV)rte;
		}
		/* 系统分配内存失败，异常退出 */
		abort();
	}
	
	return _h;
}

/* 配置选项的值 */
typedef union
{
    int data;
    char *pdata;
}value;

unsigned int host, port;

/* 解析环境变量 */
/* @Note: 配置文件的优先级为，命令行参数 > 环境变量 > 配置文件 */
int parsenv()
{
	return 0;
}
