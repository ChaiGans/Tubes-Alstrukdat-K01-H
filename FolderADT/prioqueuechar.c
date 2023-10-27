#include <stdio.h>
#include <stdlib.h>
#include "prioqueuechar.h"

boolean IsEmpty(PrioQueueChar Q){
	return (Head(Q) == Nil && Tail(Q) == Nil);
}

boolean IsFull(PrioQueueChar Q){
	return (NBElmt(Q) == MaxEl(Q));
}

int NBElmt(PrioQueueChar Q){
	if(IsEmpty(Q)){
		return 0;
	}
	if(Head(Q) == Tail(Q)){
		return 1;
	}
	if(Head(Q) > Tail(Q)){
		return Tail(Q) - Head(Q) + MaxEl(Q) + 1;
	}
	return Tail(Q) - Head(Q) + 1;
}

void MakeEmpty(PrioQueueChar * Q, int Max){
	(*Q).T = (infotype *) malloc((Max+1) * sizeof(infotype));
	if((*Q).T != NULL){
		MaxEl(*Q) = Max;
		Head(*Q) = Nil;
		Tail(*Q) = Nil;
	}else{
		MaxEl(*Q) = 0;
	}
}

void DeAlokasi(PrioQueueChar * Q){
	MaxEl(*Q) = 0;
	free((*Q).T);
}

void masuk(PrioQueueChar * Q, infotype X){
	if(IsEmpty(*Q)){
		Head(*Q) = 0;
		Tail(*Q) = 0;
	}else{
		if(Tail(*Q) == MaxEl(*Q)-1){
			Tail(*Q) = 0;
		}
		else{
			Tail(*Q)++;
		}
	}
	InfoTail(*Q) = X;
}

int compare(const void * a, const void * b){
	infotype *x = (infotype *)a;
	infotype *y = (infotype *)b;
	return (x->prio > y->prio);
}

void Enqueue(PrioQueueChar * Q, infotype X){
	int i, count;
	masuk(Q, X);
	count = NBElmt(*Q);
	infotype * temp = (infotype *) malloc(count * sizeof(infotype));
	for(i = 0; i < count; i++){
		Dequeue(Q, &temp[i]);
	}
	qsort(temp, count, sizeof(infotype), compare);
	for(i=0;i<count;i++){
		masuk(Q, temp[i]);
	}
}

void Dequeue(PrioQueueChar * Q, infotype * X){
	*X = Elmt(*Q, Head(*Q));
	if(NBElmt(*Q) == 1){
		Head(*Q) = Nil;
		Tail(*Q) = Nil;
	}
	else{
		if(Head(*Q) == MaxEl(*Q)-1){
			Head(*Q) = 0;
		}
		else{
			Head(*Q)++;
		}
	}
}

void PrintPrioQueueChar (PrioQueueChar Q){
	int len = NBElmt(Q);
	for(int i=0;i<len;i++){
		printf("%d %c\n",Q.T[Head(Q)].prio,Q.T[Head(Q)].info);
		if(Head(Q)==MaxEl(Q)){
			Head(Q)=1;
		}
		else{
			Head(Q)++;
		}
	}
	printf("#\n");
}