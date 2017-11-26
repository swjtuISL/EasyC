#ifndef __SYS_SER_H
#define __SYS_SER_H

struct Vector;
typedef struct Vector Vector;

void * funWrapperInts(void *(*fun)(Vector *vector), int args, ...);

#endif