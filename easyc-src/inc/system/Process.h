#ifndef __PROCESS_H
#define __PROCESS_H


// 结构声明
struct Process;
struct Scanner;
struct HashMap;
typedef struct Process Process;
typedef struct HashMap HashMap;
typedef struct Scanner Scanner;
typedef void * HANDLE;

Process * newProcess();
void freeProcess(Process * const p);

struct Process{
	Scanner *_pin;
	HashMap * _env;
	int _isRun;
	HANDLE *_pHandle;		// 进程句柄
	int _exitCode;

	// public (interface)
	Process *(*set)(Process * const self, char *key, char *value);
	Process *(*eset)(Process * const self, char *key, char *value);			// 通过环境变量传递参数，侵入性小
	char *(*get)(Process * const self, char *key);
	char *(*eget)(Process * const self, char *key);
	int(*start)(Process * const self, char *path);							// 进程开始，不阻塞。【未完成】
	int(*startBlock)(Process * const self, char *path);						// 进程开始直接阻塞。【未完成】
	void (*waitFinish)(Process * const self);
	int (*getExitCode)(Process *self);

	String *(*next)(Scanner *self);
	String *(*nextLine)(Scanner *self);
	int(*nextInt)(Scanner *self);
	double(*nextFloat)(Scanner *self);

	// private
	void (*_installEnv)(Process *self);
	void (*_uninstallEnv)(Process *self);
};

#endif