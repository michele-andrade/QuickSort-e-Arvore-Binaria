#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

struct arvore{
    char info;
    char operador;
    char verifica;
    int tamanho;
    int resultado;
    struct arvore* esq;
    struct arvore* dir;
};

//inicia uma arvore nula
Arvore* inicia(){
    return NULL;
}

//cria uma arvore
Arvore* cria(char c){
    Arvore *a = (Arvore*)malloc(sizeof(Arvore));
    a->esq=NULL;
    a->dir=NULL;
    if(testaOperador(c)==1){
        a->operador='#';
    }
    else{
        a->operador=c;
    }
    a->info=c;
    a->tamanho = 0;
    a->verifica = 'n';
    a->resultado = 0;
    return a;
}

//funções para inserir arvore na direita e na esquerda
Arvore* insereArvoreDir(Arvore** a, char c){
    Arvore *aux= cria(c);
    (*a)->dir = aux;
    return aux;
}
Arvore* insereArvoreEsq(Arvore** a, char c){
    Arvore *aux= cria(c);
    (*a)->esq = aux;
    return aux;
}

//testa se o char é um operador: retorna 0 para operador e 1 para numero
int testaOperador(char c){
    switch (c) {
        case '-': return 0;
        case '+': return 0;
        case '/': return 0;
        case '*': return 0;
        default: return 1;
    }
}
/*testa se uma posicao em que quer inserir uma arvore é valida: retorna 1 para posicao valida a esquerda
retorna 2 para posicao valida a direita e 0 para nenhuma das posicoes validas*/
int testaPosicao(Arvore* no){
    if(no->esq == NULL){
        if(testaOperador(no->info)==0){
            return 1;
        }
        else{
            return 0;
        }
    }
    else if(no->dir == NULL){
        if(testaOperador(no->info)==0){
            return 2;
        }
        else{
            return 0;
        }
    }
    else{
        return 0;
    }
}
/*funcao recebe a arvore e a informacao a ser inserida, testa se é um operador ou numero,
testa a posicao a ser inserida e vai caminhando pela arvore de maneira recursiva
para poder inserir no local desejado */
int insere(Arvore** raiz, char c){
    if(testaOperador((*raiz)->info)==1){
        return 0;
    }
    else{
        int temp = testaPosicao(*raiz);
        if(temp ==1){
            insereArvoreEsq(&(*raiz), c);
            (*raiz)->tamanho++;
            return 1;
        }
        else{
            int inserido = insere(&(*raiz)->esq, c);
            if(inserido == 1){
                (*raiz)->tamanho++;
                return 1;
            }
            if(temp == 2){
                insereArvoreDir(&(*raiz), c);
                (*raiz)->tamanho++;
                return 1;
            }
            inserido = insere(&(*raiz)->dir, c);
            if(inserido == 1){
                (*raiz)->tamanho++;
                return 1;
            }
            else {
                return -1;
            }
        }  
    }
}

void libera(Arvore** a){
    if(*a!=NULL){
        libera(&(*a)->esq);
        libera(&(*a)->dir);
        free(*a);
    }
}
// retorna o tamanho da arvore
int getTamanho(Arvore *a){
    return a->tamanho;
}
//funcao que executa uma das operacoes matematicas
int executaOperacao(int operandoEsq, int operandoDir, char operador){
    switch (operador)
    {
    case '+': return operandoEsq + operandoDir;
    case '-': return operandoEsq - operandoDir;
    case '/': return operandoEsq / operandoDir;
    case '*': return operandoEsq * operandoDir;
    }
    return -1;
}
/*Processa apenas um no da arvore, ou seja verifica uma raiz que contem operador, procura na direita e esquerda
os operandos realiza a operação e retorna um novo no com o resultado da operacao realizada*/
Arvore* processaNo(Arvore *no, char operador)
{
    Arvore *aux = NULL;
    int operandoEsq = (int) no->esq->info;
    int operandoDir = 0;
    int temp = -1;
    
    if(testaOperador(no->dir->info) == 0 && no->dir->esq != NULL) {
        operandoDir = (int) no->dir->esq->info;
        temp = 0;
    }
    else {
        operandoDir = (int) no->dir->info;
    }
    if(operandoEsq >= 48 && operandoEsq <= 57) {
        operandoEsq = operandoEsq - 48;
    }
    if(operandoDir >= 48 && operandoDir <= 57) {
        operandoDir = operandoDir - 48;
    }

    int resultado = executaOperacao(operandoEsq, operandoDir, operador);
    char resultado_char = (char) resultado;
    aux = cria(resultado_char);
    aux->verifica = 's';
    aux->resultado = resultado;
    if( temp == 0) {
        aux->verifica = 'n';
        aux->operador = '#';
        no->dir->esq = aux;
        no->dir->verifica = 's';
        return no->dir;
    }
    return aux;
}

/*A funcao ira receber uma arvore e um operador e ira percorrer a arvore na ordem de caminhamento central, 
ao encontrar um no valido chama a funcao processaNo que ira retornar um novo no referente a operacao matetica.
Ao receber o novo no, ele atualiza o no anterior com o resultado. 
Um exemplo abaixo é um no em que seu operador é + e aponta para um a direita em que sua info é 3
e um para esquerda em que sua info é 5, dessa forma realiza a operacao e atualiza o no com a info + para um novo no 
com a info 8.
   +           8
 /   \  ->   /   \
 5    3    NULL  NULL      */
Arvore* processaOperador(Arvore *raiz, char operador) {
    if(raiz == NULL) {
        return NULL;
    }
    if(testaOperador(raiz->info) == 0 && raiz->info == operador && raiz->operador == operador) {
        if(raiz->dir->info == operador && raiz->operador == operador) {
            Arvore *aux = NULL;
            aux = processaOperador(raiz->dir, operador);
            raiz->dir = aux;
        }
        return processaNo(raiz, operador);
    }

    Arvore *aux = NULL;
    aux = processaOperador(raiz->esq, operador);

    if(aux != NULL) {
        if(aux->verifica == 's') {
            aux->verifica = 'n';
            raiz->esq = aux;
        }
    }

    aux = processaOperador(raiz->dir, operador);

    if(aux != NULL) {
        if(aux->verifica == 's') {
            aux->verifica = 'n';
            raiz->dir = aux;
        }
    }
    return raiz;
}

/* funcao que analisa a precedencia dos operadores. 
Cria um vetor de char que recebe os operadores na ordem de precedencia matematica. Com o loop vai iterando 
sobre esses operadores e chamando a funcao processaOperador que realiza o calculo e atualiza a arvore. 
por fim ela retorna o resultado de todas as operacoes realizadas na arvore */
int precedencia(Arvore *raiz){
    char precedencia[] = "*/-+";

    for (int i = 0; i < 4; i++) {
        raiz = processaOperador(raiz, precedencia[i]);
    }

    int resultado = (int) raiz->info;
    return resultado;
}

