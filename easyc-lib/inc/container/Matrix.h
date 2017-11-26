#ifndef __MATRIX_H
#define __MATRIX_H

struct Matrix;
typedef struct Matrix Matrix;

// 构造和析构
Matrix *newMatrix();
Matrix *newMatrixByNumber(int number, int rows, int cols);
void removeMatrix(Matrix *mat);

struct Matrix{
	int _rowLength;
	int _colLength;
	void ***_mem;

	void *(* get)(Matrix *self, int m, int n);
	void *(* set)(Matrix *self, int m, int n, void *val);

	int(*rowSize)(Matrix *self);
	int(*colSize)(Matrix *self);
	int(*totalSize)(Matrix *self);
};

#endif