#ifndef __VECTOR_H
#define __VECTOR_H

// 结构声明
struct Vector;
struct Object;
struct String;
typedef struct Vector Vector;
typedef struct Object Object;
typedef struct String String;

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
	Vector * _relative;
	Object ** _mem;

	// public(interface)
	void * (* get)(Vector * const self, int idx);							// 获取指定索引的数据
	void (*set)(Vector * const self, int idx, void *item);					// 设置指定索引的数据, 数据所指向的内存不会释放
	void (*fset)(Vector * const self, int idx, void *item);					// 设置指定索引的数据, 数据所指内存的释放方式为free
	void (*ffset)(Vector * const self, int idx, void *item,					// 设置指定索引的数据, 数据所指内存的释放方式为freeMethod
		void(*freeMethod)(void *));
	void(*add)(Vector * const self, void *item);							// 在末尾添加数据, 数据所指向的内存不会释放
	void(*fadd)(Vector * const self, void *item);							// 在末尾添加数据, 会使用free来释放数据所指向的内存
	void(*ffadd)(Vector *const self, void *item, void(*freeMethod)(void *));// 在末尾添加数据, 会使用freeMethod来释放数据所指向的内存
	void(*insert)(Vector * const self, int idx, void *item);				// 在指定索引位置插入数据, 数据所指向的内存不会释放
	void(*finsert)(Vector * const self, int idx, void *item);				// 在指定索引位置插入数据, 会使用free来释放数据所指向的内存
	void(*ffinsert)(Vector * const self, int idx, void *item,				// 在指定索引位置插入数据, 会使用freeMethod来释放数据所指向的内存
		void(*freeMethod)(void *));				
	void (*remove)(Vector * const self, int idx);							// 删除指定索引的数据
	int(*size)(Vector * const self);										// 返回动态数组大小
	void(*clean)(Vector * const);											// 清空动态数组，【未实现】
	int(*contain)(Vector * const, void * obj, int(*cmp)(void*, void *));	// 判断对象是否存在, 【未实现】
	void *(*toArray)(Vector *const self);									// 转换为数组, 【未实现】
	String *(*toString)(Vector *const self);								// 将Vector中的object转换为String

	// private
	void(*_resize)(Vector * const self, int target);
};

#endif