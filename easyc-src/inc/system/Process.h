#ifndef __PROCESS_H
#define __PROCESS_H


// 结构声明
struct Process;
struct Scanner;
struct HashMap;
struct String;
struct Vector;
typedef struct Process Process;
typedef struct HashMap HashMap;
typedef struct Scanner Scanner;
typedef struct String String;
typedef struct Vector Vector;
typedef void * HANDLE;

Process * newProcess(char *exepath);
void freeProcess(Process * const p);

struct Process{
	String *_workspace;
	String *_exepath;
	Vector *_cmdArgs;		// 命令行参数
	Scanner *_pin;
	HashMap * _env;			// 环境变量参数
	int _isRun;
	HANDLE *_pHandle;		// 进程句柄
	int _exitCode;

	// public (interface)
	Process *(*uniteWorkspace)(Process *self);
	Process *(*setWorkspace)(Process *self, char *path);
	Process *(*add)(Process *self, char *arg);
	Process *(*set)(Process * const self, char *key, char *value);
	Process *(*eset)(Process * const self, char *key, char *value);			// 通过环境变量传递参数，侵入性小
	char *(*get)(Process * const self, char *key);
	char *(*eget)(Process * const self, char *key);
	int(*start)(Process * const self);										// 进程开始，不阻塞。【未完成】
	int(*startBlock)(Process * const self);									// 进程开始直接阻塞。【未完成】
	void (*waitFinish)(Process * const self);
	int (*getExitCode)(Process *self);

	int (*hasNext)(Process *self);
	String *(*next)(Process *self);
	String *(*nextLine)(Process *self);
	int(*nextInt)(Process *self);
	double(*nextFloat)(Process *self);

	// private
	void (*_installEnv)(Process *self);
	void (*_uninstallEnv)(Process *self);
};

#endif