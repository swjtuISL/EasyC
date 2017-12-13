#ifndef __INPUT_STREAM_H
#define __INPUT_STREAM_H

struct InputStream;
struct File;
typedef struct InputStream InputStream;
typedef struct File File;
typedef void * HANDLE;

InputStream * newInputStream(HANDLE hi);
InputStream * newFileInputStream(File *file);
void freeInputStream(InputStream *is);

struct InputStream{
	File *_file;
	HANDLE _hi;
	int _isFinish;

	int(*read)(InputStream *self, unsigned char *rcv, int maxLength);
	int(*readByte)(InputStream *self);
};

#endif
