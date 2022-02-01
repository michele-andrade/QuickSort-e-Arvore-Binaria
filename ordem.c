#include <stdio.h>
#include "ordem.h"
#include <time.h>
#include <limits.h>
#include <stdlib.h>

void troca(int vetor[], int i, int j){
    int aux = vetor[i];
    vetor[i] = vetor[j];
    vetor[j]= aux;
}

void insertionSort(int vetor[], int n){
    int i, j, aux;
    for(i=1; i<n; i++){
        aux=vetor[i];
        for(j=i-1; j>=0 && aux<vetor[j]; j--){
            vetor[j+1] = vetor[j];
        }
        vetor[j+1] = aux;
    }
}

int particaoaleatorio(int vetor[], int esq, int dir){
    int i,j,k;
    double d;
    d = (double) rand () / ((double) RAND_MAX + 1);
    k = d * (esq - dir + 1);
    int pivo = vetor[k];
    i = esq-1;
    for(j=esq; j<=dir-1; j++){
        if(vetor[j]<=pivo){
            i=i+1;
            troca(vetor, i, j);
        }
    }
    troca(vetor, i+1, dir);
    return i+1;
}

int particaomediana(int vetor[], int esq, int dir){
    int meio, a, b, c, mediana;
    meio=(esq+dir)/2;
    a=vetor[esq];
    b=vetor[meio];
    c=vetor[dir];
    //verificar qual é a mediana do vetor
    if(a<b){
        if(b<c){
            mediana=meio;
        }
        else{
            if(a<c){
                mediana=dir;
            }
            else{
                mediana=esq;
            }
        }
    }
    else{
        if(c<b){
            mediana=meio;
        }
        else{
            if(c<a){
                mediana=dir;
            }
            else{
                mediana=esq;
            }
        }
    }
    troca(vetor, mediana, esq);
    int pivo, i, j;
    pivo=vetor[dir];
    i = esq-1;
    for(j=esq; j<=dir-1; j++){
        if(vetor[j]<=pivo){
            i=i+1;
            troca(vetor, i, j);
        }
    }
    troca(vetor, i+1, dir);
    return i+1;
}

void QuickSortMediana(int vetor[], int esq, int dir){
    if(esq<dir){
        if((esq-dir)<4){
            insertionSort(vetor, dir);
        }
        else{
            int q=particaomediana(vetor, esq, dir);
            QuickSortMediana(vetor, dir, q-1);
            QuickSortMediana(vetor, q+1, dir);
        }
    }
}



void QuickSortaleatorio(int vetor[], int esq, int dir){
    if(esq<dir){
        if((esq-dir)<3){
            insertionSort(vetor, dir);
        }
        else{
            int q=particaoaleatorio(vetor, esq, dir);
            QuickSortaleatorio(vetor, dir, q-1);
            QuickSortaleatorio(vetor, q+1, dir);
        }
    }
}


void imprime(int vetor[], int n){
    for(int i=0; i<n; i++){
        printf("%d ", vetor[i]);
        
    }
    printf("\n");
}