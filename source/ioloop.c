#include <base.h>

typedef void * HCHAIN; // 调用链句柄
typedef unsigned int (STDCALL *HANDLER)(const int data); // 回调函数类型

/* 函数对象hash */
typedef struct __hash
{
	unsigned long so_addr;
	unsigned long fn_addr;
}hash;

/* 回调函数节点 */
typedef struct __cb_node
{
	struct __cb_node *prev; // 前驱节点
	struct __cb_node *next; // 后继节点
	HANDLER entry; // 回调函数句柄
	union
	{
		hash h;
		unsigned long scr[2];
	}__hash;
}cb_node;

/* 回调函数链 */
typedef struct __cb_chain
{
	cb_node *HEAD; // 链表头部
	cb_node *TAIL; // 链表尾部
	int count; // 回调函数个数
}cb_chain;

/* 分配数据结构 */
HCHAIN chain()
{
	cb_chain *ptr = (cb_chain *)malloc(sizeof(cb_chain));
	assert(ptr != NULL);
	if(ptr)
	{
		ptr->HEAD = NULL;
		ptr->TAIL = NULL;
		ptr->count = 0;
	}
	return (HCHAIN)ptr;
}

/* 接收数据(通常位于调用链第一个) */
unsigned int dumpdata(int sock)
{	
	assert(sock != -1);
	/* 返回数据的指针，供调用链上的其他函数使用 */
	char *data = NULL;
	return (unsigned int)data;
}

/* 注册回调函数 */
int join(HCHAIN hchain, void *so, HANDLER cb)
{
	assert(!(hchain && so && cb));
	cb_chain *chain = (cb_chain *)hchain;
	if(!chain->HEAD)
	{
		cb_node *node = (cb_node *)malloc(sizeof(cb_node));
		if(node)
		{
			/* new callback node.*/
			node->prev = node;
			node->next = node;
			//node->__hash.h.so_addr = so;
			//node->__hash.h.so_addr = cb;
			/* join in the chain */
			chain->HEAD = node;
			chain->TAIL = node;

			return 0;
		}
	}
	else
	{
		cb_node *tail = chain->TAIL;
		cb_node *node = (cb_node *)malloc(sizeof(cb_node));
		if(node)
		{
			tail->next = node;
			node->prev = tail;
			node->next = chain->HEAD;
			//node->hash = hash;

			return 0;
		}
	}
	return -1;
}
/* 指针与下标  - 指针的效率 */

/* 调用回调函数 */
int chain_call(const HCHAIN hchain, int data)
{
	assert(hchain != NULL);
	// char *buffer = (char *)data;
	return -1;
}

int dispatch()
{
	return 0;
}


