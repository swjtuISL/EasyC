#ifndef __FILE_H
#define __FILE_H

struct File;
struct Vector;
struct String;
typedef struct File File;
typedef struct Vector Vector;
typedef struct String String;
typedef void * HANDLE;

File * newFile(char *path);
void freeFile(File *file);

struct File{
	String *_path;

	int (*del)(File *self);
	Vector *(*list)(File *self);
	HANDLE (*openToRead)(File *self);
};

#endif