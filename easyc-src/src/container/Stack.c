#include <stdio.h>
#include <stdlib.h>

#include "Stack.h"
#include "List.h"

static void * pop(Stack * const self);
static void push(Stack * const self, void *obj);
static void * top(Stack * const self);
static int size(Stack * const self);

Stack * newStack(){
	Stack *stack = (Stack *)malloc(sizeof(Stack));
	stack->_list = newList();
	stack->pop = pop;
	stack->push = push;
	stack->top = top;
	stack->size = size;
	return stack;
}

void freeStack(Stack * const stack){
	freeList(stack->_list);
	free(stack);
}

static void * pop(Stack * const self){
	void * top = self->_list->removeLast(self->_list);
	return top;
}

static void push(Stack * const self, void *obj){

}
static void * top(Stack * const self){
	void * topObj = self->_list->getLast(self->_list);
	return topObj;
}


static int size(Stack * const self){
	return self->_list->_size;
}
