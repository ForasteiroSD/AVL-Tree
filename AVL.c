#include <stdio.h>
#include <stdlib.h>
#include "AVL.h"

typedef struct no {
    int chave;
    int fb;
    no *Fesq;
    no *Fdir;
    no *pai;
} no;

typedef struct avl {
    no *sentinela;
    int numElementos;
} avl;

//Função que cria e retorna uma estrutura do tipo árvore
avl *criaArvore() {
    avl *arv = (avl*) malloc(sizeof(avl));
    
    arv->sentinela = (no*) malloc(sizeof(no));

    arv->sentinela->chave = -1000;
    arv->sentinela->Fesq = NULL;
    arv->sentinela->Fdir = NULL;
    arv->sentinela->pai = NULL;
    arv->numElementos = 0;

    return arv;
}

//Função que insere um elemento na árvore
//Retorna 1 se a inserção foi realizada com sucesso
//Retorna 0 se não foi possível realizar a inserção
int insereNo(avl *arv, int valor) {
    // Verifica se a árvore existe
    no *noInserir = malloc(sizeof(no));
    if(arv == NULL) return 0;

    // Verifica se já existe algum elemento na árvore e adiciona na primeira posição
    if(arv->numElementos == 0) {
        noInserir->chave = valor;
        noInserir->fb = 0;
        noInserir->Fesq = NULL;
        noInserir->Fdir = NULL;
        noInserir->pai = arv->sentinela;

        arv->sentinela->Fdir = noInserir;
        arv->numElementos++;

        atualizaFB_insercao(arv, noInserir);
        return 1;
    } else {
        no *aux = arv->sentinela->Fdir;

        while(1 == 1) {
            if(valor < aux->chave) {
                if(aux->Fesq == NULL) {
                    noInserir->chave = valor;
                    noInserir->fb = 0;
                    noInserir->Fesq = NULL;
                    noInserir->Fdir = NULL;
                    noInserir->pai = aux;

                    aux->Fesq = noInserir;
                    arv->numElementos++;

                    atualizaFB_insercao(arv, noInserir);
                    return 1;
                } else aux = aux->Fesq;
            } else {
                if(aux->Fdir == NULL) {
                    noInserir->chave = valor;
                    noInserir->fb = 0;
                    noInserir->Fesq = NULL;
                    noInserir->Fdir = NULL;
                    noInserir->pai = aux;

                    aux->Fdir = noInserir;
                    arv->numElementos++;

                    atualizaFB_insercao(arv, noInserir);
                    return 1;
                } else aux = aux->Fdir;
            }
        }
    }
}

