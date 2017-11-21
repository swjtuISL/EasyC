#ifndef __LIST_H
#define __LIST_H

// 声明结构体及其别名
struct Node;
struct List;
typedef struct Node Node;
typedef struct List List;

// 构造和析构
List *newList();
void removeList(List *list);

// 定义结构体成员
struct Node{
	void *value;
	Node *next;
};

struct List{
	Node * _head;
	Node * _tail;
	int _size;

	// public(interface)
	void (*addLast)(List *self, void *obj);			// 在链表末尾添加对象，【未实现】
	void(*addFirst)(List *self, void *obj);			// 在链表头部添加对象，【未实现】
	void*(*removeLast)(List *self);					// 删除末尾对象，【未实现】
	void*(*removeFirst)(List *self);				// 删除头部对象，【未实现】
	void(*insert)(List *self, int idx, void *obj);	// 在指定的位置插入数据，【未实现】
	void(*remove)(List *self, int idx);				// 删除指定索引位置的数据，【未实现】

	void *(*getLast)(List *self);					// 获得尾部对象，【未实现】
	void *(*getFirst)(List *self);					// 获得头部对象，【未实现】
	void *(*get)(List *self, int idx);				// 获得指定位置的对象，【未实现】

	int(*size)(List *self);							// 获取对象大小，【未实现】
};

#endif