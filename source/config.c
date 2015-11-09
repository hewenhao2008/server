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

/* 配置文件结构体 */
typedef struct __conf
{
    /* 版本字段 */
    size_t cb_size;
}conf;

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
