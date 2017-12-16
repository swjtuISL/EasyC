#ifndef __PROCESS_H
#define __PROCESS_H


// �ṹ����
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
	Vector *_cmdArgs;		// �����в���
	Scanner *_pin;
	HashMap * _env;			// ������������
	int _isRun;
	HANDLE *_pHandle;		// ���̾��
	int _exitCode;

	// public (interface)
	Process *(*uniteWorkspace)(Process *self);
	Process *(*setWorkspace)(Process *self, char *path);
	Process *(*add)(Process *self, char *arg);
	Process *(*set)(Process * const self, char *key, char *value);
	Process *(*eset)(Process * const self, char *key, char *value);			// ͨ�������������ݲ�����������С
	char *(*get)(Process * const self, char *key);
	char *(*eget)(Process * const self, char *key);
	int(*start)(Process * const self);										// ���̿�ʼ������������δ��ɡ�
	int(*startBlock)(Process * const self);									// ���̿�ʼֱ����������δ��ɡ�
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