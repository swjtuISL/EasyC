#ifndef __CONTAINER_H
#define __CONTAINER_H

struct Container;
struct String;
struct Vector;
struct Object;
typedef struct String String;
typedef struct Container Container;
typedef struct Vector Vector;
typedef struct Object Object;

Container *newContainer();
void freeContainer(Container *container);

/*
* @Desc   : ÈÝÆ÷±àÐ´Ê¾·¶Ä£°å
* @Author : Shuaiji Lu
* @Date   : 2017/12/11
*/
struct Container{
	int _size;
	Vector *_relative;
	Object **objs;

	int(*size)(Container * const self);
	String * (*toString)(Container * const self);
};

#endif