#include "basicAlgo.h"
#include "Vector.h"
/*
* @Desc   : 求vector的最小值及其索引
* @Param  : vector, 原始的Vector
* @Param  : *idx, 返回最小值的索引
* @Return : 返回vector中的最小值
* @Authro : 卢帅吉
* @Date   : 2017.11.26
*/
int minInVector(Vector *vector, int *idx){
	int val = vector->get(vector, 0);
	*idx = 0;
	for (int i = 1; i < vector->size(vector); i++){
		int v = vector->get(vector, i);
		if (v < val){
			val = v;
			*idx = i;
		}
	}
	return val;
}