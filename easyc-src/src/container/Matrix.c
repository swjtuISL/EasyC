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
* @Desc   : Matrix������������Matrix�ռ䣬װ�غ�����
* @Return : �����µĹ����õ�Matrix
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
* @Desc   : Matrix������������һ��ָ����С�ľ��󣬲���ÿ�������Ԫ��Ϊָ����intֵ��
* @Param  : number, ���Matrix��ÿ��Ԫ�ص����ݡ�
* @Param  : rows, Matrix������
* @Param  : cols, Matrix������
* @Return : �����µĹ����õ�Vector
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
* @Desc   : �ͷ�Matrix�����ռ�
* @Param  : *mat, ��Ҫ�ͷŵ�Matrixʵ��
* @Return : void, �޷���ֵ
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
* @Desc   : ��þ�����ָ��λ�õ�Ԫ��
* @Param  : *self, ��������Matrix
* @Param  : m, ָ������ȡԪ�ص���
* @Param  : n, ָ������ȡԪ�ص���
* @Return : �����µĹ����õ�Vector
* @Authro : Shuaiji Lu
* @Date   : 2017/11/26
*/
void *get(Matrix * const self, int m, int n){
	if (m >= self->_rows || n >= self->_cols){
		reportError("������Matrix.get����������Χ", 1);
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
		reportError("������Matrix.get����������Χ", 1);
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
		reportError("������Matrix.get����������Χ", 1);
	}
	return *(double *)self->_mem[m][n]->item;
}

/*
* @Desc   : ����Matrix��ָ��λ�õ�ֵ
* @Param  : *self, ��������Matrix
* @Param  : m, ָ����Ҫ���õ�Ԫ�ص���
* @Param  : n, ָ����Ҫ���õ�Ԫ�ص���
* @Return : ��λ����ǰ��Ԫ��
* @Authro : Shuaiji Lu
* @Date   : 2017/11/26
*/
void set(Matrix * const self, int m, int n, void *item){
	if (m >= self->_rows || n >= self->_cols){
		reportError("������Matrix.set����������Χ", 1);
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
		reportError("������Matrix.set����������Χ", 1);
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
		reportError("������Matrix.set����������Χ", 1);
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
		reportError("������Matrix.set����������Χ", 1);
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
		reportError("������Matrix.set����������Χ", 1);
	}
	Object * old = self->_mem[m][n];
	if (old != NULL){
		freeObject(old);
	}
	self->_mem[m][n] = newObject(item, freeMethod, itemToString, itemCopy);
}

/*
* @Desc   : ��ȡMatrix������
* @Param  : *self, ��������Matrix
* @Return : ����Matrix������
* @Authro : Shuaiji Lu
* @Date   : 2017/11/26
*/
int rowSize(Matrix * const self){
	return self->_rows;
}

/*
* @Desc   : ��ȡMatrix������
* @Param  : *self, ��������Matrix
* @Return : ����Matrix������
* @Authro : Shuaiji Lu
* @Date   : 2017/11/26
*/
int colSize(Matrix * const self){
	return self->_cols;
}


/*
* @Desc   : ��ȡMatrix����Ԫ����
* @Param  : *self, ��������Matrix
* @Return : ����Matrix����Ԫ����
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