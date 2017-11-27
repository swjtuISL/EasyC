#ifndef __OBJECT_H
#define __OBJECT_H

struct Object;
typedef struct Object Object;

Object *newObject(void *item, void(*freeMethod)(void *item));
Object *simpleObject(void *item);
void freeObject(Object *obj);

/*
* @Desc   : 这是一种含有主题内存地址的容器, 也被其他容器共同依赖.可以用于其中的内存拷贝和对象的自动释放.
* @Author : Shuaiji Lu
* @Date   : 2017/11/27
*/
struct Object{
	void *item;
	int refCount;

	Object*(*copy)(Object *self);

	void*(*itemCopy)(void *item);
	void(*freeMethod)(void *item);
};

#endif