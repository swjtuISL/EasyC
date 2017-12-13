#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "Container.h"
#include "Object.h"
#include "Vector.h"
#include "String.h"

static int size(Container * const self);
static String * toString(Container * const self);

/*
* @Desc   : Container构造器
* @Return : 返回一个新的容器
* @Authro : Shuaiji Lu
* @Date   : 2017/12/11
*/
Container *newContainer(){
	Container *cont = malloc(sizeof(Container));
	ZeroMemory(cont, sizeof(Container));			// 将所有数据初始化为0
	cont->_relative = newVector();					// 用于保存关联内存

	//load function
	cont->size = size;
	cont->toString = toString;

	return cont;
}

/*
* @Desc   : 容器内存释放
* @Param  : *container, 待释放的内存
* @Authro : Shuaiji Lu
* @Date   : 2017/12/11
*/
void freeContainer(Container *container){
	freeVector(container->_relative);				// 释放关联内存
	for (int i = 0; i < container->_size; i++){
		freeObject(container->objs[i]);
	}
	freeObject(container->objs);
	free(container);
}

/*
* @Desc   : 获取容器大小
* @Param  : *self, 待操作的Container.
* @Return : 容器大小
* @Authro : Shuaiji Lu
* @Date   : 2017/12/11
*/
static int size(Container * const self){
	return self->_size;
}

/*
* @Desc   : 格式化Container
* @Param  : *self, 待操作的Container.
* @Return : 格式化的String
* @Authro : Shuaiji Lu
* @Date   : 2017/12/11
*/
static String * toString(Container * const self){
	String *s = newString("");
	for (int i = 0; i < self->_size; i++){
		s->appendString(s, self->objs[i]->toString(self->objs[i]));				// obj自身的格式化并进行拼接
	}
	self->_relative->addObject(self->_relative, s, freeString, NULL, NULL);		// 将内存交给容器的_relative保管
	return s;
}