//#include <stdio.h>
//#include <stdlib.h>
//#include <math.h>
//
//#include "canny.h"
//#include "Matrix.h"
//#include "Vector.h"
//
//Matrix *gaussianKernel(const int size, const double sigma){
//	const double PI = 4.0*atan(1.0);
//	int center = size / 2;
//	double sum = 0;
//	Matrix *gaus = newMatrixByNumber(0, size, size);
//	for (int i = 0; i < size; i++){
//		for (int j = 0; j < size; j++){
//			double val = (1 / (2 * PI*sigma*sigma))*exp(-((i - center)*(i - center) + (j - center)*(j - center)) / (2 * sigma*sigma));
//			gaus->setFloat(gaus, i, j, val);
//			sum += val;
//		}
//	}
//
//	for (int i = 0; i < size; i++){
//		for (int j = 0; j < size; j++){
//			gaus->setFloat(gaus, i, j, (*(double*)gaus->get(gaus, i, j)) / sum);
//		}
//	}
//	return gaus;
//}
//
//
//Matrix *gaussianFilter(const Matrix * const source, Matrix *gaus){
//	int size = gaus->colSize(gaus);
//	Matrix *imageGaussian = newMatrixByNumber(0, source->rowSize(source), source->colSize(source));
//	double *gausArray = (double *)malloc(sizeof(double)*size*size);
//
//	for (int i = 0; i<size*size; i++){
//		gausArray[i] = 0;  //赋初值，空间分配  
//	}
//	for (int i = 0; i<size; i++){
//		for (int j = 0; j<size; j++){
//			gausArray[i*size + j] = *(double *)gaus->get(gaus, i, j);//二维数组到一维 方便计算  
//		}
//	}
//
//	//滤波  
//	for (int i = 0; i<source->rowSize(source); i++)
//	{
//		for (int j = 0; j<source->colSize(source); j++)
//		{
//			int k = 0;
//			for (int l = -size / 2; l <= size / 2; l++)
//			{
//				for (int g = -size / 2; g <= size / 2; g++)
//				{
//					//以下处理针对滤波后图像边界处理，为超出边界的值赋值为边界值  
//					int row = i + l;
//					int col = j + g;
//					row = row<0 ? 0 : row;
//					row = row >= source->rowSize(source) ? source->rowSize(source) - 1 : row;
//					col = col<0 ? 0 : col;
//					col = col >= source->colSize(source) ? source->colSize(source) - 1 : col;
//					//卷积和
//					int val = gausArray[k] * (int)source->get(source, row, col);
//					int tmp = imageGaussian->get(imageGaussian, i, j);
//					imageGaussian->set(imageGaussian, i, j, tmp + val);
//					k++;
//				}
//			}
//		}
//	}
//
//	return imageGaussian;
//}
//
//const Vector * sobelGradDirction(const Matrix * source){
//	Vector *result = newVector();
//	Vector *pd = newVectorByNumber(0, (source->rowSize(source) - 1) * (source->colSize(source) - 1));
//	Matrix *imgSobX = newMatrixByNumber(0, source->rowSize(source) - 1, source->colSize(source) - 1);
//	Matrix *imgSobY = newMatrixByNumber(0, source->rowSize(source), source->colSize(source));
//
//	for (int i = 1; i < source->rowSize(source); i++){
//		for (int j = 1; j < source->colSize(source); j++){
//			
//		}
//	}
//
//	result->ffadd(result, imgSobX, freeMatrix);
//	result->ffadd(result, imgSobY, freeMatrix);
//	result->ffadd(result, pd, freeVector);
//
//	return result;
//}
//
//Matrix *sobelAmplitude(const Matrix *imgGradX, const Matrix *imgGradY){
//	Matrix *sobelAmpXY = newMatrixByNumber(0, imgGradX->rowSize(imgGradX), imgGradX->colSize(imgGradX));
//
//	for (int i = 0; i < sobelAmpXY->rowSize(sobelAmpXY); i++){
//		for (int j = 0; j < sobelAmpXY->colSize(sobelAmpXY); j++){
//			double v1 = *(double *)imgGradX->get(imgGradX, i, j);
//			double v2 = *(double *)imgGradY->get(imgGradY, i, j);
//			double val = sqrt(v1*v1 + v2*v2);
//			sobelAmpXY->set(sobelAmpXY, i, j, (int)val);
//		}
//	}
//
//	// convert?????????????????
//	return sobelAmpXY;
//}
//
//Matrix *LocalMaxValue(const Matrix *imageInput, Vector *pd)
//{
//	Matrix *imageOutput = newMatrixByMatrix(imageInput);
//
//	int k = 0;
//	for (int i = 1; i<imageInput->rowSize(imageInput) - 1; i++)
//	{
//		for (int j = 1; j<imageInput->colSize(imageInput) - 1; j++)
//		{
//			int value00 = imageInput->get(imageInput, (i - 1), j - 1);
//			int value01 = imageInput->get(imageInput, (i - 1), j);
//			int value02 = imageInput->get(imageInput, (i - 1), j + 1);
//			int value10 = imageInput->get(imageInput, (i), j - 1);
//			int value11 = imageInput->get(imageInput, (i), j);
//			int value12 = imageInput->get(imageInput, (i), j + 1);
//			int value20 = imageInput->get(imageInput, (i + 1), j - 1);
//			int value21 = imageInput->get(imageInput, (i + 1), j);
//			int value22 = imageInput->get(imageInput, (i + 1), j + 1);
//
//			if (pd->get(pd, k)>0 && pd->get(pd, k) <= 45)
//			{
//				double tmp1 = *(double *)pd->get(pd, i*imageOutput->rowSize(imageOutput) + j);
//				double tmp2 = *(double *)pd->get(pd, i*imageOutput->rowSize(imageOutput) + j);
//				if (value11 <= (value12 + (value02 - value12)*tan(tmp1)) || (value11 <= (value10 + (value20 - value10)*tan(tmp2))))
//				{
//					imageOutput->set(imageInput, i, j, 0);
//				}
//			}
//			if (pd->get(pd, k)>45 && pd->get(pd, k) <= 90)
//			{
//				double tmp1 = *(double *)pd->get(pd, i*imageOutput->colSize(imageOutput) + j);
//				double tmp2 = *(double *)pd->get(pd, i*imageOutput->colSize(imageOutput) + j);
//				if (value11 <= (value01 + (value02 - value01) / tan(tmp1)) || value11 <= (value21 + (value20 - value21) / tan(tmp2)))
//				{
//					imageOutput->set(imageOutput, i, j, 0);
//
//				}
//			}
//			if (pd->get(pd, k)>90 && pd->get(pd, k) <= 135)
//			{
//				double tmp1 = *(double *)pd->get(pd, i*imageOutput->colSize(imageOutput) + j);
//				double tmp2 = *(double *)pd->get(pd, i*imageOutput->colSize(imageOutput) + j);
//				if (value11 <= (value01 + (value00 - value01) / tan(180 - tmp1)) || value11 <= (value21 + (value22 - value21) / tan(180 - tmp2)))
//				{
//					imageOutput->set(imageOutput, i, j, 0);
//				}
//			}
//			if (pd->get(pd, k)>135 && pd->get(pd, k) <= 180)
//			{
//				double tmp1 = *(double *)pd->get(pd, i*imageOutput->colSize(imageOutput) + j);
//				double tmp2 = *(double *)pd->get(pd, i*imageOutput->colSize(imageOutput) + j);
//				if (value11 <= (value10 + (value00 - value10)*tan(180 - tmp1)) || value11 <= (value12 + (value22 - value11)*tan(180 - tmp2)))
//				{
//					imageOutput->set(imageOutput, i, j, 0);
//				}
//			}
//			k++;
//		}
//	}
//	return imageOutput;
//}
//
//void DoubleThreshold(Matrix *input, double lowThreshold, double highThreshold)
//{
//	for (int i = 0; i<input->rowSize(input); i++)
//	{
//		for (int j = 0; j<input->colSize(input); j++)
//		{
//			if ((int)input->get(input, i, j) > highThreshold)
//			{
//				input->set(input, i, j, 255);
//			}
//			else if ((int)input->get(input, i, j) < lowThreshold)
//			{
//				input->set(input, i, j, 0);
//			}
//			else{
////				input->set(input, i, j, 0);
//			}
//		}
//	}
//}