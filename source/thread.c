/*
	@Author: gatbsy
	@Date: 2015-11-04
	@Mail: i-careforu@foxmail.com
	@Comment: 线程库。
*/

#include <base.h>
#include <thread.h>

/* @Note: 原子操作部分借鉴linux内核中原子操作的实现 */

/* x86架构的lock指定前缀 */
/* @Note: 单核CPU中一条机器指令始终为原子操作，无需使用lock指定前缀，多核CPU中存在多核并行访问同一个内存单元的可能，所以需lock指令前缀锁定cpu地址总线(ABUS) */
/* @Note: 移除linux内核中smp内存补丁的机制 */
#ifndef UP
#define LOCK_PREFIX "lock"
#else
#define LOCK_PREFIX
#endif

/* 原子操作值类型 */
/* @Note: volatile关键字告诉gcc始终从内存取得counter变量的值，而非CPU寄存器或缓存 */
typedef struct
{
	volatile int counter;
}atomic_t;

/* 设置值 */
static inline void atomic_set(int i, atomic_t *v)
{
	v->counter = i;
}

/* 获取值 */
static inline int atomic_get(atomic_t *v)
{
	return v->counter;
}

/* 加法 */
/* @Note: 原子操作，确保值只会被一个线程所修改 */
static inline void atomic_add(int i, atomic_t *v)
{
	__asm__ __volatile__(
		LOCK_PREFIX "addl %1, %0"
		:"+m"(v->counter)
		:"ir"(i)
	);
}

/* 减法 */
/* @Note: 原子操作，确保值只会被一个线程所修改 */
static inline void atomic_sub(int i, atomic_t *v)
{
	__asm__ __volatile__(
		LOCK_PREFIX "subl %1, %0"
		:"+m"(v->counter)
		:"ir"(i)
	);
}

/* 自增一 */
/* @Note: 原子操作，确保值只会被一个线程所修改 */
static inline void atomic_inc(atomic_t *v)
{
	__asm__ __volatile__(
		LOCK_PREFIX "incl %0"
		:"+m"(v->counter)
	);
}

/* 自减一 */
/* @Note: 原子操作，确保值只会被一个线程所修改 */
static inline void atomic_dec(atomic_t *v)
{
	__asm__ __volatile__(
		LOCK_PREFIX "decl %0"
		:"+m"(v->counter)
	);
}

/* 自增之后并返回值 */
/* @Note: 原子操作，确保值只会被一个线程所修改 */
static inline int atomic_add_return(int i, atomic_t *v)
{
	int _i;
	/* 386 CPU编译器报错 */
	#ifdef _386
	#error("too old architecture.")
	#endif

	/* 486之后的CPU */
	_i = i;
	__asm__ __volatile__(
		LOCK_PREFIX "xaddl %0, %1"
		:"+r"(_i), "+m"(v->counter)
		::"memory"
	);
	
	return _i + i;
}

/* 自减之后并返回值 */
/* @Note: 原子操作，确保值只会被一个线程所修改 */
static inline int atomic_sub_return(int i, atomic_t *v)
{
    return atomic_add_return(-i, v);
}

/* 线程优先级 */
/* @Note: 对OS线程调度算法做了透明处理 */
typedef enum
{
    REAL = -1,  // 实时
    URGEN,      // 紧急
    NORMAL,     // 正常
    IDLE        // 空闲
}PRIORITY;

/* 线程数据结构 */
/* @Note: 类似TEB的结构体，描述线程的信息 */
typedef struct
{
    pid_t __tid;    // 线程ID
    int __core;     // 线程context所在的CPU核
    PRIORITY __prio; // 线程优先级
}thread;

/* 创建新线程 */
/* @Note: 创建新的线程并且可以指定线程优先级与线程运行的CPU核心 */
HTHREAD STDCALL new_thread(void *(STDCALL *start_routine) (void *), PRIORITY priority, int core)
{
    thread *thr = (thread *)malloc(sizeof(thread));
    assert(thr != NULL);
    if(thr)
    {
        ENTER();
        int _res = -1;
        JUDGE(_res);
        // pthread_t _thr;
        // pthread_attr_t attr; // 线程属性
        // _res = pthread_attr_init(&attr);
        LEAVE();
    }

    return NULL;
}
