/*
	@Author: gatbsy
	@Date: 2015-11-04
	@Mail: i-careforu@foxmail.com
	@Comment: 线程库。
*/

/* 线程句柄 */
typedef void *HTHREAD;

/* 线程池句柄 */
typedef void *HPOOL;

/* 线程函数 */
/* ＠Note: 线程回调函数 */
typedef void *(STDCALL *start_routine) (void *);

/* 创建新的线程 */
/* @Note:对POSIX线程库进行了一层封装 */
/* @Param: start_routine-> 线程回调函数 */
/* @Param: priority -> 线程优先级 */
/* @Param: core -> 线程将要运行在哪一个CPU核心上 */
/* @Return: HTHREAD -> 线程句柄 */
HTHREAD STDCALL new_thread(void *(STDCALL *start_routine) (void *), int priority, int core);

/* 创建线程池 */
/* @Note: 高效线程池模型的实现 */
/* @Param: start_routine -> 线程回调函数 */
/* @Param: size -> 线程池中线程的个数，size=-1,则默认个数同CPU核数一致 */
/* @Return: HPOOL -> 线程池句柄 */
HPOOL STDCALL create_pool(void *(STDCALL *start_routine) (void *), int size);

/* 线程同步 */
