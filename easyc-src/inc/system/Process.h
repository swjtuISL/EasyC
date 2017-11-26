#ifndef __PROCESS_H
#define __PROCESS_H


// 结构声明
struct Process;
struct RIO;
typedef struct Process Process;
typedef struct RIO RIO;
typedef HashMap;
typedef void * HANDLE;

Process * newProcess();
void freeProcess(Process * const p);

struct Process{
	HashMap * _hashMap;
	int _isRun;
	RIO *_rio;
	HANDLE *_pHandle;		// 进程句柄

	Process *(*set)(Process * const self, char *key, char *value);
	char *(*get)(Process * const self, char *key);
	int(*start)(Process * const self, char *path);							// 进程开始，不阻塞。【未完成】
	int(*startBlock)(Process * const self, char *path);						// 进程开始直接阻塞。【未完成】
	int(*readline)(Process * const self, void *userbuf, unsigned int n);	// 读取一行数据，限制行数最大为n，不足一行直接阻塞
	int(*readn)(Process * const self, void *userbuf, unsigned int n);		// 读取指定字节大小的数据，不足则阻塞。【未完成】
};

#endif