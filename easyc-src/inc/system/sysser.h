#ifndef __SYS_SER_H
#define __SYS_SER_H

struct Vector;
typedef struct Vector Vector;

void * funWrapperInts(void *(*fun)(Vector *vector), int length, ...);
void * funWrapperPtrs(void *(*fun)(Vector *vector), int length, ...);
void reportError(char* userMessage, unsigned long exitCode);

#endif