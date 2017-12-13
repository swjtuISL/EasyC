#ifndef __SCANNER_H
#define __SCANNER_H

struct Scanner;
struct String;
struct InputStream;
typedef struct Scanner Scanner;
typedef struct String String;
typedef struct InputStream InputStream;

#define SCANNER_BUFFER_SIZE 8192

Scanner * newScanner(InputStream *is);
void freeScanner(Scanner *scanner);

struct Scanner{
	InputStream *_is;
	char _buffer[SCANNER_BUFFER_SIZE];
	int _bufferPtr;
	int _bufferSize;

	// public (interface)
	String *(*next)(Scanner *self);
	String *(*nextLine)(Scanner *self);
	int (*nextInt)(Scanner *self);
	double (*nextFloat)(Scanner *self);

};

#endif