#include <base.h>
#include <util.h>
#include <link.h>
#include <const.h>
#include <epoll.h>
#include <config.h>
#include <sys/stat.h>

// 解析命令行参数
extern char *optarg;
extern int optind;
extern int opterr;

// 守护程序
void daemonize(void)
{
	pid_t pid;
	if((pid = fork()) != -1)
	{
		umask(0);
		if(pid > 0)
		{	
			// 父进程退出
			_exit(0);
		}
		//　新会话
		setsid();
        int fd;
		if(!OPT_INT(getoption(NULL, NULL)) && (fd = open("/dev/null", O_RDWR)) != -1)
		{
			// 重定向标准句柄 stdin(0), stdout(1), stderr(2)
			dup2(fd, 0);
			dup2(fd, 1);
			dup2(fd, 2);
			
			close(fd);
		}
		
		// 屏蔽一些信号
		#ifdef DEBUG
		#endif
	}
	assert(pid != -1);
	return ;
}

// 显示程序帮助信息
NORETURN void usage(void)
{	
	fprintf(stdout, "\n" \
		"***************************************\n"
		"  hope for your feedback.\n"
		"  @author: gatsby\n"
		"  @mail: i-careforu@foxmail.com\n"
		"**************************************\n\n"
		"usage: serv [-d] [-c <conf>].\n"
		"  -v version.\n"
		"  -d daemon.\n"
		"  -c config.\n\n"
		);
	
    exit(0);
}

extern char **environ;

int main(int argc, char **argv)
{
    // 配置文件句柄
    HCONFIG __conf = NULL;
	// 忽略错误参数
	opterr = 0;
	char c;
	while((c = getopt(argc, argv, "dc:hv")) != -1)
	{
		switch(c)
		{
			case 'd': daemonize(); break;
			case 'v': version(); break;
			case 'h': usage(); break;
			case '?': usage(); break;
			case 'c': __conf = loadconf((const char *)optarg); break;
		}
	}
    // 加载环境变量中的配置，并且覆盖掉配置文件中相同选项
	int fd;
	if((fd = ready_for_loop(0, 9000)) != -1)
	{
		ioloop(fd);	
	}
	return 0;
}
