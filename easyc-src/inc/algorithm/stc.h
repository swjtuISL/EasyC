#ifndef __STC_H
#define __STC_H

struct Vector;
struct STCCode;
typedef struct Vector Vector;
typedef struct STCCode STCCode;

struct STCCode{
	int n;
	int l;
	Vector *h;
	Vector *shift;
};

STCCode *newSTCCode(int n, int l, Vector *const h, Vector *shift);
void freeSTCCode(STCCode * const code);
void removeSTCCode(STCCode * const code);

Vector *dualViterbi(const STCCode * const code, const Vector * const x, const Vector * const w, const Vector * const m, int *mc);
Vector *calacSyndrome(const STCCode * const code, const Vector * const x);

#endif