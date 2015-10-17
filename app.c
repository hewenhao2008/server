#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

// 解析命令行参数
extern char *optarg;
extern int optind;
extern int opterr;

// 守护程序
void daemonize(void)
{
	return ;
}

// 显示程序用法
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
			case 'd': break;
			case 'c': break;
			case 'h': usage(); break;
			case '?': usage(); break;
		}
	}
	return 0;
}
