#include <stdio.h>
#include <Windows.h>

#include "Vector.h"
#include "Object.h"
#include "Matrix.h"
#include "sysser.h"

static void *get(Matrix * const self, int m, int n);
static int getInt(Matrix * const self, int m, int n);
static double getFloat(Matrix * const self, int m, int n);

static void set(Matrix * const self, int m, int n, void *val);
static void setInt(Matrix * const self, int m, int n, int val);
static void setFloat(Matrix * const self, int m, int n, double val);
static void setObject(Matrix * const self, int m, int n, void(*freeMethod)(void *), String *(itemToString)(void *));

static int rowSize(Matrix * const self);
static int colSize(Matrix * const self);
static int totalSize(Matrix * const self);

static String *toString(Matrix *self);

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
	mat->getInt = getInt;
	mat->getFloat = getFloat;

	mat->set = set;
	mat->setInt = setInt;
	mat->setFloat = setFloat;
	mat->setObject = setObject;

	mat->rowSize = rowSize;
	mat->colSize = colSize;
	mat->totalSize = totalSize;

	mat->toString = toString;
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
			mat->_mem[i][j] = newIntObject(number);
		}
	}
	mat->_cols = cols;
	mat->_rows = rows;
	return mat;
}

/*
* @Desc   : 
* @Param  : 
* @Return : 
* @Authro : Shuaiji Lu
* @Date   : 2017/11/30
*/
Matrix *newMatrixByArray(int tarray[][8], int rows, int cols){
	Matrix * mat = newMatrix();
	mat->_mem = (Object ***)malloc(sizeof(Object **) * rows);
	for (int i = 0; i < rows; i++){
		mat->_mem[i] = (Object **)malloc(sizeof(Object *) * cols);
		for (int j = 0; j < cols; j++){
			mat->_mem[i][j] = newIntObject(tarray[i][j]);
		}
	}
	mat->_cols = cols;
	mat->_rows = rows;
	return mat;
}

/*
* @Desc   :
* @Param  :
* @Return :
* @Authro : Shuaiji Lu
* @Date   : 2017/11/30
*/
Matrix *newMatrixByMatrix(Matrix *omat){
	int rows = omat->_rows;
	int cols = omat->_cols;
	Matrix * mat = newMatrix();
	mat->_mem = (Object ***)malloc(sizeof(Object **) * rows);
	for (int i = 0; i < rows; i++){
 		mat->_mem[i] = (Object **)malloc(sizeof(Object *) * cols);
		for (int j = 0; j < cols; j++){
			mat->_mem[i][j] = simpleObject(omat->get(omat, i, j));
		}
	}
	mat->_cols = cols;
	mat->_rows = rows;
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
	if (mat->_relative){
		freeVector(mat->_relative);
	}
	for (int i = 0; i < mat->_rows; i++){
		for (int j = 0; j < mat->_cols; j++){
			freeObject(mat->_mem[i][j]);
		}
		free(mat->_mem[i]);
	}
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
	if (m >= self->_rows || n >= self->_cols){
		reportError("【错误】Matrix.get索引超出范围", 1);
	}
	return self->_mem[m][n]->item;
}

/*
* @Desc   :
* @Param  :
* @Return :
* @Authro : Shuaiji Lu
* @Date   : 2017/11/30
*/
static int getInt(Matrix * const self, int m, int n){
	if (m >= self->_rows || n >= self->_cols){
		reportError("【错误】Matrix.get索引超出范围", 1);
	}
	return self->_mem[m][n]->item;
}

