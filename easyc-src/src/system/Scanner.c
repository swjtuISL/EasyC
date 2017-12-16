#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <memory.h>
#include "InputStream.h"
#include "String.h"
#include "Scanner.h"
#include "sysser.h"

static String *next(Scanner *self);
static String *nextLine(Scanner *self);
static int nextInt(Scanner *Self);
static double nextFloat(Scanner *Self);
static int readFromBuffer(Scanner *scanner, unsigned char *rcv, int maxLength);
static int hasNext(Scanner *self);

Scanner * newScanner(InputStream *is){
	Scanner *scanner = malloc(sizeof(Scanner));
	ZeroMemory(scanner, sizeof(Scanner));
	scanner->_is = is;

	// load function
	scanner->next = next;
	scanner->nextLine = nextLine;
	scanner->nextInt = nextInt;
	scanner->nextFloat = nextFloat;
	scanner->hasNext = hasNext;

	return scanner;
}

void freeScanner(Scanner *scanner){
	freeInputStream(scanner->_is);
	free(scanner);
}

static int hasNext(Scanner *self){
	InputStream *is = self->_is;
	int unread = self->_bufferSize - self->_bufferPtr;		// 可读的大小
	if (unread <= 0){
		self->_bufferSize = is->read(is, self->_buffer, SCANNER_BUFFER_SIZE);
		if (self->_bufferSize > 0){
			return 1;
		}
		else{
			return 0;
		}
	}
	return 1;
}

static String *next(Scanner *self){
	String *s = newString("");
	char bufChar = 0;
	while (1){
		int result = readFromBuffer(self, &bufChar, 1);
		if (result == -1){
			break;					// Exception
		}
		else if (result == 0){		// 读取到结尾
			break;
		}
		else{
			if ((bufChar == ' ' || bufChar == '\n' || bufChar == '\r') && s->size(s) == 0){		// 跳过前导空格(也就是现在s还没有数据，但是接收到空格的情况)
				continue;
			}
			else if ((bufChar == ' ' || bufChar == '\n') &&s->size(s) != 0){
				if (s->lastChar(s) == '\r'){
					s->popChar(s);
				}
				break;
			}
			else{
				s->appendChar(s, bufChar);
			}
		}
	}
	return s;
}

static String *nextLine(Scanner *self){
	String *s = newString("");
	char bufChar = 0;
	while (1){
		int result = readFromBuffer(self, &bufChar, 1);
		if (result == -1){
			break;					// Exception
		}
		else if (result == 0){		// 读取到结尾
			break;
		}
		else{
			if (bufChar == '\n'){
				if (s->lastChar(s)=='\r'){
					s->popChar(s);
				}
				break;
			}
			else{
				s->appendChar(s, bufChar);
			}
		}
	}
	return s;
}

static int nextInt(Scanner *self){
	String *s = self->next(self);
	int r = s->toInt(s);
	freeString(s);
	return r;
}

static double nextFloat(Scanner *self){
	String *s = self->next(self);
	double r = s->toFloat(s);
	freeString(s);
	return r;
}

static int readFromBuffer(Scanner *scanner, unsigned char *rcv, int maxLength){
	InputStream *is = scanner->_is;
	int unread = scanner->_bufferSize - scanner->_bufferPtr;		// 可读的大小
	if (unread <= 0){
		scanner->_bufferSize = is->read(is, scanner->_buffer, SCANNER_BUFFER_SIZE);
		if (scanner->_bufferSize == -1){
			return -1;
		}
		else if (scanner->_bufferSize == 0){
			return 0;
		}
		scanner->_bufferPtr = 0;
		unread = scanner->_bufferSize;
	}
	int willread = unread < maxLength ? unread : maxLength;			// 会从缓冲区读取出的数量
	memcpy(rcv, scanner->_buffer + scanner->_bufferPtr, willread);
	scanner->_bufferPtr += willread;
	return willread;
}