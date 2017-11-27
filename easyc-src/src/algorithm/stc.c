#include "stc.h"
#include "Vector.h"
#include "Matrix.h"
#include "basicAlgo.h"

#include <math.h>
#include <stdlib.h>
#include <Windows.h>
#define STC_DEBUG

static const INF = 100000000;

/*
* @Desc   : STCCode的构造器.
* @Param  : n
* @Param  : l
* @Param  : *h
* @Param  : *shift
* @Return : STCCode实例
* @Authro : Shuaiji Lu
* @Date   : 2017/11/26
*/
STCCode *newSTCCode(int n, int l, Vector *const h, Vector *shift){
	STCCode *code = (STCCode *)malloc(sizeof(STCCode));
	ZeroMemory(code, sizeof(STCCode));
	code->n = n;
	code->l = l;
	code->h = h;
	code->shift = shift;
	return code;
}

/*
* @Desc   : 释放STCCode中的数据.不释放其中的所引用的内存.
* @Param  : *code, 待释放的容器.
* @Return : 无
* @Authro : Shuaiji Lu
* @Date   : 2017/11/26
*/
void freeSTCCode(STCCode * const code){
	free(code);
}

/*
* @Desc   : 释放STCCode中的数据, 包括其中的Vector容器.
* @Param  : *code, 待释放的容器.
* @Return : 无
* @Authro : Shuaiji Lu
* @Date   : 2017/11/26
*/
void removeSTCCode(STCCode * const code){
	freeVector(code->shift);
	freeVector(code->h);
	free(code);
}

/*
* @Desc   : 采用STC将原始二进制数据进行编码，使其包含二进制秘密数据.
* @Param  : *code, STC所需要的奇偶校验矩阵的相关信息.
* @Param  : *x, 原始二进制序列.
* @Param  : *m, 秘密消息二进制序列.
* @Param  : *mc, 编码后的最小损耗.
* @Param  : *w, 原始数据中对应位置修改造成的损失权重.
* @Return : 返回含密的二进制序列.
* @Authro : Shuaiji Lu
* @Date   : 2017/11/26
*/
Vector *dualViterbi(const STCCode * const code, const Vector * const x, const Vector * const w, const Vector * const m, int *mc){
	// 1).initialize datastructures
	Matrix * paths = newMatrixByNumber(0, 1<<code->l, code->n);
	Vector *costs = newVectorByNumber(INF, 1 << code->l);
	costs->set(costs, 0, 0);
	int m_id = 1;					// message bit id;
	Vector * y = newVectorByNumber(0, x->size(x));

	// 2).run forward algorithm
	for (int i = 1; i <= code->n; i++){
		Vector *costs_old = newVectorByVector(costs);
		int hi = code->h->get(code->h, i-1);
		int ji = 1;
		for (int j = 1; j <= (1 << code->l); j++){
			int c1 = (int)costs_old->get(costs_old, ji-1) + ((int)x->get(x, i - 1)) * ((int)w->get(w, i - 1));
			int tmp1 = costs_old->get(costs_old, (ji - 1) ^ hi);
			int tmp2 = (1 - (int)x->get(x, i - 1)) * ((int)w->get(w, i - 1));
			int c2 = tmp1 + tmp2;
			c1 = c1 > INF ? INF : c1;
			c2 = c2 > INF ? INF : c2;
			if (c1 < c2){
				costs->set(costs, j-1, c1);
				paths->set(paths, j-1, i-1, ji);
			}
			else{
				costs->set(costs, j-1, c2);
				paths->set(paths, j-1, i-1, ((ji-1)^hi)+1);
			}
			ji += 1;
		}
		int loopTimes = code->shift->get(code->shift, i - 1);
		for (int j = 1; j <= loopTimes; j++){
			Vector *nv = newVector();
			int startK = m->get(m, m_id-1) == 0 ? 0 : 1;
			for (int k = startK; k < costs->size(costs); k += 2){
				nv->add(nv, costs->get(costs, k));
			}
			for (int k = 0; k < (1 << (code->l - 1)); k++){
				nv->add(nv, INF);
			}
			m_id += 1;
			freeVector(costs);
			costs = nv;
		}
		freeVector(costs_old);
#ifdef STC_DEBUG
		for (int i = 0; i < paths->rowSize(paths); i++){
			for (int j = 0; j < paths->colSize(paths); j++){
				if (paths->get(paths, i, j) == INF){
					printf("INF ");
					continue;
				}
				printf("%d ", paths->get(paths, i, j));
			}
			printf("\n");
		}
		printf("costs : ");
		for (int k = 0; k < costs->size(costs); k++){
			if (costs->get(costs, k) == INF){
				printf("INF ");
				continue;
			}
			printf("%d ", costs->get(costs, k));
		}
		printf("\n");
		printf("\n=====================================================\n");
#endif
	}
	// 3).backward run
	int ind = 0;
	int minCost = 0;
	minCost = minInVector(costs, &ind);
	ind += 1;
	m_id -= 1;
	for (int i = code->n; i >= 1; i--){
		for (int j = 1; j <= code->shift->get(code->shift, i - 1); j++){
			ind = 2 * ind + (int)m->get(m, m_id - 1) - 1;
			m_id -= 1;
		}
		int tmp = paths->get(paths, ind - 1, i - 1);
		y->set(y, i - 1, ind != tmp);
		ind = paths->get(paths, ind - 1, i - 1);
	}

	// 4).free
	freeMatrix(paths);
	freeVector(costs);
	
	*mc = minCost;
	return y;
}


/*
* @Desc   : 对含密二进制序列x进行解码, 得到二进制秘密数据.
* @Param  : *code, STC所需要的奇偶校验矩阵的相关信息.
* @Param  : *x, 含密二进制序列.
* @Return : 返回秘密二进制序列.
* @Authro : Shuaiji Lu
* @Date   : 2017/11/26
*/
Vector *calacSyndrome(const STCCode * const code, const Vector * const x){
	Vector *m = newVector();
	unsigned int tmp = 0;

	for (int i = 1; i <= code->n; i++){
		unsigned int hi = code->h->get(code->h, i-1);
		if (x->get(x, i-1) == 1){
			tmp ^= hi;
		}
		for (int j = 1; j <= code->shift->get(code->shift, i-1); j++){
			m->add(m, tmp%2);
			tmp >>= 1;
		}
	}
	return m;
}