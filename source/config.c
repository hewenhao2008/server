/*
    @Author: gatsby
    @Data: 2015-10-22
    @Mail: i-careforu@foxmail.com
    @Comment: 解析配置文件。
*/

#include <config.h>

/* 映射宏＠将文本映射至ｃ语言结构体 */
#define BEGIN_MAP(list)

/* 映射宏＠将文本映射至c语言结构体 */
#define END_MAP

size_t def_buf_size = 32 * 1024;

/* config句柄 */
typedef struct __config
{
    void *ptr;
}config;

/* 加载配置文件 */
HCONFIG STDCALL loadconf(const char *path)
{
    return 0;
}
