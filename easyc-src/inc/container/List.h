#ifndef __LIST_H
#define __LIST_H

#include "containerDefine.h"

// �����ṹ�弰�����
struct List;
typedef struct List List;

// ���������
List *newList();
void freeList(List * const list);

struct List{
	Node * _head;
	Node * _tail;
	int _size;

	// public(interface)
	void(*addLast)(List * const self, void *obj);			// ������ĩβ��Ӷ��󣬡�δʵ�֡�
	void(*addFirst)(List * const self, void *obj);			// ������ͷ����Ӷ��󣬡�δʵ�֡�
	void*(*removeLast)(List * const self);					// ɾ��ĩβ���󣬡�δʵ�֡�
	void*(*removeFirst)(List * const self);				// ɾ��ͷ�����󣬡�δʵ�֡�
	void(*insert)(List * const self, int idx, void *obj);	// ��ָ����λ�ò������ݣ���δʵ�֡�
	void(*remove)(List * const self, int idx);				// ɾ��ָ������λ�õ����ݣ���δʵ�֡�

	void *(*getLast)(List * const self);					// ���β�����󣬡�δʵ�֡�
	void *(*getFirst)(List * const self);					// ���ͷ�����󣬡�δʵ�֡�
	void *(*get)(List * const self, int idx);				// ���ָ��λ�õĶ��󣬡�δʵ�֡�

	int(*size)(List * const self);							// ��ȡ�����С����δʵ�֡�
};

#endif