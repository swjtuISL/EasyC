#ifndef __CONTAINER_DEFINE_H
#define __CONTAINER_DEFINE_H

struct KVNode;
struct Node;
struct Object;
typedef struct Object Object;
typedef struct KVNode KVNode;
typedef struct Node Node;


// 定义结构体成员
struct KVNode{
	KVNode * next;
	char * key;
	Object * obj;
};

struct Node{
	void *value;
	Node *next;
};


#endif