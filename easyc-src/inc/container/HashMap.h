#ifndef __HASHMAP_H
#define __HASHMAP_H

#include "containerDefine.h"
#include "Vector.h"

// 声明结构体及其别名

struct HashMap;
struct String;
typedef struct HashMap HashMap;
typedef struct String String;


// 构造和析构
HashMap *newHashMap(unsigned long(*keyHash)(void *obj));
void freeHashMap(HashMap * const map);
void removeHashMap(HashMap * const map);



struct HashMap{
	int _size;				// 实际的大小
	int _bucketsLength;		// buckets数组大小
	float _maxAverageDeep;	// 最大平均深度
	KVNode ** _buckets;		// 桶
	Vector *_relative;
	void(*_kfm)(void *);	// key的释放方式

	// public(interface)
	void (*setKeyFreeMethod)(HashMap * const self, void (*keyFreeMethod)(void *));
	void * (*get)(HashMap * const self, void *key);
	int(*getInt)(HashMap * const self, void *key);
	float(*getFloat)(HashMap * const self, void *key);
	void (*putInt)(HashMap * const self, void *key, int value);
	void (*putFloat)(HashMap * const self, void *key, double value);
	void (*putChars)(HashMap * const self, void *key, char * value);
	void(*put)(HashMap * const self, void *key, void * value, 
		void(*freeMethod)(void *),
		String *(itemToString)(void *),
		void*(*itemCopy)(void *));
	Vector * (*keys)(HashMap * const self);
	int(*size)(HashMap * const self);
	String * (*toString)(HashMap * const self);				// 将数据转换为字符串，方便调试。

	// private
	void (* _resize)(HashMap * const self);

	// 需要配置的函数，没有配置则采用默认配置
	unsigned long (* _hash)(void *obj);				// value的hash
};


#endif