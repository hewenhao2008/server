#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

// 解析命令行参数
extern char *optarg;
extern int optind;
extern int opterr;

// 守护程序
void daemonize(void)
{
	char *cwd = getcwd(NULL, 0);
	pid_t pid;
	if((pid = fork()) != -1)
	{
		if(pid > 0)
		{	
			// 父进程退出
			_exit(0);
		}
		
		setsid();
		umask(0);
		chdir(cwd);
		free(cwd);
		
		/* 关闭所有的文件描述符 */
		int fd;
		for(fd=0; fd<getdtablesize(); fd++)
		{
			close(fd);
		}
	}
	assert(pid != -1);
	return ;
}

// 显示程序帮助信息
void usage(void)
{	
	fprintf(stdout, "\n" \
		"***************************************\n"
		"  hope for your feedback.\n"
		"  @author: gatsby\n"
		"  @mail: i-careforu@foxmail.com\n"
		"**************************************\n\n"
		"usage: serv [-d] [-c <conf>].\n"
		"  -d daemon.\n"
		"  -c config.\n\n"
		);
	
	return ;
}

int main(int argc, char **argv)
{
	// 忽略错误参数
	opterr = 0;
	char c;
	while((c = getopt(argc, argv, "dc:h")) != -1)
	{
		switch(c)
		{
			case 'd': daemonize(); break;
			case 'c': break;
			case 'h': usage(); break;
			case '?': usage(); break;
		}
	}
	for(;;)
	{	
		sleep(2);
	}
	return 0;
}
