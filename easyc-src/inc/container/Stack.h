#ifndef __STACK_H
#define __STACK_H

struct List;
struct Stack;
typedef struct Stack Stack;
typedef struct List List;

Stack * newStack();
void freeStack(Stack * const stack);

struct Stack{
	List * _list;

	// public(interface)
	void *(*pop)(Stack * const self);					// 出栈
	void(*push)(Stack * const self, void *obj);		// 入栈
	void *(*top)(Stack * const self);					// 栈顶元素
	int(*size)(Stack * const self);					// 栈大小
};

#endif