/*
* @Desc   :
* @Param  :
* @Return :
* @Authro : Shuaiji Lu
* @Date   : 2017/11/30
*/
static double getFloat(Matrix * const self, int m, int n){
	if (m >= self->_rows || n >= self->_cols){
		reportError("【错误】Matrix.get索引超出范围", 1);
	}
	return *(double *)self->_mem[m][n]->item;
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
void set(Matrix * const self, int m, int n, void *item){
	if (m >= self->_rows || n >= self->_cols){
		reportError("【错误】Matrix.set索引超出范围", 1);
	}
	Object * old = self->_mem[m][n];
	if (old != NULL){
		freeObject(old);
	}
	self->_mem[m][n] = simpleObject(item);
}

/*
* @Desc   :
* @Param  :
* @Return :
* @Authro : Shuaiji Lu
* @Date   : 2017/11/30
*/
void fset(Matrix * const self, int m, int n, void *item){
	if (m >= self->_rows || n >= self->_cols){
		reportError("【错误】Matrix.set索引超出范围", 1);
	}
	Object * old = self->_mem[m][n];
	if (old != NULL){
		freeObject(old);
	}
	self->_mem[m][n] = newObject(item, free, NULL, NULL);
}

/*
* @Desc   :
* @Param  :
* @Return :
* @Authro : Shuaiji Lu
* @Date   : 2017/11/30
*/
static void setInt(Matrix * const self, int m, int n, int item){
	if (m >= self->_rows || n >= self->_cols){
		reportError("【错误】Matrix.set索引超出范围", 1);
	}
	Object * old = self->_mem[m][n];
	if (old != NULL){
		freeObject(old);
	}
	self->_mem[m][n] = newIntObject(item);
}

/*
* @Desc   :
* @Param  :
* @Return :
* @Authro : Shuaiji Lu
* @Date   : 2017/11/30
*/
static void setFloat(Matrix * const self, int m, int n, double item){
	if (m >= self->_rows || n >= self->_cols){
		reportError("【错误】Matrix.set索引超出范围", 1);
	}
	Object * old = self->_mem[m][n];
	if (old != NULL){
		freeObject(old);
	}
	self->_mem[m][n] = newFloatObject(item);
}

/*
* @Desc   :
* @Param  :
* @Return :
* @Authro : Shuaiji Lu
* @Date   : 2017/11/30
*/
static void setObject(Matrix * const self, int m, int n, void *item, void(*freeMethod)(void *), String *(itemToString)(void *), void*(*itemCopy)(void *)){
	if (m >= self->_rows || n >= self->_cols){
		reportError("【错误】Matrix.set索引超出范围", 1);
	}
	Object * old = self->_mem[m][n];
	if (old != NULL){
		freeObject(old);
	}
	self->_mem[m][n] = newObject(item, freeMethod, itemToString, itemCopy);
}

/*
* @Desc   : 获取Matrix的行数
* @Param  : *self, 待操作的Matrix
* @Return : 返回Matrix的行数
* @Authro : Shuaiji Lu
* @Date   : 2017/11/26
*/
int rowSize(Matrix * const self){
	return self->_rows;
}

/*
* @Desc   : 获取Matrix的列数
* @Param  : *self, 待操作的Matrix
* @Return : 返回Matrix的列数
* @Authro : Shuaiji Lu
* @Date   : 2017/11/26
*/
int colSize(Matrix * const self){
	return self->_cols;
}


/*
* @Desc   : 获取Matrix的总元素数
* @Param  : *self, 待操作的Matrix
* @Return : 返回Matrix的总元素数
* @Authro : Shuaiji Lu
* @Date   : 2017/11/26
*/
int totalSize(Matrix * const self){
	return self->_cols*self->_rows;
}

/*
* @Desc   :
* @Param  :
* @Return :
* @Authro : Shuaiji Lu
* @Date   : 2017/11/30
*/
String *toString(Matrix *self){
	String *s = newString("");
	for (int i = 0; i < self->_rows; i++){
		for (int j = 0; j < self->_cols; j++){
			Object *obj = self->_mem[i][j];
			String *part = obj->toString(obj);
			s->appendString(s, part)->append(s, ", ");
		}
		s->append(s, "\n");
	}
	if (self->_relative == NULL){
		self->_relative = newVector();
	}
	self->_relative->addObject(self->_relative, s, freeString, NULL, NULL);
	return s;
}