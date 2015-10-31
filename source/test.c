
void test(void)
{
    int a = 10, b;
    __asm__ __volatile__(
        "movl %1, %%eax;"
        "movl %%eax, %0;"
        :"=r"(b)
        :"r"(a)
        :"%eax"
    );
}
