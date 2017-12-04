#ifndef __HASHMAP_H
#define __HASHMAP_H

#include "containerDefine.h"
#include "Vector.h"

// �����ṹ�弰�����

struct HashMap;
struct String;
typedef struct HashMap HashMap;
typedef struct String String;


// ���������
HashMap *newHashMap(unsigned long(*keyHash)(void *obj));
void freeHashMap(HashMap * const map);
void removeHashMap(HashMap * const map);



struct HashMap{
	int _size;				// ʵ�ʵĴ�С
	int _bucketsLength;		// buckets�����С
	float _maxAverageDeep;	// ���ƽ�����
	KVNode ** _buckets;		// Ͱ
	Vector *_relative;
	void(*_kfm)(void *);	// key���ͷŷ�ʽ

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
	String * (*toString)(HashMap * const self);				// ������ת��Ϊ�ַ�����������ԡ�

	// private
	void (* _resize)(HashMap * const self);

	// ��Ҫ���õĺ�����û�����������Ĭ������
	unsigned long (* _hash)(void *obj);				// value��hash
};


#endif