//Função que remove um elemento da árvore implementando a remoção por cópia usando o sucessor
//Retorna 1 se o elemento foi removido
//Retorna 0 se a árvore estiver vazia
//Retorna -1 caso o elemento a ser removido não esteja na árvore
int removeNo(avl *arv, int valor) {
    if(arv->numElementos == 0) return 0;

    no *aux = arv->sentinela;
    while(1 == 1) {
        if(valor == aux->chave) {
            //Nó a ser removido não possui nenhum filho
            if(aux->Fesq == NULL && aux->Fdir == NULL) {
                if(aux->pai->chave < aux->chave || aux == arv->sentinela->Fdir) {
                    //Pai na esquerda
                    aux->pai->Fdir = NULL;
                } else {
                    //Pai na direita
                    aux->pai->Fesq = NULL;
                }

                atualizaFB_remocao(arv, aux, aux->chave);
                free(aux);
                arv->numElementos--;
                return 1;

            //Nó a ser removido possui apenas o filho da esquerda
            } else if(aux->Fesq != NULL && aux->Fdir == NULL) {
                //Verifica se o pai está a esqueda ou direita do filho
                if(aux->pai->chave < aux->chave || aux == arv->sentinela->Fdir) {
                    //Pai na esquerda
                    aux->pai->Fdir = aux->Fesq;
                } else {
                    //Pai na direita
                    aux->pai->Fesq = aux->Fesq;
                }
                if(aux->Fesq != NULL) aux->Fesq->pai = aux->pai;
                atualizaFB_remocao(arv, aux, aux->chave);
                free(aux);
                arv->numElementos--;
                return 1;

            //Nó a ser removido possui apenas o filho da direita
            } else if(aux->Fesq == NULL && aux->Fdir != NULL) {
                //Verifica se o pai está a esqueda ou direita do filho
                if(aux->pai->chave < aux->chave || aux == arv->sentinela->Fdir) {
                    //Pai na esquerda
                    aux->pai->Fdir = aux->Fdir;
                } else {
                    //Pai na direita
                    aux->pai->Fesq = aux->Fdir;
                }
                if(aux->Fdir != NULL) aux->Fdir->pai = aux->pai;
                atualizaFB_remocao(arv, aux, aux->chave);
                free(aux);
                arv->numElementos--;
                return 1;

            //Nó a ser removido possui dois filhos
            } else if(aux->Fesq != NULL && aux->Fdir != NULL) {
                //Cria nó cópia (elemento mais a esqueda do elemento a direita da auxiliar)
                no *copia = aux->Fdir;
                while(copia->Fesq != NULL) copia = copia->Fesq;

                //Caso copia seja uma folha
                if(copia->Fdir == NULL) {
                    aux->chave = copia->chave;
                    copia->pai->Fesq = NULL;
                }
                else /*Caso copia tenha um filho (a direita)*/ {
                    aux->chave = copia->chave;

                    if(copia->pai != aux) copia->pai->Fesq = copia->Fdir;
                    else aux->Fdir = copia->Fdir;
                    copia->Fdir->pai = copia->pai;
                }
                atualizaFB_remocao(arv, aux, aux->chave);
                free(copia);
                arv->numElementos--;
                return 1;
            }
        }

        //Caos o valor seja menor que o atual
        if(valor < aux->chave) {
            if(aux->Fesq == NULL) return -1;
            else aux = aux->Fesq;
        } else /*Caos o valor seja maior que o atual*/ {
            if(aux->Fdir == NULL) return -1;
            else aux = aux->Fdir;
        }
    }
}

//Função que imprime a árvore em ordem
//printf("%d - %d\n",chave, pai)
void imprimeOrdem(no *raiz) {
    if(raiz->Fesq != NULL) imprimeOrdem(raiz->Fesq);
    printf("no: %d - pai: %d - fb: %d\n", raiz->chave, raiz->pai->chave, raiz->fb);
    if(raiz->Fdir != NULL) imprimeOrdem(raiz->Fdir);
}

//Função que imprime a árvore em pré-ordem
//printf("%d - %d\n",chave, pai)
void imprimePreOrdem(no *raiz) {
    printf("no: %d - pai: %d - fb: %d\n", raiz->chave, raiz->pai->chave, raiz->fb);
    if(raiz->Fesq != NULL) imprimePreOrdem(raiz->Fesq);
    if(raiz->Fdir != NULL) imprimePreOrdem(raiz->Fdir);
}

//Função que retorna a raiz da árvore
no *getRaiz(avl *arv) {
    return arv->sentinela->Fdir;
}

//Função que retorna a quantidade de elementos da árvore
int getNumElementos(avl *arv) {
    return arv->numElementos;
}

//Função que lê um arquivo com números inteiros e carrega na árvore
void processaCarga(avl *arv, char *nomeArquivo) {
    int chave;
    FILE *arq = fopen(nomeArquivo, "r");

    while(!feof(arq)) {
        fscanf(arq, "%d\n", &chave);
        insereNo(arv, chave);
    }

    fclose(arq);
}

/***** AVL *****/

