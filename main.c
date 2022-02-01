#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <stdbool.h>
#include "ordem.h"

int main(){
    FILE *arq;
    arq = fopen("b.txt", "r");
    int *vetor,n=500;
    vetor= malloc(n * sizeof(int));
	for(int i = 0; i < n; i++){
        fscanf(arq, "%d",&vetor[i]);
	}
    fclose(arq); 
    QuickSortaleatorio(vetor, 1,n);
    imprime(vetor,n);
    QuickSortMediana(vetor, 1,n);
    imprime(vetor,n);
    free(vetor);
    return 0;
}