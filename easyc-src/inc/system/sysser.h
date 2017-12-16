#ifndef __SYS_SER_H
#define __SYS_SER_H

struct Vector;
struct InputStream;
struct OutputStream;
typedef struct Vector Vector;
typedef struct InputStream InputStream;
typedef struct OutputStream OutputStream;

#define stdis getStdInputStream()
#define stdos getStdOutputStream()
#define stdes getStdOutputStream()

InputStream *getStdInputStream();
OutputStream *getStdOutputStream();
OutputStream *getStdErrorStream();
String *getExeDir();
void * funWrapperInts(void *(*fun)(Vector *vector), int length, ...);
void * funWrapperPtrs(void *(*fun)(Vector *vector), int length, ...);
void reportError(char* userMessage, unsigned long exitCode);

#endif