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
* @Desc   : Object����������Ҫָ��Object��item��ָ�ڴ���ͷŷ���, ������Object�ͷ�ʱ, �Զ��ͷ�item��ָ����ڴ�.
* @Param  : *item, Object�е������ڴ�ĵ�ַ.
* @Param  : *freeMethod, �����ڴ���ͷ�.
* @Param  : *itemToString, �����ڴ���ַ�����.
* @Return : �����µĹ����õ�Object.
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
* @Desc   : Object��������item��ֱ�ӱ���������ʹ�õ�Ҳ�Ǹ�������
* @Param  : val, Object�б����������
* @Return : �����µĹ����õ�Object.
* @Authro : Shuaiji Lu
* @Date   : 2017/11/30
*/
Object *newIntObject(int val){
	return newObject(val, NULL, intToString, NULL);
}

/*
* @Desc   : Object��������item�б��渡�����ĵ�ַ��
* @Param  : val, �����ڴ��б���ĸ�����ֵ��
* @Return : �����µĹ����õ�Object.
* @Authro : Shuaiji Lu
* @Date   : 2017/11/30
*/
Object *newFloatObject(double val){
	double *dv = malloc(sizeof(double) * 1);
	*dv = val;
	return newObject(dv, free, floatToString, floatCopy);
}

/*
* @Desc   : Object�������������ַ��������ø÷������������·���һ���µ��ڴ汣���ַ����飬��������Ҫ��Ϊ���������ڴ���ɿء�
* @Param  : *chars, Object�е������ڴ�ĵ�ַ.
* @Return : �����µĹ����õ�Object.
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
* @Desc   : Object������������һ����Object, ���������ڴ治��Ҫ�ͷ�(�������һ����item��û��ָ������ڴ�, ������ָ���ڴ�ֲ��ڳ�������)
* @Param  : *item��Object�����ڴ�ĵ�ַ��
* @Return : �����µĹ����õ�Object
* @Authro : Shuaiji Lu
* @Date   : 2017/11/27
*/
Object *simpleObject(void *item){
	return newObject(item, NULL, NULL, NULL);
}

/*
* @Desc   : �ͷ�Object�����������������ü���, ���ڵ�Object���������������, ������һ�������ͷſռ�ʱ���ƶ�Object���ͷš���freeMethod��ΪNULLʱ����������ڴ��ͷſռ䡣
* @Param  : *chars.��ʼ�ַ���.
* @Return : �����µĹ����õ�String
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
* @Desc   : �����ڴ��Ĭ�Ͽ���������ֱ�ӷ��������ڴ��׵�ַ�����ֿ���������ͨ�����ж��ָ��ָ�������ַ�������������ַΪ����ֵʱ�����ǲ���Ҫ���������ڴ�Ŀ���ʱ��
* @Param  : *item, �����ڴ�ĵ�ַ.
* @Return : �������ڴ���׵�ַ.
* @Authro : Shuaiji Lu
* @Date   : 2017/11/30
*/
static void * defaultItemCopy(void *item){
	return item;
}

/*
* @Desc   : �������ڴ濽������.
* @Param  : *item, �����ڴ�ĵ�ַ.
* @Return : �������ڴ���׵�ַ.
* @Authro : Shuaiji Lu
* @Date   : 2017/11/30
*/
static double * floatCopy(void *item){
	double *nd = (double *)malloc(sizeof(double)*1);
	*nd = *(double *)item;
	return nd;
}

/*
* @Desc   : �ַ����鿽������.
* @Param  : *item, �����ڴ�ĵ�ַ.
* @Return : �������ڴ���׵�ַ.
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
* @Desc   : �����ڴ��Ĭ���ַ�����������ֱ�ӽ������ڴ���׵�ֵַ�ַ�������
* @Param  : *item, �����ڴ�ĵ�ַ.
* @Return : �ַ������Ľ��.
* @Authro : Shuaiji Lu
* @Date   : 2017/11/30
*/
static String * defaultToString(void *item){
	String *s = newString("");
	return s->appendInt(s, (int)item);
}

/*
* @Desc   : IntObject�ַ�����.
* @Param  : *item, Object�е������ڴ�ĵ�ַ�����������Ҫ�ַ���������ֵ����Ϊ�õ�ַ��ֱ�ӱ�����ֵ.
* @Return : �ַ������Ľ��.
* @Authro : Shuaiji Lu
* @Date   : 2017/11/30
*/
static String * intToString(void *item){
	String *s = newString("");
	return s->appendInt(s, (int)item);
}

/*
* @Desc   : FloatObject�ַ�����.
* @Param  : *item, ָ��double���͵��ڴ��ַ.
* @Return : �ַ������Ľ��.
* @Authro : Shuaiji Lu
* @Date   : 2017/11/30
*/
static String * floatToString(void *item){
	String *s = newString("");
	return s->appendFloat(s, *(double *)item);
}

/*
* @Desc   : CharsObject�ַ�����.
* @Param  : *item, Object�е������ڴ�ĵ�ַ.
* @Return : �ַ������Ľ��.
* @Authro : Shuaiji Lu
* @Date   : 2017/11/30
*/
static String * charsToString(void *item){
	return newString((char *)item);
}

/*
* @Desc   : Object���ַ�������ֱ�ӽ���itemToString������
* @Param  : *self, Object���������ⲿ����.
* @Return : �ַ������Ľ��.
* @Authro : Shuaiji Lu
* @Date   : 2017/11/30
*/
static String * toString(Object *self){
	String *s = self->itemToString(self->item);
	self->_relative->addObject(self->_relative, s, freeString, NULL, NULL);
	return s;
}


/*
* @Desc   : Object�Ŀ������ֽ�item�ڴ���п������ٿ������ͷŷ������ַ���������������������
* @Param  : *self, Object���������ⲿ����.
* @Return : �ַ������Ľ��.
* @Authro : Shuaiji Lu
* @Date   : 2017/11/30
*/
static Object * copy(Object *self){
	return newObject(self->itemCopy(self->item), self->itemFree, self->itemToString, self->itemCopy);
}