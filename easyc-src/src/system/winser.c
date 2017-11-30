#include <stdio.h>
#include "winser.h"

VOID str2wstr(char *str, LPTSTR tstr){
	int len = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, 0);		// 计算转换后需要的字节数
	LPCWSTR wstr = (LPCWSTR)malloc(sizeof(wchar_t)*len);
	MultiByteToWideChar(CP_ACP, 0, str, -1, wstr, len);
	lstrcpyW(tstr, wstr);
}

VOID str2str(char *str, LPSTR tstr){
	int len = lstrlenA(str);
	lstrcpyA(tstr, str);
}
