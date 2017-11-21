#include <stdio.h>
#include <stdlib.h>

#include "Stack.h"
#include "List.h"

static void * pop(Stack *self);
static void push(Stack *self, void *obj);
static void * top(Stack *self);
static int size(Stack *self);

Stack * newStack(){
	Stack *stack = (Stack *)malloc(sizeof(Stack));
	stack->_list = newList();
	stack->pop = pop;
	stack->push = push;
	stack->top = top;
	stack->size = size;
	return stack;
}

void removeStack(Stack *stack){
	removeList(stack->_list);
	free(stack);
}

static void * pop(Stack *self){
	void * top = self->_list->removeLast(self->_list);
	return top;
}

static void push(Stack *self, void *obj){

}
static void * top(Stack *self){
	void * topObj = self->_list->getLast(self->_list);
	return topObj;
}


static int size(Stack *self){
	return self->_list->_size;
}
