#ifndef __STRING_H
#define __STRING_H

struct String;
struct Vector;
typedef struct String String;
typedef struct Vector Vector;

String *newString(char * chars);
void freeString(String *s);
char *toChars(String *self);
char *toCharsN(String *self);
int toInt(String *self);									// 【未实现】
double toFloat(String *self);								// 【未实现】

/*
* @Desc   : 动态字符串, 可以动态的扩展字符串, 也提供转换为char*的接口.
* @Author : Shuaiji Lu
* @Date   : 2017/11/27
*/
struct String{
	char *_mem;				// 字符保存区域, 包括结尾符
	int _capacity;
	float _loadFactor;
	int _size;				// 不包含结尾符的字符个数
	Vector *_relative;

	// public (interface)
	String *(*append)(String *self, char *chars);
	String *(*appendString)(String *self, String *s);
	String *(*appendPtr)(String *self, void *ptr);
	String *(*appendInt)(String *self, int intnum);
	String *(*appendFloat)(String *self, float floatnum);
	String *(*appendChar)(String *self, char chr);
	String *(*substring)(String *self, int begin, int length);		// 【未实现】
	char(*lastChar)(String *self);									// 字符串最后一个字符(结尾符的前一个)
	char(*popChar)(String *self);									// 将最后一个字符弹出
	int(*size)(String *self);
	int(*toInt)(String *self);										
	double(*toFloat)(String *self);
	char *(*toChars)(String *self);

	// private
	void(*_resize)(String *self, int target);
};

#endif