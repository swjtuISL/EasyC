#ifndef __HASHMAP_H
#define __HASHMAP_H

#include "Vector.h"

// �����ṹ�弰�����
struct KVNode;
struct HashMap;
struct Entry;
typedef struct KVNode KVNode;
typedef struct HashMap HashMap;
typedef struct Entry Entry;

// ���������
HashMap *newHashMap(unsigned long(*hashFunction)(void *obj));
void removeHashMap(HashMap *map);

// ����ṹ���Ա
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
	int _size;				// ʵ�ʵĴ�С
	int _bucketsLength;		// buckets�����С
	float _maxAverageDeep;	// ���ƽ�����
	KVNode ** _buckets;		// Ͱ

	// public(interface)
	void * (* get)(HashMap *self, void *key);
	void * (* put)(HashMap *self, void *key, void * value);
	Vector * (* keys)(HashMap *self);
	Vector * (*entries)(HashMap *self);
	int (* size)(HashMap *self);
	char * (*toString)(HashMap *self);				// ������ת��Ϊ�ַ�����������ԡ�δʵ�֡���

	// private
	void (* _resize)(HashMap *self);

	// ��Ҫ���õĺ�����û�����������Ĭ������
	unsigned long (* _hash)(void *obj);				// value��hash
};


#endif