#ifndef __OUTPUT_STREAM_H
#define __OUTPUT_STREAM_H

struct OutputStream;
typedef struct OutputStream OutputStream;
typedef void * HANDLE;

OutputStream *newOutputStream();
void freeOutputStream(OutputStream *os);

struct OutputStream{
	HANDLE _ho;
};

#endif