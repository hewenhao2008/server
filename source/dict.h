/*
    @Author: gatsby
    @Data: 2016-01-27
    @Mail: i-careforu@foxmail.com
    @Note: 哈希表的C语言实现。
*/
#ifndef __DICT_H_
#define __DICT_H_

#include <stdint.h>

#define DICT_NOTUSED(V) ((void) V)

typedef struct dictEntry
{
	void *key;
	union
	{
		void *val;
		int64_t s64;
		uint64_t u64;
	}v;
	struct dictEntry *next;
}dictEntry;

#endif
