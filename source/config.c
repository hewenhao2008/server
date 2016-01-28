/*
    @Author: gatsby
    @Data: 2015-10-22
    @Mail: i-careforu@foxmail.com @Comment: 解析配置文件。
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
	/* 键值对键的数据类型为字符串 */
	void *pkey;
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
	unsigned int score;
	//int (*get_score)(paires *);
}node;

/* 计算二叉树节点权值 */
/* @Note: 根据二叉树节点权值进行排序 */
int get_score(paires *map)
{
	int score = 0;
	char *cp = (char *)map->pkey;
	while(cp++ != NULL)
	{
		score += *cp << 3;
	}
	return score;
}

/* 二叉树结构体 */
/* @Note: 描述整棵二叉树属性的数据结构 */
typedef struct __tree
{
	/* 根节点 */
	node *root;
	/* 二叉树节点个数 */
	size_t count;
	/* 树的深度 */
	int depth;
	/* 树的度 */
	int degree;
	/* 获取树的深度 */
	//int (*get_depth)(struct __tree *);
	/* 获取树的度 */
	//int (*get_degree)(struct __tree *);
	/* 红色节点个数 */
	//size_t red;
	/* 黑色节点个数 */
	//size_t black;
}tree;

/* 初始化红黑二叉树 */
/* @Note: 二叉树根节点指针初始化为NULL */
static inline void init_tree(tree *_tree)
{
	memset((void *)_tree, sizeof(tree), 0);
	_tree->depth = 1;
}

/* 向二叉树插入节点 */
/* @Note: 递归实现方式 */
int insert_recursive(node *_root, node *_node)
{
	return 0;
}

/* 向二叉树插入节点 */
int insert_node(tree *_tree, node *_node)
{
	_node->score = get_score(_node->map);
	_tree->count++;
	/* 调用递归实现方式　*/
	return insert_recursive(_tree->root, _node);
}

/* 二叉树的深度 */
/* @Note: 默认二叉树的根节点深度depth为1 */
int depth(tree *_tree)
{
	return _tree->depth;
}

/* 二叉树的度 */
/* @Note: 默认二叉树的度为0 */
int degree(tree *_tree)
{
	return _tree->degree;
}

/* 配置文件结构体 */
/* @Note: 配置文件选项的键值对，采用红黑二叉树存储 */
typedef struct __conf
{
    /* 版本字段 */
    size_t cb_size;
	/* 指向二叉树根节点的指针 */
	tree *_tree;
}conf;

/* 加载配置文件 */
/* @Note: 解析配置文件，并返回句柄，配置文件采用集合保存key-value键值对 */
HCONFIG STDCALL loadconf(const char *path)
{
    FILE *_f;
    if((_f = fopen(path, "r")) != NULL)
    {
        /* 关闭文件 */
        fclose(_f);
        _f = NULL;
    }
    return NULL;
}

void *STDCALL getoption(void *key, void *val)
{
    return NULL;
}
