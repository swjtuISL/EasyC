#ifndef __LIST_H
#define __LIST_H

// �����ṹ�弰�����
struct Node;
struct List;
typedef struct Node Node;
typedef struct List List;

// ���������
List *newList();
void removeList(List *list);

// ����ṹ���Ա
struct Node{
	void *value;
	Node *next;
};

struct List{
	Node * _head;
	Node * _tail;
	int _size;

	// public(interface)
	void (*addLast)(List *self, void *obj);			// ������ĩβ��Ӷ��󣬡�δʵ�֡�
	void(*addFirst)(List *self, void *obj);			// ������ͷ����Ӷ��󣬡�δʵ�֡�
	void*(*removeLast)(List *self);					// ɾ��ĩβ���󣬡�δʵ�֡�
	void*(*removeFirst)(List *self);				// ɾ��ͷ�����󣬡�δʵ�֡�
	void(*insert)(List *self, int idx, void *obj);	// ��ָ����λ�ò������ݣ���δʵ�֡�
	void(*remove)(List *self, int idx);				// ɾ��ָ������λ�õ����ݣ���δʵ�֡�

	void *(*getLast)(List *self);					// ���β�����󣬡�δʵ�֡�
	void *(*getFirst)(List *self);					// ���ͷ�����󣬡�δʵ�֡�
	void *(*get)(List *self, int idx);				// ���ָ��λ�õĶ��󣬡�δʵ�֡�

	int(*size)(List *self);							// ��ȡ�����С����δʵ�֡�
};

#endif