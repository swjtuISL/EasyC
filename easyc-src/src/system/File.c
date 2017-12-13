#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "File.h"
#include "String.h"

static int del(File *self);
static Vector *list(File *self);
static HANDLE openToRead(File *self);

File * newFile(char *path){
	File *file = malloc(sizeof(File));
	ZeroMemory(file, sizeof(File));
	file->_path = newString(path);

	// load function
	file->del = del;
	file->list = list;
	file->openToRead = openToRead;

	return file;
}

void freeFile(File *file){
	freeString(file->_path);
	free(file);
}

static int del(File *self){

}
static Vector *list(File *self){

}
static HANDLE openToRead(File *self){
	HANDLE hd = CreateFile(toChars(self->_path),
		GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hd == INVALID_HANDLE_VALUE){
		// Exception
		printf("error create file");
	}
	return hd;
}