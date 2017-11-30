#include <stdio.h>

#include "String.h"
#include "sysser.h"
#include "Vector.h"
#include "stc.h"

void testSTC(){
	Vector *vx = funWrapperInts(newVectorByVector, 16, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0);
	Vector *vw = funWrapperInts(newVectorByVector, 16, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
	Vector *vm = funWrapperInts(newVectorByVector, 8, 0, 0, 0, 0, 0, 0, 0, 0);

	STCCode *code = newSTCCode(16, 2, 
		funWrapperInts(newVectorByVector, 16, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3),
		funWrapperInts(newVectorByVector, 16, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1));

	int minCost = 0;
	Vector * vy = dualViterbi(code, vx, vw, vm, &minCost);
	Vector * message = calacSyndrome(code, vy);

	printf("m : %s\n", toChars(vm->toString(vm)));
	printf("x : %s\n", toChars(vx->toString(vx)));
	printf("y : %s\n", toChars(vy->toString(vy)));
	printf("minCost : %d\n", minCost);
	printf("\nrecover message : %s", toChars(message->toString(message)));

	removeSTCCode(code);
	funWrapperPtrs(freeAllVector, 4, vx, vm, vw, vy, message);
}