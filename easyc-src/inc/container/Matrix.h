#ifndef __MATRIX_H
#define __MATRIX_H

struct Matrix;
struct Object;
struct Vector;
struct String;
typedef struct Matrix Matrix;
typedef struct Object Object;
typedef struct Vector Vector;
typedef struct String String;

// 构造和析构
Matrix *newMatrixByNumber(int number, int rows, int cols);
Matrix *newMatrixByArray(int **tarray, int rows, int cols);
Matrix *newMatrixByMatrix(Matrix *mat);
void freeMatrix(Matrix * const mat);

/*
* @Desc   : 固定行列大小的二维矩阵
* @Author : Shuaiji Lu
* @Date   : 2017/11/26
*/
struct Matrix{
	int _rows;
	int _cols;
	Object ***_mem;
	Vector *_relative;

	void *(*get)(Matrix * const self, int m, int n);
	int (*getInt)(Matrix * const self, int m, int n);
	double (*getFloat)(Matrix * const self, int m, int n);

	void(*set)(Matrix * const self, int m, int n, void *val);
	void(*fset)(Matrix * const self, int m, int n, void *val);
	void(*setInt)(Matrix * const self, int m, int n, int val);
	void(*setFloat)(Matrix * const self, int m, int n, double val);
	void(*setObject)(Matrix * const self, int m, int n, void *item, void(*freeMethod)(void *), String *(itemToString)(void *), void*(*itemCopy)(void *));

	int(*rowSize)(Matrix * const self);
	int(*colSize)(Matrix * const self);
	int(*totalSize)(Matrix * const self);

	String *(*toString)(Matrix *self);
};

#endif