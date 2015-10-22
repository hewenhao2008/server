/*
    @Author: gatsby
    @Data: 2015-10-22
    @Mail: i-careforu@foxmail.com
    @Comment: 解析配置文件。 
*/

#ifndef __CONFIG_H_
#define __CONFIG_H_

#include <base.h>

/* config句柄 */
typedef void *HCONFIG;

/* config的选项值 */
typedef unsigned int HVALUE;

/* 获取conf文件句柄 */
HCONFIG STDCALL loadconf(const char *path);

/* 获取conf文件一个选项的值 */
HVALUE STDCALL getvalue(HCONFIG, const char *field);

#endif
