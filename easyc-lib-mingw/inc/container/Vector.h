#ifndef __VECTOR_H
#define __VECTOR_H

// �ṹ����
struct Vector;
typedef struct Vector Vector;

// �������������
Vector *newVector();
Vector *newVectorByInts(int *ptr, int length);
Vector *newVectorByNumber(int number, int length);
Vector *newVectorByVector(Vector *ovect);
void removeVector(Vector *vector);

// �ṹ����
struct Vector{
	int _size;
	int _capacity;
	float _loadFactor;
	void ** _mem;

	// public(interface)
	void * (* get)(Vector *self, int idx);								// ��ȡָ������������
	void * (* set)(Vector *self, int idx, void *obj);					// ����ָ������������
	void(*add)(Vector *self, void *obj);								// ��ĩβ�������
	void * (*remove)(Vector *self, int idx);							// ɾ��ָ������������
	void(*insert)(Vector *self, int idx, void *obj);					// ��ָ������λ�ò�������
	int (*size)(Vector *self);											// ���ض�̬�����С
	void(*clean)(void *self);											// ��ն�̬���飬��δʵ�֡�
	int (*contain)(void *self, void * obj, int (*cmp)(void*, void *));	// �ж϶����Ƿ����, ��δʵ�֡�


	// private
	void(*_resize)(Vector *self);
};

#endif