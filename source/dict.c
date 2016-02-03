#include <dict.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <sys/time.h>

static int dict_can_resize = 1;

/******************api implemention**************************/
/*Reset a hash table already initialized with ht_init().
 *Note: this function should only be called by ht_destroy(). */
static void _dictReset(dictht *ht)
{
    ht->table = NULL;
    ht->size = 0;
    ht->sizemask = 0;
    ht->used = 0;
}

/* Initialize the hash table. */
/* 初始化哈希表 */
static int _dictInit(dict *d, dictType *type, void *privdata)
{
    _dictReset(&d->ht[0]);
    _dictReset(&d->ht[1]);
    d->type = type;
    d->privdata = privdata;
    d->rehashidx = -1;
    d->iterators = 0;
    return DICT_OK;
}

/* create a new hashtable. */
dict *dictCreate(dictType *type, void *privdata) 
{
    dict *d = (dict *)malloc(sizeof(*d));
    return (d == NULL ? NULL : d);
}

/*调整哈希表的大小*/
int dictResize(dict *d)
{
    int minimal;

    if(!dict_can_resize || dictIsRehashing(d)) return DICT_ERR;
    minimal = d->ht[0].used;
    if(minimal < DICT_HT_INITIAL_SIZE)
        minimal = DICT_HT_INITIAL_SIZE;
    return dictExpand(d, minimal);
}

/* Our hash table capability is a power of two */
/* 哈希表的容量是以2的指数增长的 */
static unsigned long _dictNextPower(unsigned long size)
{
    unsigned long i = DICT_HT_INITIAL_SIZE;

    if(size >= LONG_MAX) return LONG_MAX;
    for(;;) {
        if(i >= size)
            return i;
        i *= 2;
    }
    return 0;
}

/* Expand or create the hash table. */
int dictExpand(dict *d, unsigned long size)
{
    dictht n; // the new hashtable.
    unsigned long realsize = _dictNextPower(size);

    /* The size is invalid if it is smaller then the number 
     * of elements already inside the hash table*/
    if(dictIsRehashing(d) || d->ht[0].used > size) return DICT_ERR;

    /* Rehashing to the same table size is not useful. */
    if (realsize  == d->ht[0].size) return DICT_ERR;

    /* Allocate the new hash table and initialized all pointers to NULL. */
    n.size = realsize;
    n.sizemask = realsize - 1;
    n.table = (dictEntry **)malloc(realsize * sizeof(dictEntry *)); // 指向指针的指针

    /* Is this the first initialization? If so it't not really a rehashing
     * we just set the first hash table so that it can accept keys.*/
    if(d->ht[0].table == NULL) {
        d->ht[0] = n;
        return DICT_OK;
    }

    /* Prepare a second hash table for incremental rehashing. */
    d->ht[1] = n;
    d->rehashidx = 0;
    return DICT_OK;
}

/* 渐进式，进行rehash操作*/
int dictRehash(dict *d, int n) {
    // 遍历空桶最大数目
    int empty_visits = n*10; /* Max number of empty bucket to visit.*/

    if(!dictIsRehashing(d)) return 0;
    while(n-- && d->ht[0].used != 0) {
        dictEntry *de, *nextde;
        while(d->ht[0].table[d->rehashidx] == NULL) {
            d->rehashidx++;
            if(--empty_visits == 0)  return DICT_ERR;
        }
        // 将旧的哈希联表移动至新的哈希链表
        de = d->ht[0].table[d->rehashidx];
        while(de) {
            unsigned int h;
            nextde = de->next;
            h = dictHashKey(de->key) & d->ht[1].sizemask;
            de->next = d->ht[1].table[h];
            d->ht[1].table[h] = de;
            d->ht[0].used--;
            d->ht[1].used++;
            de = nextde;
        }
        d->ht[0].table[d->rehashidx] = NULL;
        d->rehashidx++;
    }

    if(d->ht[0].used == 0) {
        free(d->ht[0].table);
        d->ht[0] = d->ht[1];
        _dictReset(&d->ht[1]);
        d->rehashidx = -1;
    }
    return 1;
}

longlong timeInMilliseconds(void) {
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return (((long long)tv.tv_sec)*1000) + (tv.tv_usec/1000);
}

int dictRehashMilliseconds(dict *d, int ms) {
    long long start = timeInMilliseconds();
    int rehashres = 0;

    while(dictRehash(d, 100)) {
        rehashres += 100;
        if((timeInMilliseconds() - start) > ms) break;
    }
    return rehashres;
}
