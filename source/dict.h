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

/* 字典条目 */
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

/* 哈希表 */
typedef struct dictht
{
    dictEntry **table; //哈希桶(Hash Bucket)的数组
    unsigned long size; // 哈希表桶的个数
    unsigned long sizemask; // 哈希表掩码，用于计算散列地址
    unsigned long used; // 已经使用的哈希桶个数
}dictht;

/* 字典类型 */
typedef struct dictType {
    unsigned int (*hashFunction)(void *key); // 计算key散列值的哈希函数指针
    void *(*keyDup)(void *privdata, const void *key); // 键复制的函数指针
    void *(*valDup)(void *privdata, const void *obj); // 值复制的函数指针
    void (*keyDestructor)(void *privdata, const void *key); // 释放键的函数指针
    void (*valDestructor)(void *privdata, const void *val); // 释放值的函数指针
    int (*keyCompare)(void *privdata, const void *key1, const void *key2); // 值比较函数指针
}dictType;

typedef struct dict {
    dictType *type; // 字典类型
    void *privdata; // ???
    dictht ht[2]; // 双哈希表
    long rehashidx; // rehashing索引
    unsigned long iterators; // 该字典上目前运行的迭代器数目
}dict;

/* 字典的迭代器 */
typedef struct dictIterator {
    dict *d; // 指向字典的指针
    long index; // ???
    int table, safe;
    dictEntry *next, *nextEntry; // ???
    long long fingerprint; // 迭代器指纹
}dictIterator;

typedef void (dictScanFunction)(const void *privdata, dictEntry *de); // ???

/* 哈希表的初始化大小 */
#define DICT_HT_INITIAL_SIZE    4

/*****************************宏定义***************************/
/* 释放值 */
#define dictFreeVal(d, entry) do{\
}while(0)

/* 设置字典条目值得宏函数 */
#define dictSetVal(d, entry, _val_) do{\
    if((d)->type->valDup) \
        entry->v.val = (d)->type->valDup((d)->private, _val_); \
    else \
        entry->v.val = _val__; \
}while(0)

/* 设置有符号数 */
#define dictSetSignedIntegerVal(d, entry, _val_) do{ \
    entry->v.s64 = _val_; \
}while(0)

/* 设置无符号数 */
#define dictSetUnsignedIntegerVal(d, entry, _val_) do{ \
    entry->v.u64 = _val_; \
}while(0)

/* 设置双精度浮点数 */
#define dictSetDoubleVal(d, entry, _val_) do{ \
    entry->v.d = _val_; \
}while(0)

/* 设置key值 */
#define dictSetKey(d, entry, _key_) do{ \
    if((d)->type->keyDup) \
        entry->v.val = (d)->keyDup((d)->privdata, _key_) \
}while(0)

/* 释放指定的键 */
#define dictFreeKey(d, entry) do{\
    if((d)->keyDestructor) \
        (d)->keyDestructor(d->privdata, (entry)->key); \
}while(0)

/* 比较两个键值 */
#define dictCompareKey(d, key1, key2) \
    ((d)->type->keyCompare) ? \
        (d)-type->keyCompare((d)->privdata, key1, key2) : \
        ((key1) == (key2)) \

#define dictHashKey(key) (d)->type->hashFunction(key) // 计算key的值
#define dictGetKey(de) ((d)->key) // 获取entry的键
#define dictGetVal(de) ((d)->v.val) // 获取entry的值
#define dictIsRehashing(d) ((d)->rehashidx != -1) // 哈希表是否正在rehashing

/*****************api函数*********************/
dict *dictCreate(dictType *type, void *privdata); // 创建字典
int dictResize(dict *d); // 重新设定哈希表的大小
int dictExpand(dict *d, unsigned long size); // 扩展字典，哈希表rehashing
int dictAdd(dict *d, void *key, void *val); // 字典中加入一个条目
/*****************hash table类型**************/
#endif /* __DICT_H_ */
