#include <stdio.h>
#include <Windows.h>
#include "Matrix.h"

static void *get(Matrix *self, int m, int n);
static void *set(Matrix *self, int m, int n, void *val);

static int rowSize(Matrix *self);
static int colSize(Matrix *self);
static int totalSize(Matrix *self);

Matrix *newMatrix(){
	Matrix *mat = (Matrix *)malloc(sizeof(Matrix));
	ZeroMemory(mat, sizeof(Matrix));
	
	// load function
	mat->get = get;
	mat->set = set;
	mat->rowSize = rowSize;
	mat->colSize = colSize;
	mat->totalSize = totalSize;
	return mat;
}
Matrix *newMatrixByNumber(int number, int rows, int cols){
	Matrix * mat = newMatrix();
	mat->_mem = (void ***)malloc(sizeof(void **) * rows);
	for (int i = 0; i < rows; i++){
		mat->_mem[i] = (void **)malloc(sizeof(void *) * cols);
		for (int j = 0; j < cols; j++){
			mat->_mem[i][j] = number;
		}
	}
	mat->_colLength = cols;
	mat->_rowLength = rows;
	return mat;
}
void removeMatrix(Matrix *mat){

}

void *get(Matrix *self, int m, int n){
	if (m >= self->_rowLength || n >= self->_colLength){
		return NULL;
	}
	return self->_mem[m][n];
}
void *set(Matrix *self, int m, int n, void *val){
	if (m >= self->_rowLength || n>=self->_colLength){
		return NULL;
	}
	void * old = self->_mem[m][n];
	self->_mem[m][n] = val;
	return old;
}

int rowSize(Matrix *self){
	return self->_rowLength;
}
int colSize(Matrix *self){
	return self->_colLength;
}
int totalSize(Matrix *self){
	return self->_colLength*self->_rowLength;
}
