#ifndef UP
#define LOCK_PREFIX \
        ".section .smp_locks,\"a\"\n"    \
        "  .align 4\n"            \
"  .long 661f\n" /* address */    \
".previous\n"            \
"661:\n\tlock; "

#else /* ! CONFIG_SMP */
#define LOCK_PREFIX ""
#endif

void test(void)
{
	__asm__ __volatile__(
		LOCK_PREFIX "xchg %eax, %ebx"
	);
}

/*
int main(int argc, char **argv)
{
	test();
	return 0;
}*/
