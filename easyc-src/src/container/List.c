#include <stdio.h>
#include <stdlib.h>

#include "List.h"

List *newList(){
	List * list = (List *)malloc(sizeof(List));
	list->_size = 0;
	list->_tail = NULL;
	list->_head = NULL;

	return list;
}

void removeList(List *list){
	for (Node *node = list->_head; node != NULL; ){
		Node *nextnode = node->next;
		free(node);
		node = nextnode;
	}
	free(list);
}