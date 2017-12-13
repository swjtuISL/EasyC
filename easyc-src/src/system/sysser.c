//#define UNICODE 

#include <stdio.h>
#include <stdarg.h>
#include <String.h>
#include <Windows.h>
#include "InputStream.h"
#include "sysser.h"
#include "winser.h"
#include "Vector.h"

#define MESSAGE_MAX_LENGTH 8192

InputStream *getStdInputStream(){
	return newInputStream(GetStdHandle(STD_INPUT_HANDLE));
}

OutputStream *getStdOutputStream(){
	return newOutputStream(GetStdHandle(STD_OUTPUT_HANDLE));
}

OutputStream *getStdErrorStream(){
	return  newOutputStream(GetStdHandle(STD_ERROR_HANDLE));
}

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
		vector->addInt(vector, va_arg(head, int));
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

void reportError(char* userMessage, unsigned long exitCode){
	TCHAR um[MESSAGE_MAX_LENGTH];
	LPTSTR lpvSysMsg;
	DWORD errNum = GetLastError();			// 获得错误代码

	str2tstr(userMessage, um);
	fprintf(stderr, TEXT("%s\n"), um);
	DWORD eMsgLen = FormatMessage(			// 格式化错误信息
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, errNum,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpvSysMsg, 0, NULL);
	if (eMsgLen > 0){
		fprintf(stderr, TEXT("%s\n"), lpvSysMsg);
	}
	else{
		fprintf(stderr, TEXT("Last Error Number : %d.\n"), errNum);
	}

	if (exitCode > 0){
		ExitProcess(exitCode);
	}
	return;
}