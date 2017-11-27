#ifndef __BIG_NUMBER_H
#define __BIG_NUMBER_H

struct BigNumber;
struct String;
struct Vector;
typedef struct BigNumber BigNumber;
typedef struct Vector Vector;
typedef struct String String;

struct BigNumber{
	
	void(*add)(BigNumber *self, int number);
	void(*sub)(BigNumber *self, int number);
	void(*mul)(BigNumber *self, int number);
	void(*div)(BigNumber *self, int number);

	void(*addBig)(BigNumber *self, BigNumber *number);
	void(*subBig)(BigNumber *self, BigNumber *number);
	void(*mulBig)(BigNumber *self, BigNumber *number);
	void(*divBig)(BigNumber *self, BigNumber *number);

	String *(*toString)(BigNumber *self);
};

#endif