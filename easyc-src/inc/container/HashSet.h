#ifndef __HASH_SET_H
#define __HASH_SET_H

struct HashSet;
typedef struct HashSet HashSet;

struct HashSet{
	void(*add)(HashSet * const self, void *);
	int(*size)(HashSet * const self);
	char * (*toString)(HashSet * const self);				// 将数据转换为字符串，方便调试【未实现】。
};

#endif