#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "Object.h"

static void * defaultItemCopy(void *item);
static Object* defaultCopy(Object *self);

/*
* @Desc   : Object构造器。需要指定Object中item所指内存的释放方法, 用于在Object释放时, 自动释放item所指向的内存.
* @Param  : *item, Object中的主题内存的地址.
* @Param  : *freeMethod, 主题内存的释放.
* @Return : 返回新的构建好的Object.
* @Authro : Shuaiji Lu
* @Date   : 2017/11/27
*/
Object *newObject(void *item, void(*freeMethod)(void *item)){
	Object *obj = (Object *)malloc(sizeof(Object));
	ZeroMemory(obj, sizeof(Object));
	obj->item = item;
	obj->refCount = 1;
	// load function
	obj->freeMethod = freeMethod;
	obj->itemCopy = defaultItemCopy;
	obj->copy = defaultCopy;
	return obj;
}

/*
* @Desc   : Object构造器。构造一个简单Object, 并且主题内存不需要释放(这种情况一般是item并没有指向可用内存, 或者所指的内存分布在常数区域)
* @Param  : *item。Object主题内存的地址。
* @Return : 返回新的构建好的Object
* @Authro : Shuaiji Lu
* @Date   : 2017/11/27
*/
Object *simpleObject(void *item){
	return newObject(item, NULL);
}

/*
* @Desc   : 释放Object。这里面引入了引用计数, 用于当Object被多个容器所引用, 而其中一个容器释放空间时限制对Object的释放。当freeMethod不为NULL时，会对主题内存释放空间。
* @Param  : *chars.初始字符串.
* @Return : 返回新的构建好的String
* @Authro : Shuaiji Lu
* @Date   : 2017/11/27
*/
void freeObject(Object *obj){
	obj->refCount -= 1;
	if (obj->refCount == 0){
		if (obj->freeMethod){
			obj->freeMethod(obj->item);
		}
		free(obj);
	}
}

static void * defaultItemCopy(void *item){
	return item;
}

static Object* defaultCopy(Object *self){
	return newObject(self->itemCopy(self->item), self->freeMethod);
}