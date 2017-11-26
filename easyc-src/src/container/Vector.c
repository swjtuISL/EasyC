#include <stdlib.h>
#include <Windows.h>
#include "Vector.h"

static const INITIAL_CAPACITY = 16;
static const float DEFAULT_LOAD_FACTOR = 0.75f;

static void * get(Vector * const self, int idx);
static void * set(Vector * const self, int idx, void *obj);
static void add(Vector * const self, void *obj);
static void * remove(Vector * const self, int idx);
static void insert(Vector * const self, int idx, void *obj);
static int size(Vector * const self);
static void resize(Vector * const self);

/*
* @Desc   : Vector构造器。构造一个无元素的Vector实例。
* @Return : 返回新的构建好的Vector
* @Authro : 卢帅吉
* @Date   : 2017.11.26
*/
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

/*
* @Desc   : Vector构造器.通过整数数组的首地址和长度, 构造一个Vector.
* @Param  : *ptr, 数组的首元素地址
* @Param  : length, 数组长度
* @Return : 返回新的构建好的Vector
* @Authro : 卢帅吉
* @Date   : 2017.11.26
*/
Vector *newVectorByInts(int *ptr, int length){
	Vector *vector = newVector();
	for (int i = 0; i < length; i++, ptr++){
		vector->add(vector, *ptr);
	}
	return vector;
}

/*
* @Desc   : Vector构造器.构造一个长度为length,所有元素为整数number的Vector.
* @Param  : number, 填充Vector的数值.
* @Param  : length, 填充的长度.
* @Return : 返回新的构建好的Vector.
* @Authro : 卢帅吉
* @Date   : 2017.11.26
*/
Vector *newVectorByNumber(int number, int length){
	Vector *vector = newVector();
	for (int i = 0; i < length; i++){
		vector->add(vector, number);
	}
	return vector;
}

/*
 * @Desc   : Vector构造器.通过一个Vector构造另外一个Vector, 新Vector的元素和原Vector的元素相同.
 * @Param  : ovect, 原始的Vector.
 * @Return : 返回新的构建好的Vector.
 * @Authro : 卢帅吉
 * @Date   : 2017.11.25
*/
Vector *newVectorByVector(Vector * const ovect){
	Vector *vector = newVector();
	for (int i = 0; i < ovect->size(ovect); i++){
		vector->add(vector, ovect->get(ovect, i));
	}
	return vector;
}

/*
* @Desc   : 释放Vector容器, 只释放容器并不释放其中的指针所指向的内存.
* @Param  : *vector, 待释放的Vector容器
* @Return : 无
* @Authro : 卢帅吉
* @Date   : 2017.11.26
*/
void freeVector(Vector * const vector){
	free(vector->_mem);
	vector->_mem = NULL;
	free(vector);
}

/*
* @Desc   : 释放所有的Vector, 值释放这些Vector容器, 并不释放其中指针所指向的内存.
* @Param  : vector, vector中的元素为待释放的vector实例.
* @Return : 无
* @Authro : 卢帅吉
* @Date   : 2017.11.26
*/
void freeAllVector(Vector * const vector){
	for (int i = 0; i < vector->_size; i++){
		freeVector(vector->get(vector, i));
	}
}

/*
* @Desc   : 获得指定索引位置处的元素.
* @Param  : *self, 待操作的vector.
* @Param  : idx, 获得该索引处的元素.
* @Return : 索引处的元素.
* @Authro : 卢帅吉
* @Date   : 2017.11.26
*/
static void * get(Vector * const self, int idx){
	if (idx >= self->_size){
		return NULL;
	}
	return self->_mem[idx];
}


/*
* @Desc   : 给指定位置进行赋值, 返回该位置原先的元素.
* @Param  : *self, 待操作的vector.
* @Param  : idx, 待赋值的位置.
* @Param  : *obj, 赋值到vector的元素.
* @Return : 返回新的构建好的Vector
* @Authro : 卢帅吉
* @Date   : 2017.11.26
*/
static void * set(Vector * const self, int idx, void *obj){
	if (idx >= self->_size){
		return NULL;
	}
	void * old = self->_mem[idx];
	self->_mem[idx] = obj;
	return old;
}

/*
* @Desc   : 在末尾添加一格新元素.
* @Param  : *self, 待操作的vector.
* @Param  : length, 填充的长度.
* @Return : 无
* @Authro : 卢帅吉
* @Date   : 2017.11.26
*/
static void add(Vector * const self, void *obj){
	self->_resize(self);
	self->_mem[self->_size] = obj;
	self->_size += 1;
}

/*
* @Desc   : 删除指定索引位置的元素，将该索引后面的元素往前面移动一格, 并且返回被删除的元素.
* @Param  : *self, 待操作的vector.
* @Param  : idx, 待删除的索引位置.
* @Return : 返回被删除的元素.
* @Authro : 卢帅吉
* @Date   : 2017.11.26
*/
static void * remove(Vector * const self, int idx){
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

/*
* @Desc   : 在指定的位置插入一个元素, 该位置后面的所有元素往后面移动一格.
* @Param  : *self, 待操作的vector.
* @Param  : idx, 在该索引位置插入.
* @Return : 无
* @Authro : 卢帅吉
* @Date   : 2017.11.26
*/
static void insert(Vector * const self, int idx, void *obj){
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

/*
* @Desc   : 得到vector中的元素个数.
* @Param  : *self, 待操作的vector.
* @Return : vector中存在的元素个数.
* @Authro : 卢帅吉
* @Date   : 2017.11.26
*/
static int size(Vector * const self){
	return self->_size;
}

/*
* @Desc   : vector扩容. 当vector中再增加一个元素达到capacity*loadFactor时, 将进行扩容操作.
* @Param  : *self, 待操作的vector.
* @Return : 无
* @Authro : 卢帅吉
* @Date   : 2017.11.26
*/
static void resize(Vector * const self){
	if ( (self->_size+1) < self->_capacity * self->_loadFactor){
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