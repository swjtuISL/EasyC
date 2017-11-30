#ifndef __IMAGE_CANNY_H
#define __IMAGE_CANNY_H

struct Matrix;
struct Vector;
typedef struct Matrix Matrix;
typedef struct Vector Vector;

Matrix *gaussianKernel(const int size, const double sigma);
Matrix *gaussianFilter(const Matrix * const source, Matrix *gaus);
const Vector * sobelGradDirction(const Matrix * source);
Matrix *sobelAmplitude(const Matrix *imgGradX, const Matrix *imgGradY);
Matrix *LocalMaxValue(const Matrix *imageInput, double *pointDrection);
void DoubleThreshold(Matrix *input, double lowThreshold, double highThreshold);

#endif