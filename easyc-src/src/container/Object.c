#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <memory.h>
#include "Vector.h"
#include "Object.h"

static void * defaultItemCopy(void *item);
static String * defaultToString(void *item);

static double * floatCopy(void *item);
static char   * charsCopy(void *item);
static String * intToString(void *item);
static String * floatToString(void *item);
static String * charsToString(void *item);

static Object * copy(Object *self);
static String * toString(Object *self);

/*
* @Desc   : Object构造器。需要指定Object中item所指内存的释放方法, 用于在Object释放时, 自动释放item所指向的内存.
* @Param  : *item, Object中的主题内存的地址.
* @Param  : *freeMethod, 主题内存的释放.
* @Param  : *itemToString, 主题内存的字符串化.
* @Return : 返回新的构建好的Object.
* @Authro : Shuaiji Lu
* @Date   : 2017/11/27
*/
Object *newObject(void *item, 
	void(*itemFree)(void *item), String *(*itemToString)(void *item), void*(*itemCopy)(void *item)){

	Object *obj = (Object *)malloc(sizeof(Object));
	ZeroMemory(obj, sizeof(Object));
	obj->item = item;
	obj->_relative = newVector();
	// load function
	obj->copy = copy;
	obj->toString = toString;

	obj->itemCopy = itemCopy == NULL ? defaultItemCopy : itemCopy;
	obj->itemToString = itemToString == NULL ? defaultToString : itemToString;
	obj->itemFree = itemFree;
	return obj;
}

/*
* @Desc   : Object构造器。item中直接保存整数，使用的也是该整数。
* @Param  : val, Object中保存的整数。
* @Return : 返回新的构建好的Object.
* @Authro : Shuaiji Lu
* @Date   : 2017/11/30
*/
Object *newIntObject(int val){
	return newObject(val, NULL, intToString, NULL);
}

/*
* @Desc   : Object构造器。item中保存浮点数的地址。
* @Param  : val, 主题内存中保存的浮点数值。
* @Return : 返回新的构建好的Object.
* @Authro : Shuaiji Lu
* @Date   : 2017/11/30
*/
Object *newFloatObject(double val){
	double *dv = malloc(sizeof(double) * 1);
	*dv = val;
	return newObject(dv, free, floatToString, floatCopy);
}

/*
* @Desc   : Object构造器。常量字符数组会调用该方法，将会重新分配一段新的内存保存字符数组，这样做主要是为了让主题内存更可控。
* @Param  : *chars, Object中的主题内存的地址.
* @Return : 返回新的构建好的Object.
* @Authro : Shuaiji Lu
* @Date   : 2017/11/30
*/
Object *newCharsObject(char *chars){
	int length = lstrlen(chars)+1;
	char *nchars = (char *)malloc(sizeof(char)*length);
	memcpy(nchars, chars, length);
	return newObject(nchars, free, charsToString, charsCopy);
}

/*
* @Desc   : Object构造器。构造一个简单Object, 并且主题内存不需要释放(这种情况一般是item并没有指向可用内存, 或者所指的内存分布在常数区域)
* @Param  : *item。Object主题内存的地址。
* @Return : 返回新的构建好的Object
* @Authro : Shuaiji Lu
* @Date   : 2017/11/27
*/
Object *simpleObject(void *item){
	return newObject(item, NULL, NULL, NULL);
}

/*
* @Desc   : 释放Object。这里面引入了引用计数, 用于当Object被多个容器所引用, 而其中一个容器释放空间时限制对Object的释放。当freeMethod不为NULL时，会对主题内存释放空间。
* @Param  : *chars.初始字符串.
* @Return : 返回新的构建好的String
* @Authro : Shuaiji Lu
* @Date   : 2017/11/27
*/
void freeObject(Object *obj){
	freeVector(obj->_relative);
	if (obj->itemFree){
		obj->itemFree(obj->item);
	}
	free(obj);
}

/*
* @Desc   : 主题内存的默认拷贝函数，直接返回主题内存首地址。此种拷贝方案，通常会有多个指针指向主题地址。常用在主题地址为整数值时，或是不需要考虑主题内存的拷贝时。
* @Param  : *item, 主题内存的地址.
* @Return : 返回新内存的首地址.
* @Authro : Shuaiji Lu
* @Date   : 2017/11/30
*/
static void * defaultItemCopy(void *item){
	return item;
}

/*
* @Desc   : 浮点数内存拷贝函数.
* @Param  : *item, 主题内存的地址.
* @Return : 返回新内存的首地址.
* @Authro : Shuaiji Lu
* @Date   : 2017/11/30
*/
static double * floatCopy(void *item){
	double *nd = (double *)malloc(sizeof(double)*1);
	*nd = *(double *)item;
	return nd;
}

/*
* @Desc   : 字符数组拷贝函数.
* @Param  : *item, 主题内存的地址.
* @Return : 返回新内存的首地址.
* @Authro : Shuaiji Lu
* @Date   : 2017/11/30
*/
static char   * charsCopy(void *item){
	char *chars = item;
	int length = lstrlen(chars);
	char *nchars = (char *)malloc(sizeof(char)*length);
	return nchars;
}

/*
* @Desc   : 主题内存的默认字符串化函数，直接将主题内存的首地址值字符串化。
* @Param  : *item, 主题内存的地址.
* @Return : 字符串化的结果.
* @Authro : Shuaiji Lu
* @Date   : 2017/11/30
*/
static String * defaultToString(void *item){
	String *s = newString("");
	return s->appendInt(s, (int)item);
}

/*
* @Desc   : IntObject字符串化.
* @Param  : *item, Object中的主题内存的地址，这里就算需要字符串化的数值，因为用地址来直接保存数值.
* @Return : 字符串化的结果.
* @Authro : Shuaiji Lu
* @Date   : 2017/11/30
*/
static String * intToString(void *item){
	String *s = newString("");
	return s->appendInt(s, (int)item);
}

/*
* @Desc   : FloatObject字符串化.
* @Param  : *item, 指向double类型的内存地址.
* @Return : 字符串化的结果.
* @Authro : Shuaiji Lu
* @Date   : 2017/11/30
*/
static String * floatToString(void *item){
	String *s = newString("");
	return s->appendFloat(s, *(double *)item);
}

/*
* @Desc   : CharsObject字符串化.
* @Param  : *item, Object中的主题内存的地址.
* @Return : 字符串化的结果.
* @Authro : Shuaiji Lu
* @Date   : 2017/11/30
*/
static String * charsToString(void *item){
	return newString((char *)item);
}

/*
* @Desc   : Object的字符串化，直接交给itemToString方法。
* @Param  : *self, Object自身，用于外部调用.
* @Return : 字符串化的结果.
* @Authro : Shuaiji Lu
* @Date   : 2017/11/30
*/
static String * toString(Object *self){
	String *s = self->itemToString(self->item);
	self->_relative->addObject(self->_relative, s, freeString, NULL, NULL);
	return s;
}


/*
* @Desc   : Object的拷贝。现将item内存进行拷贝，再拷贝其释放方案，字符串化方案，拷贝方案。
* @Param  : *self, Object自身，用于外部调用.
* @Return : 字符串化的结果.
* @Authro : Shuaiji Lu
* @Date   : 2017/11/30
*/
static Object * copy(Object *self){
	return newObject(self->itemCopy(self->item), self->itemFree, self->itemToString, self->itemCopy);
}