void atualizaFB_insercao(avl *arv, no *novoNo) {
    no *aux = novoNo;

    do {
        if(aux->chave < aux->pai->chave) aux->pai->fb = aux->pai->fb - 1;
        else aux->pai->fb = aux->pai->fb + 1;
        aux = aux->pai;
    } while(aux != arv->sentinela->Fdir && aux != arv->sentinela && aux->fb != 0 && aux->fb != 2 && aux->fb != -2);

    if(aux->fb == 2 || aux->fb == -2) {
        balaneceamento(arv, aux);
    }
}

void atualizaFB_remocao(avl *arv, no *noRemovido, int chave){
    no *aux = noRemovido;

    do {
        aux = aux->pai;
        if(chave < aux->chave) aux->fb++;
        else aux->fb--;
    } while(aux != arv->sentinela->Fdir && aux->fb == 0);

    if(aux->fb == 2 || aux->fb == -2) {
        balaneceamento(arv, aux);
        if(aux != arv->sentinela->Fdir && aux->pai->fb == 0) atualizaFB_remocao(arv, aux->pai, aux->chave);
    }
}

void balaneceamento(avl *arv, no *noDesbalanceado) {
    no *filho;
    // Rotação à direita
    if(noDesbalanceado->fb == -2) {
        filho = noDesbalanceado->Fesq;
        // Rotação dupla (esquerda depois direita)
        if(filho->fb == 1) {
            int fbNeto = filho->Fdir->fb;
            rotacaoEsq(filho);
            rotacaoDir(noDesbalanceado);
            // Atualização do fb
            if(fbNeto == -1) noDesbalanceado->fb = 1;
            else if(fbNeto == 1) filho->fb = -1;
        } else /* Rotação simples */ {
            int fbFilho = filho->fb;
            rotacaoDir(noDesbalanceado);
            if(fbFilho == 0) {
                noDesbalanceado->fb = -1;
                filho->fb = 1;
            }
        }
    } else /*Rotação á esquerda*/ {
        filho = noDesbalanceado->Fdir;
        // Rotação dupla (direita depois esquerda)
        if(filho->fb == -1) {
            int fbNeto = filho->Fesq->fb;
            rotacaoDir(filho);
            rotacaoEsq(noDesbalanceado);
            // Atualização do fb
            if(fbNeto == -1) filho->fb = 1;
            else if(fbNeto == 1) noDesbalanceado->fb = -1;
        } else /* Rotação simples */ {
            int fbFilho = filho->fb;
            rotacaoEsq(noDesbalanceado);
            if(fbFilho == 0) {
                noDesbalanceado->fb = 1;
                filho->fb = -1;
            }
        }
    }
}

void rotacaoDir(no *noDesbalanceado) {
    no *filho = noDesbalanceado->Fesq;

    // Zerando FBs
    noDesbalanceado->fb = 0;
    filho->fb = 0;
    if(filho->Fesq != NULL) filho->Fesq->fb = 0;

    // Rotação
    noDesbalanceado->Fesq = filho->Fdir;
    if(filho->Fdir != NULL) filho->Fdir->pai = noDesbalanceado;
    filho->pai = noDesbalanceado->pai;
    if(noDesbalanceado == noDesbalanceado->pai->Fesq) noDesbalanceado->pai->Fesq = filho;
    else noDesbalanceado->pai->Fdir = filho;
    filho->Fdir = noDesbalanceado;
    noDesbalanceado->pai = filho;
}

void rotacaoEsq(no *noDesbalanceado) {
    no *filho = noDesbalanceado->Fdir;

    // Zerando FBs
    noDesbalanceado->fb = 0;
    filho->fb = 0;
    //if(filho->Fdir != NULL) filho->Fdir->fb = 0;

    // Rotação
    noDesbalanceado->Fdir = filho->Fesq;
    if(filho->Fesq != NULL) filho->Fesq->pai = noDesbalanceado;
    filho->pai = noDesbalanceado->pai;
    if(noDesbalanceado == noDesbalanceado->pai->Fesq) noDesbalanceado->pai->Fesq = filho;
    else noDesbalanceado->pai->Fdir = filho;
    filho->Fesq = noDesbalanceado;
    noDesbalanceado->pai = filho;
}