#define _CRT_SECURE_NO_WARNINGS			// 忽略库函数安全问题
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#include "Vector.h"
#include "Scanner.h"
#include "Process.h"
#include "InputStream.h"
#include "HashMap.h"
#include "String.h"

static Process * set(Process * const self, char *key, char *value);
static char * get(Process * const self, char *key);
static Process * eset(Process * const self, char *key, char *value);
static char * eget(Process * const self, char *key);
static int start(Process * const self, char *path);							// 进程开始，不阻塞。【未完成】
static int startBlock(Process * const self, char *path);					// 进程开始直接阻塞。【未完成】
static void waitFinish(Process * const self);
static String * next(Process *self);
static String * nextLine(Process *self);
static int nextInt(Process *self);
static double nextFloat(Process *self);
static int getExitCode(Process *self);
static void _installEnv(Process *self);
static void _uninstallEnv(Process *self);

Process * newProcess(){
	Process * process = (Process *)malloc(sizeof(Process));
	ZeroMemory(process, sizeof(Process));
	process->_isRun = 0;				// 未开始
	process->_env = newHashMap(NULL);	// 初始化进程将使用的环境变量

	// load function
	process->get = get;
	process->set = set;
	process->eget = eget;
	process->eset = eset;
	process->start = start;
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

static int start(Process * const self, char *path){
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
	CreateProcess(NULL, path,
		NULL, NULL, TRUE,
		0, NULL, NULL,
		&si, &pi);
	CloseHandle(ho);
	self->_isRun = 1;
	self->_uninstallEnv(self);
	return 1;
}

static int startBlock(Process * const self, char *path){
	if (start(self, path)){
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