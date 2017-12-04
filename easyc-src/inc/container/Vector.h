#ifndef __VECTOR_H
#define __VECTOR_H

// �ṹ����
struct Vector;
struct Object;
struct String;
typedef struct Vector Vector;
typedef struct Object Object;
typedef struct String String;

// �������������
Vector *newVector();
Vector *newVectorByInts(int *ptr, int length);
Vector *newVectorByNumber(int number, int length);
Vector *newVectorByVector(Vector * const ovect);
void freeVector(Vector * const vector);
void freeAllVector(Vector * const vector);

// �ṹ����
struct Vector{
	int _size;
	int _capacity;
	float _loadFactor;
	Vector * _relative;
	Object ** _mem;

	// public(interface)
	void * (* get)(Vector * const self, int idx);
	int (*getInt)(Vector * const self, int idx);
	double (*getFloat)(Vector * const self, int idx);

	void(*set)(Vector * const self, int idx, void *item);
	void(*fset)(Vector * const self, int idx, void *item);
	void(*setInt)(Vector * const self, int idx, int item);
	void(*setFloat)(Vector * const self, int idx, double item);
	void(*setChars)(Vector * const self, int idx, char * item);
	void(*setObject)(Vector * const self, int idx, void *item,
		void(*freeMethod)(void *),
		String *(itemToString)(void *),
		void*(*itemCopy)(void *));

	void(*add)(Vector * const self, void *item);
	void(*fadd)(Vector * const self, void *item);
	void(*addInt)(Vector * const self, int item);
	void(*addFloat)(Vector * const self, double item);
	void(*addChars)(Vector * const self, char * item);
	void(*addObject)(Vector * const self, void *item,
		void(*freeMethod)(void *),
		String *(itemToString)(void *),
		void*(*itemCopy)(void *));

	void(*insert)(Vector * const self, int idx, void *item);
	void(*finsert)(Vector * const self, int idx, void *item);
	void(*insertInt)(Vector * const self, int idx, int item);
	void(*insertFloat)(Vector * const self, int idx, double item);
	void(*insertChars)(Vector * const self, int idx, char * item);
	void(*insertObject)(Vector * const self, int idx, void *item,
		void(*freeMethod)(void *),
		String *(itemToString)(void *),
		void*(*itemCopy)(void *));


	void (*remove)(Vector * const self, int idx);							// ɾ��ָ������������
	int(*size)(Vector * const self);										// ���ض�̬�����С
	void(*clean)(Vector * const);											// ��ն�̬���飬��δʵ�֡�
	int(*contain)(Vector * const, void * obj, int(*cmp)(void*, void *));	// �ж϶����Ƿ����, ��δʵ�֡�
	int    *(*toIntArray)(Vector *const self);
	double *(*toFloatArray)(Vector *const self);
	void   *(*toPtrArray)(Vector *const self);
	String *(*toString)(Vector *const self);								// ��Vector�е�objectת��ΪString

	// private
	void(*_resize)(Vector * const self, int target);
};

#endif