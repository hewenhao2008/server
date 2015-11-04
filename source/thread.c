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

/* 原子操作 - 加法 */
static inline void atomic_add(int i, atomic_t *v)
{
	__asm__ __volatile__(
		LOCK_PREFIX "addl %1, %0"
		:"+m"(v->counter)
		:"ir"(i)
	);
}

/* 原子操作 - 减法 */
static inline void atomic_sub(int i, atomic_t *v)
{
	__asm__ __volatile__(
		LOCK_PREFIX "subl %1, %0"
		:"+m"(v->counter)
		:"ir"(i)
	);
}

/* 原子操作 - 自增一 */
static inline void atomic_inc(atomic_t *v)
{
	__asm__ __volatile__(
		LOCK_PREFIX "incl %0"
		:"+m"(v->counter)
	);
}

/* 原子操作 - 自减一 */
static inline void atomic_dec(atomic_t *v)
{
	__asm__ __volatile__(
		LOCK_PREFIX "decl %0"
		:"+m"(v->counter)
	);
}

/* 原子操作　- 自增之后并返回值 */
static inline int atomic_add_return(int i, atomic_t *v)
{
	int _i;
	/* 386 CPU */
	#ifdef _386
	#error("too old arch.")
	#endif
	/* 486之后的数据 */
	_i = i;
	__asm__ __volatile__(
		LOCK_PREFIX "xaddl %0, %1"
		:"+r"(_i), "+m"(v->counter)
		::"memory"
	);
	
	return _i + i;
}

/* 开启新线程 */
