#ifndef arvore_h
#define arvore_h

typedef struct arvore Arvore;


Arvore* inicia();
Arvore* cria(char c);
int testaOperador(char c);
Arvore* insereArvoreDir(Arvore** a, char c);
Arvore* insereArvoreEsq(Arvore** a, char c);
int insere(Arvore** a, char c);
void libera(Arvore** a);
int getTamanho(Arvore *a);
int precedencia(Arvore *raiz);


#endif