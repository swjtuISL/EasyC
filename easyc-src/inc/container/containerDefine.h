#ifndef __CONTAINER_DEFINE_H
#define __CONTAINER_DEFINE_H

struct KVNode;
struct Node;
struct Object;
typedef struct Object Object;
typedef struct KVNode KVNode;
typedef struct Node Node;


// ����ṹ���Ա
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