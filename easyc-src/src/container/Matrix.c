#include <stdio.h>
#include <Windows.h>

#include "Vector.h"
#include "Object.h"
#include "Matrix.h"

static void *get(Matrix * const self, int m, int n);
static void *set(Matrix * const self, int m, int n, void *val);

static int rowSize(Matrix * const self);
static int colSize(Matrix * const self);
static int totalSize(Matrix * const self);

/*
* @Desc   : Matrix构造器。分配Matrix空间，装载函数。
* @Return : 返回新的构建好的Matrix
* @Authro : Shuaiji Lu
* @Date   : 2017/11/26
*/
static Matrix *newMatrix(){
	Matrix *mat = (Matrix *)malloc(sizeof(Matrix));
	ZeroMemory(mat, sizeof(Matrix));
	mat->_relative = newVector();

	// load function
	mat->get = get;
	mat->set = set;
	mat->rowSize = rowSize;
	mat->colSize = colSize;
	mat->totalSize = totalSize;
	return mat;
}

/*
* @Desc   : Matrix构造器。生成一个指定大小的矩阵，并且每个矩阵的元素为指定的int值。
* @Param  : number, 填充Matrix的每个元素的数据。
* @Param  : rows, Matrix的行数
* @Param  : cols, Matrix的列数
* @Return : 返回新的构建好的Vector
* @Authro : Shuaiji Lu
* @Date   : 2017/11/26
*/
Matrix *newMatrixByNumber(int number, int rows, int cols){
	Matrix * mat = newMatrix();
	mat->_mem = (Object ***)malloc(sizeof(Object **) * rows);
	for (int i = 0; i < rows; i++){
		mat->_mem[i] = (Object **)malloc(sizeof(Object *) * cols);
		for (int j = 0; j < cols; j++){
			mat->_mem[i][j] = simpleObject(number);
		}
	}
	mat->_colLength = cols;
	mat->_rowLength = rows;
	return mat;
}

/*
* @Desc   : 释放Matrix容器空间
* @Param  : *mat, 需要释放的Matrix实例
* @Return : void, 无返回值
* @Authro : Shuaiji Lu
* @Date   : 2017/11/26
*/
void freeMatrix(Matrix * const mat){
	for (int i = 0; i < mat->_rowLength; i++){
		for (int j = 0; j < mat->_colLength; j++){
			freeObject(mat->_mem[i][j]);
		}
		free(mat->_mem[i]);
	}
	freeVector(mat->_relative);
	free(mat);
}

/*
* @Desc   : 获得矩阵中指定位置的元素
* @Param  : *self, 待操作的Matrix
* @Param  : m, 指定待获取元素的行
* @Param  : n, 指定待获取元素的列
* @Return : 返回新的构建好的Vector
* @Authro : Shuaiji Lu
* @Date   : 2017/11/26
*/
void *get(Matrix * const self, int m, int n){
	if (m >= self->_rowLength || n >= self->_colLength){
		return NULL;
	}
	return self->_mem[m][n]->item;
}

/*
* @Desc   : 设置Matrix中指定位置的值
* @Param  : *self, 待操作的Matrix
* @Param  : m, 指定需要设置的元素的列
* @Param  : n, 指定需要设置的元素的行
* @Return : 该位置以前的元素
* @Authro : Shuaiji Lu
* @Date   : 2017/11/26
*/
void *set(Matrix * const self, int m, int n, void *val){
	if (m >= self->_rowLength || n>=self->_colLength){
		return NULL;
	}
	void * old = self->_mem[m][n]->item;
	self->_mem[m][n]->item = val;
	return old;
}

/*
* @Desc   : 获取Matrix的行数
* @Param  : *self, 待操作的Matrix
* @Return : 返回Matrix的行数
* @Authro : Shuaiji Lu
* @Date   : 2017/11/26
*/
int rowSize(Matrix * const self){
	return self->_rowLength;
}

/*
* @Desc   : 获取Matrix的列数
* @Param  : *self, 待操作的Matrix
* @Return : 返回Matrix的列数
* @Authro : Shuaiji Lu
* @Date   : 2017/11/26
*/
int colSize(Matrix * const self){
	return self->_colLength;
}


/*
* @Desc   : 获取Matrix的总元素数
* @Param  : *self, 待操作的Matrix
* @Return : 返回Matrix的总元素数
* @Authro : Shuaiji Lu
* @Date   : 2017/11/26
*/
int totalSize(Matrix * const self){
	return self->_colLength*self->_rowLength;
}
