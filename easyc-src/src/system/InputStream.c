#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "File.h"
#include "Vector.h"
#include "InputStream.h"
#include "sysser.h"

static int read(InputStream *self, unsigned char *rcv, int maxLength);
static int readByte(InputStream *self);

InputStream * newInputStream(HANDLE hi){
	InputStream *is = malloc(sizeof(InputStream));
	ZeroMemory(is, sizeof(InputStream));
	is->_hi = hi;

	// load function
	is->read = read;
	is->readByte = readByte;

	return is;
}

InputStream * newFileInputStream(File *file){
	HANDLE hd = file->openToRead(file);
	InputStream *is = newInputStream(hd);
	is->_file = file;
	return is;
}

void freeInputStream(InputStream *is){
	if (is->_file){
		freeFile(is->_file);
	}
	if (is->_hi != GetStdHandle(STD_INPUT_HANDLE)){
		CloseHandle(is->_hi);
	}
	free(is);
}

static int read(InputStream *self, unsigned char *rcv, int maxLength){
	int haveRead = 0;
	if (ReadFile(self->_hi, rcv, maxLength, &haveRead, NULL) == FALSE){
//		reportError("【错误】读取数据异常", 1);
		return -1;
	}
	return haveRead;
}

static int readByte(InputStream *self){
	int rcv = 0;
	if (self->_isFinish){		// 判断是否已经读完
		return -1;
	}
	int haveRead = self->read(self, &rcv, 1);
	if (haveRead){
		return rcv;
	}
	else{
		self->_isFinish = 1;
		return -1;
	}
}