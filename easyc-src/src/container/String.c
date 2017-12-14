#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <String.h>
#include <math.h>
#include <memory.h>
#include "String.h"
#include "Vector.h"

static const INITIAL_CAPACITY = 16;
static const float DEFAULT_LOAD_FACTOR = 0.75f;

static String * append(String *self, char *chars);
static String * appendString(String *self, String *s);
static String * appendPtr(String *self, void *ptr);
static String * appendInt(String *self, int intnum);
static String * appendFloat(String *self, float floatnum);
static String * appendChar(String *self, char chr);
static String * substring(String *self, int begin, int length);
static char lastChar(String *self);
static char popChar(String *self);
static int size(String *self);
static void _resize(String *self, int target);
int toInt(String *self);
double toFloat(String *self);
char *toChars(String *self);

/*
* @Desc   : String������������һ���Ѱ��������ַ���Stringʵ����
* @Param  : *chars.��ʼ�ַ���.
* @Return : �����µĹ����õ�String
* @Authro : Shuaiji Lu
* @Date   : 2017/11/27
*/
String *newString(char * chars){
	if (chars == NULL){
		chars = "";
	}
	String *s = (String *)malloc(sizeof(String));
	ZeroMemory(s, sizeof(String));

	int charsLength = lstrlen(chars)+1;					// ���Ͻ�β���ĳ���
	int nextLength = 1 << ((int)log2(charsLength)+1);
	s->_loadFactor = DEFAULT_LOAD_FACTOR;
	s->_capacity = nextLength > INITIAL_CAPACITY ? nextLength : INITIAL_CAPACITY;
	s->_mem = (char *)malloc(sizeof(char)*s->_capacity);
	ZeroMemory(s->_mem, s->_capacity);
	for (int i = 0; i < charsLength; i++){
		s->_mem[i] = chars[i];
	}
	s->_relative = newVector();
	s->_size = charsLength-1;							// ������β���ĳ���

	// load function
	s->append = append;
	s->appendString = appendString;
	s->appendInt = appendInt;
	s->appendFloat = appendFloat;
	s->appendPtr = appendPtr;
	s->appendChar = appendChar;
	s->substring = substring;
	s->lastChar = lastChar;
	s->popChar = popChar;
	s->size = size;
	s->toInt = toInt;
	s->toFloat = toFloat;
	s->toChars = toChars;
	s->_resize = _resize;
}

/*
* @Desc   : �ͷ�String�������ڴ�.
* @Param  : *s, Ҫ�ͷŵ�String
* @Return : ��
* @Authro : Shuaiji Lu
* @Date   : 2017/11/27
*/
void freeString(String *s){
	free(s->_mem);
	freeVector(s->_relative);
	free(s);
}

/*
* @Desc   : ��̬ƴ���ַ���.
* @Param  : *self, Ҫ������String
* @Param  : *chars, ��self�ַ�������ƴ��char.
* @Return : �����ַ���ʵ��self����.
* @Authro : Shuaiji Lu
* @Date   : 2017/11/27
*/
static String * append(String *self, char *chars){
	int appendLength = lstrlen(chars)+1;
	self->_resize(self, self->_size + appendLength);
	memcpy(self->_mem + self->_size, chars, appendLength);
	self->_size += (appendLength - 1);						// ������β���ĳ���
	return self;
}

/*
* @Desc   : ��̬ƴ�ӵ�ֵַ.
* @Param  : *self, Ҫ������String
* @Param  : *ptr, ��self�ַ�������ƴ�ӵ�ֵַ.
* @Return : �����ַ���ʵ��self����.
* @Authro : Shuaiji Lu
* @Date   : 2017/11/27
*/
static String * appendPtr(String *self, void *ptr){
	char buf[64];
	sprintf_s(buf, 64, "%d", ptr);
	self->append(self, buf);
	return self;
}

