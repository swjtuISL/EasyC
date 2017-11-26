#include "RIO.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <fileapi.h>

static int readn(RIO *self, void *userbuf, unsigned int n);
static int readline(RIO *self, void *userbuf, unsigned int n);
static int writen(RIO *self, void *userbuf, unsigned int n);

void initRIO(RIO *rio, HANDLE hi, HANDLE ho){
	ZeroMemory(rio, sizeof(RIO));

	rio->_hi = hi;
	rio->_ho = ho;
	rio->_ptr = rio->_memory;
	
	// load function
	rio->readline = readline;
	rio->readn = readn;
	rio->writen = writen;
}

/*
基本的缓冲读操作。
读取指定长度大小的数据到buf中。
先尝试将缓冲区塞满，然后将缓冲区的数据拷贝到buf中，最后返回读出数据的个数。
*/
static int basicRead(RIO *rp, char *buf, unsigned int n){
	if (rp->_unreadSize <= 0){		// 缓冲区数据为空，需要读取数据
		if (ReadFile(rp->_hi, rp->_memory, sizeof(rp->_memory), &rp->_unreadSize, NULL) == FALSE){
			// # ERROR #
			return -1;
		}
		if (rp->_unreadSize == 0){		// 数据读取完毕
			return 0;
		}
		else{
			rp->_ptr = rp->_memory;	// 读取了新的缓存，重置数据头
		}
	}

	// 缓冲区中有数据
	int cnt = rp->_unreadSize < n ? rp->_unreadSize : n;	// 如果缓冲区的数据小于待取出的数据个数，则取出的数据为缓冲区的大小
	memcpy(buf, rp->_ptr, cnt);								// 取出数据
	rp->_ptr += cnt;										// 移动
	rp->_unreadSize -= cnt;
	return cnt;
}

static int readn(RIO *self, void *userbuf, unsigned int n){

}
static int readline(RIO *self, void *userbuf, unsigned int maxlen){
	int n = 0;
	char *bufp = userbuf;
	for (n = 1; n < maxlen; n++){
		int rc = 0;
		char c = 0;
		if ((rc = basicRead(self, &c, 1)) == 1){	// 从缓冲区里面读取数据，若缓冲区中没有数据会先尝试将缓冲区的数据填满
			*bufp++ = c;
			if (c == '\n'){
				break;
			}
		}
		else if (rc == 0){
			if (n == 1){
				return 0;
			}
			else{
				break;
			}
		}
		else{
			return -1;
		}
	}
	return n;
}
static int writen(RIO *self, void *userbuf, unsigned int n){

}