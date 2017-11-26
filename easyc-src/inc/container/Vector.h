#ifndef __VECTOR_H
#define __VECTOR_H

// 结构声明
struct Vector;
typedef struct Vector Vector;

// 构造和析构函数
Vector *newVector();
Vector *newVectorByInts(int *ptr, int length);
Vector *newVectorByNumber(int number, int length);
Vector *newVectorByVector(Vector * const ovect);
void freeVector(Vector * const vector);
void freeAllVector(Vector * const vector);

// 结构定义
struct Vector{
	int _size;
	int _capacity;
	float _loadFactor;
	void ** _mem;

	// public(interface)
	void * (* get)(Vector * const self, int idx);								// 获取指定索引的数据
	void * (* set)(Vector * const self, int idx, void *obj);					// 设置指定索引的数据
	void(*add)(Vector * const self, void *obj);								// 在末尾添加数据
	void * (*remove)(Vector * const self, int idx);							// 删除指定索引的数据
	void(*insert)(Vector * const self, int idx, void *obj);					// 在指定索引位置插入数据
	int(*size)(Vector * const self);											// 返回动态数组大小
	void(*clean)(Vector * const);											// 清空动态数组，【未实现】
	int(*contain)(Vector * const, void * obj, int(*cmp)(void*, void *));	// 判断对象是否存在, 【未实现】


	// private
	void(*_resize)(Vector * const self);
};

#endif