/*
* @Desc   : ��̬ƴ������.
* @Param  : *self, Ҫ������String
* @Param  : intnum, ��self�ַ�������ƴ������.
* @Return : �����ַ���ʵ��self����.
* @Authro : Shuaiji Lu
* @Date   : 2017/11/27
*/
static String * appendInt(String *self, int intnum){
	char buf[64];
	sprintf_s(buf, 64, "%d", intnum);
	self->append(self, buf);
	return self;
}
/*
* @Desc   : ��̬ƴ�Ӹ�����.
* @Param  : *self, Ҫ������String
* @Param  : floatnum, ��self�ַ�������ƴ��float.
* @Return : �����ַ���ʵ��self����.
* @Authro : Shuaiji Lu
* @Date   : 2017/11/27
*/
static String * appendFloat(String *self, float floatnum){
	char buf[64];
	sprintf_s(buf, 64, "%f", floatnum);
	self->append(self, buf);
	return self;
}

/*
* @Desc   : ��̬ƴ���ַ���.
* @Param  : *self, Ҫ������String
* @Param  : *s, ��self�ַ�������ƴ��String.
* @Return : �����ַ���ʵ��self����.
* @Authro : Shuaiji Lu
* @Date   : 2017/11/27
*/
static String * appendString(String *self, String *s){
	int appendLength = s->_size + 1;
	self->_resize(self, self->_size + appendLength);
	memcpy(self->_mem + self->_size, s->_mem, appendLength);
	self->_size += (appendLength - 1);						// ������β���ĳ���
	return self;
}

static String * appendChar(String *self, char chr){
	self->_resize(self, self->_size + 2);					// +2��Ԥ���˽�β��
	self->_mem[self->_size] = chr;
	self->_mem[self->_size+1] = '\0';
	self->_size += 1;
	return self;
}

static String *substring(String *self, int begin, int length){

}

static char lastChar(String *self){
	if (self->_size >= 1){
		return self->_mem[self->_size-1];
	}
	else{
		// Exception
		return -1;
	}
}

static char popChar(String *self){
	if (self->_size >= 1){
		char old = self->_mem[self->_size - 1];
		self->_mem[self->_size - 1] = self->_mem[self->_size];
		self->_size -= 1;
		return old;
	}
	else{
		// Exception
		return -1;
	}
}

/*
* @Desc   : ����ַ�������.
* @Param  : *self, Ҫ������String
* @Return : �����ַ�������(�ַ������ַ�����).
* @Authro : Shuaiji Lu
* @Date   : 2017/11/27
*/
static int size(String *self){
	return self->_size;
}

/*
* @Desc   : ȷ������target��С�Ŀռ��Ա�����ַ�����.
* @Param  : *self, Ҫ������String
* @Param  : target, ��ҪString��ǰ����������Ϊtarget.
* @Return : ��
* @Authro : Shuaiji Lu
* @Date   : 2017/11/27
*/
static void _resize(String *self, int target){
	if (target < self->_capacity * self->_loadFactor){
		return;
	}
	int newcap = 1<<((int)log2(target)+1);
	char * newmem = (char *)malloc(sizeof(char) * newcap);
	for (int i = 0; i < newcap; i++){
		if (i < self->_capacity){
			newmem[i] = self->_mem[i];
		}
		else{
			newmem[i] = NULL;
		}
	}
	free(self->_mem);
	self->_mem = newmem;
	self->_capacity = newcap;
}

int toInt(String *self){
	int r = atoi(self->_mem);
	return r;
}

double toFloat(String *self){
	double r = atof(self->_mem);
	return r;
}

/*
* @Desc   : ���ַ���ת����char*, ���ص�����Ϊ��ض���, String�ͷŵ�ʱ��ᱻ�ͷ�.
* @Param  : *self, Ҫ������String
* @Return : �����ַ�����chars.
* @Authro : Shuaiji Lu
* @Date   : 2017/11/27
*/
char *toChars(String *self){
	char *chars = (char *)malloc(sizeof(char)*(self->_size + 1));
	memcpy(chars, self->_mem, self->_size + 1);
	self->_relative->addObject(self->_relative, chars, free, NULL, NULL);
	return chars;
}

char *toCharsN(String *self){
	char *chars = (char *)malloc(sizeof(char)*(self->_size + 1));
	memcpy(chars, self->_mem, self->_size + 1);
	return chars;
}