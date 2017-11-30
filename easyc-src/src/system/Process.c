
#include "Process.h"
#include "RIO.h"

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

static Process *set(Process * const self, char *key, char *value);
static char *get(Process * const self, char *key);
static int start(Process * const self, char *path);							// ���̿�ʼ������������δ��ɡ�
static int startBlock(Process * const self, char *path);					// ���̿�ʼֱ����������δ��ɡ�
static int readline(Process * const self, void *userbuf, unsigned int n);	// ��ȡһ�����ݣ������������Ϊn������һ��ֱ������
static int readn(Process * const self, void *userbuf, unsigned int n);		// ��ȡָ���ֽڴ�С�����ݣ���������������δ��ɡ�

Process * newProcess(){
	Process * process = (Process *)malloc(sizeof(Process));
	ZeroMemory(process, sizeof(process));
	process->_isRun = 0;

	// load function
	process->get = get;
	process->set = set;
	process->start = start;
	process->readline = readline;
	process->readn = readn;

	return process;
}

void freeProcess(Process * const p){

}

static int start(Process * const self, char *path){
	if (self->_isRun){
		return 0;
	}
	HANDLE hi, ho;
	SECURITY_ATTRIBUTES pipeSA = { sizeof(SECURITY_ATTRIBUTES), NULL, TRUE };
	CreatePipe(&hi, &ho, &pipeSA, 0);
	self->_rio = (RIO *)malloc(sizeof(RIO));
	initRIO(self->_rio, hi, ho);
	

	PROCESS_INFORMATION pi;
	STARTUPINFO si;
	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&pi, sizeof(pi));
	si.cb = sizeof(si);
	si.hStdError = GetStdHandle(STD_ERROR_HANDLE);
	si.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
	si.hStdOutput = self->_rio->_ho;
	si.dwFlags = STARTF_USESTDHANDLES;
	CreateProcess(NULL, path,
		NULL, NULL, TRUE,
		0, NULL, NULL,
		&si, &pi);
	CloseHandle(self->_rio->_ho);
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

static Process *set(Process * const self, char *key, char *value){

}

static char *get(Process * const self, char *key){

}

static int readline(Process * const self, void *userbuf, unsigned int n){
	return self->_rio->readline(self->_rio, userbuf, n);
}

static int readn(Process * const self, void *userbuf, unsigned int n){

}