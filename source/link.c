#include <base.h>
#include <link.h>

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
HCHAIN chain(void)
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
		#ifdef DEBUG
		printf("[join node]:%p\n", node);
		#endif
		if(node)
		{
			/* new callback node.*/
			node->prev = node;
			node->next = node;
			node->entry = cb;
			node->__hash.h.so_addr = (ulong)so;
			node->__hash.h.so_addr = (ulong)cb;
			/* join in the chain */
			chain->HEAD = node;
			chain->TAIL = node;
			chain->count++;

			return 0;
		}
	}
	else
	{
		cb_node *tail = chain->TAIL;
		cb_node *node = (cb_node *)malloc(sizeof(cb_node));
		#ifdef DEBUG
		printf("[join node]:%p\n", node);
		#endif
		if(node)
		{
			tail->next = node;
			node->prev = tail;
			node->next = chain->HEAD;
			node->entry = cb;
			node->__hash.h.so_addr = (ulong)so;
			node->__hash.h.so_addr = (ulong)cb;
			/* join in the chain */
			chain->HEAD->prev = node;
			chain->TAIL = node;
			chain->count++;
			
			return 0;
		}
	}
	return -1;
}

/* 调用回调函数 */
int chain_call(const HCHAIN hchain, int data)
{
	assert(hchain != NULL);
	cb_chain *chain = (cb_chain *)hchain;
	if(chain->HEAD)
	{
		// 遍历双向链表，执行回调函数
		cb_node *cp = chain->HEAD;
		cb_node *head = cp;
		
		while(cp->next != head)
		{
			if(cp->entry(data) <= 0)
			{
				return -1;
			}
			cp = cp->next;
		}
	}
	return 0;
}
