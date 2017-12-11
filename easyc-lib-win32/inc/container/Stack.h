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
	void *(*pop)(Stack *self);					// ��ջ
	void(*push)(Stack *self, void *obj);		// ��ջ
	void *(*top)(Stack *self);					// ջ��Ԫ��
	int(*size)(Stack *self);					// ջ��С
};

#endif