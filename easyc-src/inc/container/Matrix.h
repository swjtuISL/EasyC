#ifndef __MATRIX_H
#define __MATRIX_H

struct Matrix;
typedef struct Matrix Matrix;

// 构造和析构
Matrix *newMatrix();
Matrix *newMatrixByNumber(int number, int rows, int cols);
void freeMatrix(Matrix * const mat);

/*
* @Desc   : 固定行列大小的二维矩阵
* @Author : Shuaiji Lu
* @Date   : 2017.11.26
*/
struct Matrix{
	int _rowLength;
	int _colLength;
	void ***_mem;

	void *(*get)(Matrix * const self, int m, int n);
	void *(*set)(Matrix * const self, int m, int n, void *val);

	int(*rowSize)(Matrix * const self);
	int(*colSize)(Matrix * const self);
	int(*totalSize)(Matrix * const self);
};

#endif