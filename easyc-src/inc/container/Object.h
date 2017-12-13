#ifndef __OBJECT_H
#define __OBJECT_H

struct Object;
struct String;
struct Vector;
typedef struct String String;
typedef struct Object Object;
typedef struct Vector Vector;

Object *newObject(void *item, void(*freeMethod)(void *item), String *(*itemToString)(void *item), void*(*itemCopy)(void *item));
Object *newIntObject(int val);
Object *newFloatObject(double val);
Object *newCharsObject(char *chars);
Object *simpleObject(void *item);
void freeObject(Object *obj);

/*
* @Desc   : ����һ�ֺ��������ڴ��ַ������, Ҳ������������ͬ����.�����������е��ڴ濽����������Զ��ͷ��Լ��ַ�����.
* @Author : Shuaiji Lu
* @Date   : 2017/11/27
*/
struct Object{
	void *item;
	Vector *_relative;
	Object*(*copy)(Object *self);
	String *(*toString)(Object *self);

	void*(*itemCopy)(void *item);
	void(*itemFree)(void *item);
	String *(*itemToString)(void *item);
};

#endif