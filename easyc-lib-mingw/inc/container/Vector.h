#ifndef __VECTOR_H
#define __VECTOR_H

// 结构声明
struct Vector;
typedef struct Vector Vector;

// 构造和析构函数
Vector *newVector();
Vector *newVectorByInts(int *ptr, int length);
Vector *newVectorByNumber(int number, int length);
Vector *newVectorByVector(Vector *ovect);
void removeVector(Vector *vector);

// 结构定义
struct Vector{
	int _size;
	int _capacity;
	float _loadFactor;
	void ** _mem;

	// public(interface)
	void * (* get)(Vector *self, int idx);								// 获取指定索引的数据
	void * (* set)(Vector *self, int idx, void *obj);					// 设置指定索引的数据
	void(*add)(Vector *self, void *obj);								// 在末尾添加数据
	void * (*remove)(Vector *self, int idx);							// 删除指定索引的数据
	void(*insert)(Vector *self, int idx, void *obj);					// 在指定索引位置插入数据
	int (*size)(Vector *self);											// 返回动态数组大小
	void(*clean)(void *self);											// 清空动态数组，【未实现】
	int (*contain)(void *self, void * obj, int (*cmp)(void*, void *));	// 判断对象是否存在, 【未实现】


	// private
	void(*_resize)(Vector *self);
};

#endif