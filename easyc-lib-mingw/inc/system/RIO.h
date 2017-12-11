#ifndef __RIO_H
#define __RIO_H

struct RIO;
typedef struct RIO RIO;
typedef void * HANDLE;

void initRIO(RIO *rio, HANDLE hi, HANDLE ho);

#define RIO_BUFFERSIZE 8192

struct RIO{
	HANDLE _hi;
	HANDLE _ho;
	int _unreadSize;		// 缓冲区中的未读字节数
	char *_ptr;
	char _memory[RIO_BUFFERSIZE];

	int(*readn)(RIO *self, void *userbuf, unsigned int n);
	int(*readline)(RIO *self, void *userbuf, unsigned int n);
	int(*writen)(RIO *self, void *userbuf, unsigned int n);
};

#endif