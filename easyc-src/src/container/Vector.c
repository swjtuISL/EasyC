#include <stdlib.h>
#include <Windows.h>
#include "Vector.h"

static const INITIAL_CAPACITY = 16;
static const float DEFAULT_LOAD_FACTOR = 0.75f;

static void * get(Vector *self, int idx);
static void * set(Vector *self, int idx, void *obj);
static void add(Vector *self, void *obj);
static void * remove(Vector *self, int idx);
static void insert(Vector *self, int idx, void *obj);
static int size(Vector *self);
static void resize(Vector *self);

// 创建Vector容器
Vector *newVector(){
	Vector * vector = (Vector *)malloc(sizeof(Vector));
	ZeroMemory(vector, sizeof(Vector));
	vector->_mem = (void **)malloc(sizeof(void *)*INITIAL_CAPACITY);
	for (int i = 0; i < INITIAL_CAPACITY; i++){
		vector->_mem[i] = NULL;
	}
	vector->_capacity = INITIAL_CAPACITY;
	vector->_loadFactor = DEFAULT_LOAD_FACTOR;
	vector->_size = 0;

	// load function
	vector->get = get;
	vector->set = set;
	vector->add = add;
	vector->insert = insert;
	vector->remove = remove;
	vector->size = size;
	vector->_resize = resize;
}

Vector *newVectorByInts(int *ptr, int length){
	Vector *vector = newVector();
	for (int i = 0; i < length; i++, ptr++){
		vector->add(vector, *ptr);
	}
	return vector;
}

Vector *newVectorByNumber(int number, int length){
	Vector *vector = newVector();
	for (int i = 0; i < length; i++){
		vector->add(vector, number);
	}
	return vector;
}

/*
 * @Desc   : Vector构造器。通过一个Vector构造另外一个Vector，新Vector的元素和原Vector的元素相同。
 * @Param  : ovect, 原始的Vector
 * @Return : 返回新的构建好的Vector
 * @Authro : Shuaiji Lu
 * @Date   : 2017.11.25
*/
Vector *newVectorByVector(Vector *ovect){
	Vector *vector = newVector();
	for (int i = 0; i < ovect->size(ovect); i++){
		vector->add(vector, ovect->get(ovect, i));
	}
	return vector;
}

// 只释放容器，里面元素并不会释放
void removeVector(Vector *vector){
	free(vector->_mem);
	vector->_mem = NULL;
	free(vector);
}

static void * get(Vector *self, int idx){
	if (idx >= self->_size){
		return NULL;
	}
	return self->_mem[idx];
}

static void * set(Vector *self, int idx, void *obj){
	if (idx >= self->_size){
		return NULL;
	}
	void * old = self->_mem[idx];
	self->_mem[idx] = obj;
	return old;
}

static void add(Vector *self, void *obj){
	self->_resize(self);
	self->_mem[self->_size] = obj;
	self->_size += 1;
}

static void * remove(Vector *self, int idx){
	if (idx >= self->_size){
		return NULL;
	}
	void *old = self->_mem[idx];
	for (int i = idx; i < self->_size-1; i++){
		self->_mem[i] = self->_mem[i+1];
	}
	self->_mem[self->_size - 1] = NULL;
	self->_size -= 1;
	return old;
}

static void insert(Vector *self, int idx, void *obj){
	if (idx >= self->_size+1){		// 可以插在末尾
		return NULL;
	}
	self->_resize(self);
	for (int i = idx; i < self->_size; i++){
		self->_mem[i + 1] = self->_mem[i];
	}
	self->_mem[idx] = obj;
	self->_size += 1;
}

static int size(Vector *self){
	return self->_size;
}

static void resize(Vector *self){
	if (self->_size < self->_capacity * self->_loadFactor){
		return;
	}
	int newcap = 2 * self->_capacity;
	void ** newmem = (void **)malloc(sizeof(void *) * newcap);
	for (int i = 0; i < newcap; i++){
		if (i < self->_capacity){
			newmem[i] = self->_mem[i];
		}
		else{
			newmem[i] = NULL;
		}
	}
	free(self->_mem);
	self->_mem = newmem;
	self->_capacity = newcap;
}