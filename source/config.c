/*
    @Author: gatsby
    @Data: 2015-10-22
    @Mail: i-careforu@foxmail.com
    @Comment: 解析配置文件。
*/

#include <config.h>

#define DELIMITER   ' ' 

/* socket缓冲区大小 */
size_t def_buf_size = 32 * 1024;

/* 选项值 */
typedef union
{
	int data;
	void *pdata;
}value_t;

/* 选项键值对 */
/* @Note: C++/Java/Python等语言的map、dict数据类型 */
typedef struct __paires
{
	/* 键值对的键的数据类型为字符串 */
	// char key[32];
	char *key;
	value_t value;
}paires;

/* 红黑树节点颜色 */
/* @Note: 红黑树节点颜色用于标识节点状态 */
typedef enum {RED=0, BLACK} color_t;

/* 二叉树节点 */
/* @Note: 红黑二叉树树有左右叶子节点 */
typedef struct __node
{
	struct __node *lleaf;
	struct __node *rleaf;
	color_t color; 
	paires *map;
}node;

/* 配置文件结构体 */
/* @Note: 配置文件选项的键值对，采用红黑二叉树存储 */
typedef struct __conf
{
    /* 版本字段 */
    size_t cb_size;
	/* 指向二叉树根节点的指针 */
	node *root;
}conf;

/* 红黑二叉树 */
/* @Note: 红黑二叉树相关的操作，特殊的搜索二叉树 */
static inline void init_tree(node **proot)
{
	// assert(proot != NULL);
	*proot = NULL;
}

/* 加载配置文件 */
/* @Note: 解析配置文件，并返回句柄，配置文件采用集合保存key-value键值对 */
HCONFIG STDCALL loadconf(const char *path)
{
    FILE *_f;
    if((_f = fopen(path, "r")) != NULL)
    {
        /* 解析缓冲区 */
        char parser[1024];
        memset((void *)parser, 0, sizeof(parser));

        while(fgets(parser, sizeof(parser), _f) != NULL)
        {
            #ifdef DEBUG
            printf("%s", parser);
            #endif
            /* 解析配置文件 */
            memset((void *)parser, 0, sizeof(parser));
        }

        /* 关闭文件 */
        fclose(_f);
        _f = NULL;
    }
    return 0;
}
