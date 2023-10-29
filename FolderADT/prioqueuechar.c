#include <stdio.h>
#include <stdlib.h>
#include "prioqueuechar.h"

boolean IsEmptyQueue(PrioQueueChar Q){
	return (Head(Q) == Nil && Tail(Q) == Nil);
}

boolean IsFullQueue(PrioQueueChar Q){
	return (NBElmtQueue(Q) == MaxEl(Q));
}

int NBElmtQueue(PrioQueueChar Q){
	if(IsEmptyQueue(Q)){
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

void MakeEmptyQueue(PrioQueueChar * Q, int Max){
	(*Q).T = (infotype *) malloc((Max+1) * sizeof(infotype));
	if((*Q).T != NULL){
		MaxEl(*Q) = Max;
		Head(*Q) = Nil;
		Tail(*Q) = Nil;
	}else{
		MaxEl(*Q) = 0;
	}
}

void DeAlokasiQueue(PrioQueueChar * Q){
	MaxEl(*Q) = 0;
	free((*Q).T);
}

void masuk(PrioQueueChar * Q, infotype X){
	if(IsEmptyQueue(*Q)){
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
	return (x->popularity > y->popularity);
}

void Enqueue(PrioQueueChar * Q, infotype X){
	int i, count;
	masuk(Q, X);
	count = NBElmtQueue(*Q);
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
	if(NBElmtQueue(*Q) == 1){
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
	int len = NBElmtQueue(Q);
	for(int i=0;i<len;i++){
		printf("%d %c\n",Q.T[Head(Q)].popularity,Q.T[Head(Q)].popularity);
		if(Head(Q)==MaxEl(Q)){
			Head(Q)=1;
		}
		else{
			Head(Q)++;
		}
	}
	printf("#\n");
}