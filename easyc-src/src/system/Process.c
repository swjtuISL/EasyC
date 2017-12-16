#define _CRT_SECURE_NO_WARNINGS			// 忽略库函数安全问题
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <String.h>
#include "sysser.h"
#include "Vector.h"
#include "Scanner.h"
#include "Process.h"
#include "InputStream.h"
#include "HashMap.h"
#include "String.h"

static Process *uniteWorkspace(Process *self);
static Process *setWorkspace(Process *self, char *path);
static Process *add(Process *self, char *arg);
static Process * set(Process * const self, char *key, char *value);
static char * get(Process * const self, char *key);
static Process * eset(Process * const self, char *key, char *value);
static char * eget(Process * const self, char *key);
static int start(Process * const self);										// 进程开始，不阻塞。【未完成】
static int startBlock(Process * const self);								// 进程开始直接阻塞。【未完成】
static void waitFinish(Process * const self);
static String * next(Process *self);
static String * nextLine(Process *self);
static int nextInt(Process *self);
static double nextFloat(Process *self);
static int getExitCode(Process *self);
static void _installEnv(Process *self);
static void _uninstallEnv(Process *self);
static int hasNext(Process *self);

Process * newProcess(char *exepath){
	Process * process = (Process *)malloc(sizeof(Process));
	ZeroMemory(process, sizeof(Process));
	process->_isRun = 0;				// 未开始
	process->_env = newHashMap(NULL);	// 初始化进程将使用的环境变量
	process->_exepath = newString(exepath);

	// load function
	process->uniteWorkspace = uniteWorkspace;
	process->setWorkspace = setWorkspace;
	process->add = add;
	process->get = get;
	process->set = set;
	process->eget = eget;
	process->eset = eset;
	process->start = start;
	process->startBlock = startBlock;
	process->hasNext = hasNext;
	process->next = next;
	process->nextLine = nextLine;
	process->nextFloat = nextFloat;
	process->nextInt = nextInt;
	process->waitFinish = waitFinish;
	process->_installEnv = _installEnv;
	process->_uninstallEnv = _uninstallEnv;

	return process;
}

void freeProcess(Process * const p){
	if (p->_cmdArgs){
		freeVector(p->_cmdArgs);
	}
	if (p->_exepath){
		freeString(p->_exepath);
	}
	if (p->_workspace){
		freeString(p->_workspace);
	}
	if (p->_env){
		freeHashMap(p->_env);
	}
	if (p->_isRun && p->_pin){
		freeScanner(p->_pin);
		CloseHandle(p->_pHandle);
	}
	if (p){
		free(p);
	}
}

static Process *uniteWorkspace(Process *self){
	if (self->_isRun){
		// Exception
	}
	String *exepath = getExeDir();
	if (self->_workspace){
		freeString(self->_workspace);
	}
	char *s = toChars(self->_exepath);
	char *last = strrchr(s, '\\');
	s[last - s] = '\0';
	self->_workspace = exepath->append(exepath, "\\")->append(exepath, s);
	return self;
}

static Process *setWorkspace(Process *self, char *path){
	if (self->_isRun){
		// Exception
	}
	if (self->_workspace){
		freeString(self->_workspace);
	}
	else{
		self->_workspace = newString(path);
	}
	return self;
}

static int start(Process * const self){
	if (self->_isRun){
		return 0;
	}
	HANDLE hi, ho;
	SECURITY_ATTRIBUTES pipeSA = { sizeof(SECURITY_ATTRIBUTES), NULL, TRUE };
	CreatePipe(&hi, &ho, &pipeSA, 0);
	self->_pin = newScanner(newInputStream(hi));

	PROCESS_INFORMATION pi;
	STARTUPINFO si;
	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&pi, sizeof(pi));
	si.cb = sizeof(si);
	si.hStdError = GetStdHandle(STD_ERROR_HANDLE);
	si.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
	si.hStdOutput = ho;
	si.dwFlags = STARTF_USESTDHANDLES;

	self->_installEnv(self);
	String *path = newString("");
	path->appendString(path, self->_exepath);
	for (int i = 0; self->_cmdArgs && (i < self->_cmdArgs->size(self->_cmdArgs)); i++){
		char *cmdarg = self->_cmdArgs->get(self->_cmdArgs, i);
		path->append(path, " ")->append(path, cmdarg);
	}
	CreateProcess(NULL, toChars(path),
		NULL, NULL, TRUE,
		0, NULL, self->_workspace == NULL ? NULL : toChars(self->_workspace),
		&si, &pi);
	CloseHandle(ho);
	self->_isRun = 1;
	self->_uninstallEnv(self);
	freeString(path);
	return 1;
}

static int startBlock(Process * const self){
	if (start(self)){
		WaitForSingleObject(self->_pHandle, INFINITE);
		return 1;
	}
	else{
		return 0;
	}
}

void waitFinish(Process * const self){
	if (self->_isRun){
		WaitForSingleObject(self->_pHandle, INFINITE);
		GetExitCodeProcess(self->_pHandle, &self->_exitCode);
	}
}

static Process *add(Process *self, char *arg){
	if (self->_cmdArgs == NULL){
		self->_cmdArgs = newVector();
	}
	self->_cmdArgs->addChars(self->_cmdArgs, arg);
	return self;
}

static Process *set(Process * const self, char *key, char *value){
	return self;
}

static char *get(Process * const self, char *key){

}

static Process * eset(Process * const self, char *key, char *value){
	self->_env->putChars(self->_env, key, value);
	return self;
}

static char * eget(Process * const self, char *key){
	return self->_env->get(self->_env, key);
}

static int hasNext(Process *self){
	if (!self->_isRun){
		// Exception
	}
	return self->_pin->hasNext(self->_pin);
}

static String * next(Process *self){
	if (!self->_isRun){
		// Exception
	}
	return self->_pin->next(self->_pin);
}

static String * nextLine(Process *self){
	if (!self->_isRun){
		// Exception
	}
	return self->_pin->nextLine(self->_pin);
}

static int nextInt(Process *self){
	return self->_pin->nextInt(self->_pin);
}

static double nextFloat(Process *self){
	if (!self->_isRun){
		// Exception
	}
	return self->_pin->nextFloat(self->_pin);
}

static int getExitCode(Process *self){
	
}

static void _installEnv(Process *self){
	Vector *keys = self->_env->keys(self->_env);
	for (int i = 0; i < keys->size(keys); i++){
		char *key = keys->get(keys, i);
		char *val = self->_env->get(self->_env, key);
		String *s = newString(key);
		s->append(s, "=")->append(s, val);
		_putenv(toChars(s));
		freeString(s);
	}
}

static void _uninstallEnv(Process *self){
	Vector *keys = self->_env->keys(self->_env);
	for (int i = 0; i < keys->size(keys); i++){
		char *key = keys->get(keys, i);
		String *s = newString(key);
		s->append(s, "=");
		_putenv(toChars(s));
		freeString(s);
	}
}