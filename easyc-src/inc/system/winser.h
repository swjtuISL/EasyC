#ifndef __WIN_SER_H
#define __WIN_SER_H

#include <Windows.h>

#ifdef UNICODE
#define str2tstr str2wstr
#else
#define str2tstr str2str
#endif

VOID str2wstr(char* str, LPCTSTR tstr);
VOID str2str(char *str, LPTSTR tstr);

#endif