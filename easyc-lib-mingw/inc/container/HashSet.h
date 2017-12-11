#ifndef __HASH_SET_H
#define __HASH_SET_H

struct HashSet;
typedef struct HashSet HashSet;

struct HashSet{
	void(*add)(HashSet *self, void *);
	int (*size)(HashSet *self);
	char * (*toString)(HashSet *self);				// 将数据转换为字符串，方便调试【未实现】。
};

#endif