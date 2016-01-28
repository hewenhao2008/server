/*
    @Author: gatsby
    @Data: 2015-10-22
    @Mail: i-careforu@foxmail.com
    @Comment: 解析配置文件。 
*/

#ifndef __CONFIG_H_
#define __CONFIG_H_

#include <stdint.h>
#include <base.h>

/* config句柄 */
typedef void *HCONFIG;

/* 获取conf文件句柄 */
HCONFIG STDCALL loadconf(const char *path);

/* 获取某个选项的值 */
void *STDCALL getoption(void *key, void *val);

/* 选项值强制类型转换的宏函数 */
#define OPT_INT(V)      ((int) V)
#define OPT_UINT(V)     ((unsigned int) V)
#define OPT_INT64(V)    ((int64_t) V)
#define OPT_UINT64(V)   ((uint64_t) V)
#define OPT_STR(V)      ((char *) V)
#define OPT_CHAR(V)     ((char) V)

#endif
