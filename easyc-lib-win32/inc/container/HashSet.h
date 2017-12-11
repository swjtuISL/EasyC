#ifndef __HASH_SET_H
#define __HASH_SET_H

struct HashSet;
typedef struct HashSet HashSet;

struct HashSet{
	void(*add)(HashSet *self, void *);
	int (*size)(HashSet *self);
	char * (*toString)(HashSet *self);				// ������ת��Ϊ�ַ�����������ԡ�δʵ�֡���
};

#endif