
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"

int main(){
    Arvore *a = inicia();
    char expressao[20];
    printf("Digite uma expressão a ser calculada: ");
    scanf("%s", expressao);

    
    int tam = strlen(expressao);
    printf("Tamanho da expressao: %d\n", tam);
    for(int i=1; i<tam; i=i+2){
        if(a == NULL){
            a = cria(expressao[i]);
            insere(&a, expressao[i-1]);
        }
        else{
            insere(&a, expressao[i]);
            insere(&a, expressao[i-1]);
        }
    }
    insere(&a, expressao[tam-1]);

    int resultado = precedencia(a);

    printf("resultado: %d\n", resultado);
    
    libera(&a);
}