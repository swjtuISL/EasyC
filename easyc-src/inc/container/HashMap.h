#ifndef __HASHMAP_H
#define __HASHMAP_H

#include "Vector.h"

// 声明结构体及其别名
struct KVNode;
struct HashMap;
struct Entry;
typedef struct KVNode KVNode;
typedef struct HashMap HashMap;
typedef struct Entry Entry;

// 构造和析构
HashMap *newHashMap(unsigned long(*hashFunction)(void *obj));
void freeHashMap(HashMap * const map);
void removeHashMap(HashMap * const map);

// 定义结构体成员
struct KVNode{
	KVNode * next;
	char * key;
	void * value;
};

struct Entry{
	char *key;
	char *value;
};

struct HashMap{
	int _size;				// 实际的大小
	int _bucketsLength;		// buckets数组大小
	float _maxAverageDeep;	// 最大平均深度
	KVNode ** _buckets;		// 桶

	// public(interface)
	void * (*get)(HashMap * const self, void *key);
	void * (*put)(HashMap * const self, void *key, void * value);
	Vector * (*keys)(HashMap * const self);
	Vector * (*entries)(HashMap * const self);
	int(*size)(HashMap * const self);
	char * (*toString)(HashMap * const self);				// 将数据转换为字符串，方便调试【未实现】。

	// private
	void (* _resize)(HashMap * const self);

	// 需要配置的函数，没有配置则采用默认配置
	unsigned long (* _hash)(void *obj);				// value的hash
};


#endif