#ifndef __STACK_H
#define __STACK_H

struct List;
struct Stack;
typedef struct Stack Stack;
typedef struct List List;

Stack * newStack();
void removeStack(Stack *stack);

struct Stack{
	List * _list;

	// public(interface)
	void *(*pop)(Stack *self);					// 出栈
	void(*push)(Stack *self, void *obj);		// 入栈
	void *(*top)(Stack *self);					// 栈顶元素
	int(*size)(Stack *self);					// 栈大小
};

#endif