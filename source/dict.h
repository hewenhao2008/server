/*
    @Author: gatsby
    @Data: 2016-01-27
    @Mail: i-careforu@foxmail.com
    @Note: 哈希表的C语言实现（借鉴了redis的hash类型实现）。
*/
#ifndef __DICT_H_
#define __DICT_H_

#include <stdint.h>

/* Unused arguemts generate annoying warings...*/
#define DICT_NOTUSED(V) ((void) V)

#define DICT_OK		0
#define DICT_ERR	1

typedef struct dictEntry
{
	void *key;
	union
	{
		void *val;
		int64_t s64;
		uint64_t u64;
		double d;
	}v;
	struct dictEntry *next;
}dictEntry;

#endif
