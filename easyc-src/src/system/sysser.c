#include <stdio.h>
#include <stdarg.h>
#include <String.h>
#include "sysser.h"
#include "Vector.h"

/*
 * @Desc  : 包装fun的输入输出。传入的可变参数封装为Vector，再传给被包装的函数fun。需要注意的是Vector会在该函数返回前被销毁掉。
 * @Param : * fun, 被包装的函数
 * @Param : length, 可变参数长度，位于可变参数的前参数
 * @Return: 返回被包装的函数fun的返回值
 * @Author: Shuaiji Lu
 * @Date  : 2017/11/26
*/
void * funWrapperInts(void *(*fun)(Vector *vector), int length, ...){
	Vector *vector = newVector();
	va_list head;
	va_start(head, length);
	for (int i = 0; i < length; i++){
		vector->add(vector, va_arg(head, int));
	}
	va_end(head);
	void * obj = fun(vector);
	freeVector(vector);
	return obj;
}

void * funWrapperPtrs(void *(*fun)(Vector *vector), int length, ...){
	Vector *vector = newVector();
	va_list head;
	va_start(head, length);
	for (int i = 0; i < length; i++){
		vector->add(vector, va_arg(head, void *));
	}
	va_end(head);
	void * obj = fun(vector);
	freeVector(vector);
	return obj;
}