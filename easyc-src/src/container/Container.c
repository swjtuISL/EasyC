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
* @Desc   : Container������
* @Return : ����һ���µ�����
* @Authro : Shuaiji Lu
* @Date   : 2017/12/11
*/
Container *newContainer(){
	Container *cont = malloc(sizeof(Container));
	ZeroMemory(cont, sizeof(Container));			// ���������ݳ�ʼ��Ϊ0
	cont->_relative = newVector();					// ���ڱ�������ڴ�

	//load function
	cont->size = size;
	cont->toString = toString;

	return cont;
}

/*
* @Desc   : �����ڴ��ͷ�
* @Param  : *container, ���ͷŵ��ڴ�
* @Authro : Shuaiji Lu
* @Date   : 2017/12/11
*/
void freeContainer(Container *container){
	freeVector(container->_relative);				// �ͷŹ����ڴ�
	for (int i = 0; i < container->_size; i++){
		freeObject(container->objs[i]);
	}
	freeObject(container->objs);
	free(container);
}

/*
* @Desc   : ��ȡ������С
* @Param  : *self, ��������Container.
* @Return : ������С
* @Authro : Shuaiji Lu
* @Date   : 2017/12/11
*/
static int size(Container * const self){
	return self->_size;
}

/*
* @Desc   : ��ʽ��Container
* @Param  : *self, ��������Container.
* @Return : ��ʽ����String
* @Authro : Shuaiji Lu
* @Date   : 2017/12/11
*/
static String * toString(Container * const self){
	String *s = newString("");
	for (int i = 0; i < self->_size; i++){
		s->appendString(s, self->objs[i]->toString(self->objs[i]));				// obj����ĸ�ʽ��������ƴ��
	}
	self->_relative->addObject(self->_relative, s, freeString, NULL, NULL);		// ���ڴ潻��������_relative����
	return s;
}