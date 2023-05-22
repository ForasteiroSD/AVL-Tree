//
// Created by Vanessa on 27/04/2023.
//

#ifndef ARVOREBINARIA_ARVOREBINARIA_H
#define ARVOREBINARIA_ARVOREBINARIA_H

typedef struct no no;
typedef struct avl avl;

//Função que cria e retorna uma estrutura do tipo árvore
avl *criaArvore();

//Função que insere um elemento na árvore
//Retorna 1 se a inserção foi realizada com sucesso
//Retorna 0 se não foi possível realizar a inserção
int insereNo(avl *arv, int valor);

//Função que remove um elemento da árvore implementando a remoção por cópia usando o sucessor
//Retorna 1 se o elemento foi removido
//Retorna 0 se a árvore estiver vazia
//Retorna -1 caso o elemento a ser removido não esteja na árvore
int removeNo(avl *arv, int valor);

//Função que imprime a árvore em ordem
//printf("%d - %d\n",chave, pai)
void imprimeOrdem(no *raiz);

//Função que imprime a árvore em pré-ordem
//printf("%d - %d\n",chave, pai)
void imprimePreOrdem(no *raiz);

//Função que retorna a raiz da árvore
no *getRaiz(avl *arv);

//Função que retorna a quantidade de elementos da árvore
int getNumElementos(avl *arv);

//Função que lê um arquivo com números inteiros e carrega na árvore
void processaCarga(avl *arv, char *nomeArquivo);



/***** AVL *****/

void atualizaFB_insercao(avl *arv, no *novoNo);

void atualizaFB_remocao(avl *arv, no *noRemovido, int chave);

void balaneceamento(avl *arv, no *noDesbalanceado);

void rotacaoDir(no *noDesbalanceado);

void rotacaoEsq(no *noDesbalanceado);

#endif //ARVOREBINARIA_ARVOREBINARIA_H