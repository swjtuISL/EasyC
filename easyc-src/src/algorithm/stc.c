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
* @Desc   : STCCode�Ĺ�����.
* @Param  : n
* @Param  : l
* @Param  : *h
* @Param  : *shift
* @Return : STCCodeʵ��
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
* @Desc   : �ͷ�STCCode�е�����.���ͷ����е������õ��ڴ�.
* @Param  : *code, ���ͷŵ�����.
* @Return : ��
* @Authro : Shuaiji Lu
* @Date   : 2017/11/26
*/
void freeSTCCode(STCCode * const code){
	free(code);
}

/*
* @Desc   : �ͷ�STCCode�е�����, �������е�Vector����.
* @Param  : *code, ���ͷŵ�����.
* @Return : ��
* @Authro : Shuaiji Lu
* @Date   : 2017/11/26
*/
void removeSTCCode(STCCode * const code){
	freeVector(code->shift);
	freeVector(code->h);
	free(code);
}

/*
* @Desc   : ����STC��ԭʼ���������ݽ��б��룬ʹ�������������������.
* @Param  : *code, STC����Ҫ����żУ�����������Ϣ.
* @Param  : *x, ԭʼ����������.
* @Param  : *m, ������Ϣ����������.
* @Param  : *mc, ��������С���.
* @Param  : *w, ԭʼ�����ж�Ӧλ���޸���ɵ���ʧȨ��.
* @Return : ���غ��ܵĶ���������.
* @Authro : Shuaiji Lu
* @Date   : 2017/11/26
*/
Vector *dualViterbi(const STCCode * const code, const Vector * const x, const Vector * const w, const Vector * const m, int *mc){
	// 1).initialize datastructures
	Matrix * paths = newMatrixByNumber(0, 1<<code->l, code->n);
	Vector *costs = newVectorByNumber(INF, 1 << code->l);
	costs->setInt(costs, 0, 0);
	int m_id = 1;					// message bit id;
	Vector * y = newVectorByNumber(0, x->size(x));

	// 2).run forward algorithm
	for (int i = 1; i <= code->n; i++){
		Vector *costs_old = newVectorByVector(costs);
		int hi = code->h->getInt(code->h, i-1);
		int ji = 1;
		for (int j = 1; j <= (1 << code->l); j++){
			int c1 = costs_old->getInt(costs_old, ji-1) + (x->getInt(x, i - 1)) * (w->getInt(w, i - 1));
			int tmp1 = costs_old->get(costs_old, (ji - 1) ^ hi);
			int tmp2 = (1 - x->getInt(x, i - 1)) * w->getInt(w, i - 1);
			int c2 = tmp1 + tmp2;
			c1 = c1 > INF ? INF : c1;
			c2 = c2 > INF ? INF : c2;
			if (c1 < c2){
				costs->setInt(costs, j-1, c1);
				paths->setInt(paths, j-1, i-1, ji);
			}
			else{
				costs->setInt(costs, j-1, c2);
				paths->setInt(paths, j-1, i-1, ((ji-1)^hi)+1);
			}
			ji += 1;
		}
		int loopTimes = code->shift->getInt(code->shift, i - 1);
		for (int j = 1; j <= loopTimes; j++){
			Vector *nv = newVector();
			int startK = m->getInt(m, m_id-1) == 0 ? 0 : 1;
			for (int k = startK; k < costs->size(costs); k += 2){
				nv->addInt(nv, costs->getInt(costs, k));
			}
			for (int k = 0; k < (1 << (code->l - 1)); k++){
				nv->addInt(nv, INF);
			}
			m_id += 1;
			freeVector(costs);
			costs = nv;
		}
		freeVector(costs_old);
#ifdef STC_DEBUG
		for (int i = 0; i < paths->rowSize(paths); i++){
			for (int j = 0; j < paths->colSize(paths); j++){
				if (paths->getInt(paths, i, j) == INF){
					printf("INF ");
					continue;
				}
				printf("%d ", paths->getInt(paths, i, j));
			}
			printf("\n");
		}
		printf("costs : ");
		for (int k = 0; k < costs->size(costs); k++){
			if (costs->getInt(costs, k) == INF){
				printf("INF ");
				continue;
			}
			printf("%d ", costs->getInt(costs, k));
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
		for (int j = 1; j <= code->shift->getInt(code->shift, i - 1); j++){
			ind = 2 * ind + m->getInt(m, m_id - 1) - 1;
			m_id -= 1;
		}
		int tmp = paths->getInt(paths, ind - 1, i - 1);
		y->setInt(y, i - 1, ind != tmp);
		ind = paths->getInt(paths, ind - 1, i - 1);
	}

	// 4).free
	freeMatrix(paths);
	freeVector(costs);
	
	*mc = minCost;
	return y;
}


/*
* @Desc   : �Ժ��ܶ���������x���н���, �õ���������������.
* @Param  : *code, STC����Ҫ����żУ�����������Ϣ.
* @Param  : *x, ���ܶ���������.
* @Return : �������ܶ���������.
* @Authro : Shuaiji Lu
* @Date   : 2017/11/26
*/
Vector *calacSyndrome(const STCCode * const code, const Vector * const x){
	Vector *m = newVector();
	unsigned int tmp = 0;

	for (int i = 1; i <= code->n; i++){
		unsigned int hi = code->h->getInt(code->h, i-1);
		if (x->getInt(x, i-1) == 1){
			tmp ^= hi;
		}
		for (int j = 1; j <= code->shift->getInt(code->shift, i-1); j++){
			m->addInt(m, tmp%2);
			tmp >>= 1;
		}
	}
	return m;
}