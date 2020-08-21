/*
  Arquivo: main.c
  Autor: Pedro Di Santi
  Data: 20/08/2020 18:39
  Descrição:
    Este programa tem como finalidade explorar a manipulação de uma Árvore Binária. Ela implementa a criação de uma nova
        árvore, onde novos elementos podem ser inseridos.
    Além disso, podemos desenhar a árvore inserida de maneira gráfica. Também temos a implementação do caminhamento bfs,
    do caminhamentos recursivo eRd, do caminhamento recursivo Red e do caminhamento edR.
    Por fim, podemos calcular a quantidade de nós e a altura da árvore inserida.
  Funções baseadas em: https://pucsp.sharepoint.com/sites/EDNL/Material%20de%20Aula/CODIGOS/MODELO%20PROGRAMA.c
  De: Lisbete Madsen Barbosa
  Em: 19/03/13 14:49
*/

#include <stdlib.h>
#include <stdio.h>

#include "FilaPointer.h"
#include "Booleano.h"
#include "desenharArvore.h"

typedef struct No{
    int elemento;
    struct No * esq;
    struct No * dir;
} No;

typedef No* Arvore;

Arvore criarArvoreVazia( );
Arvore construirNovoNo(int valor);
Arvore inserirElemento(Arvore ap, int valor);
Arvore encontrarElementro(Arvore ap, int valor);
int contarNos(Arvore ap);
int contarFolhas(Arvore ap);
int obterAltura(Arvore ap);
void mostrarRaiz(Arvore);
void mostrarArvoreBFS(Arvore ap);
void mostrarArvoreRED(Arvore ap);
void mostrarArvoreERD(Arvore ap);
void mostrarArvoreEDR(Arvore ap);

int main()
{
    char ch = 'i';
    int data;
    Arvore tree = criarArvoreVazia();


    printf("\n"
           "______________MENU_______________"
           "\n "
           "(1) - Inserir elemento na árvore \n "
           "(2) - Encontrar elemento na árvore \n "
           "(3) - Desenhar árvore \n "
           "(4) - Mostrar árvore Red, eRd, edR, bfs \n "
           "(5) - Altura da árvore \n "
           "(6) - Número de folhas da árvore \n "
           "(7) - Número de nós da árvore \n "
           "(Q) - Sair\n"
           "__________________________________"
           );


    while(ch != 'q'){
        printf("\nComando: ");
        scanf(" %c",&ch);

        switch(ch)
        {
            case '1' :
                printf("\n Digite o elemento a ser inserido: ");
                scanf(" %d",&data);
                tree = inserirElemento(tree, data);
                break;
            case '2' :
                printf("\n Digite o elemento a ser buscado: ");
                scanf(" %d",&data);
                int encontrado = encontrarElementro(tree, data);
                if (encontrado == 1){
                    printf("\n O elemento %d foi encontrado.", data);
                } else{
                    printf("\n O elemento %d não foi encontrado.", data);
                }
                break;
            case '3' :
                desenharArvore(tree);
                break;
            case '4':
                printf("\n Árvore Red: ");
                mostrarArvoreRED(tree);

                printf("\n Árvore eRd: ");
                mostrarArvoreERD(tree);

                printf("\n Árvore edR: ");
                mostrarArvoreEDR(tree);

                printf("\n Árvore bfs: ");
                mostrarArvoreBFS(tree);
                break;
            case '5':
                printf("\n A altura da árvore é %d ", obterAltura(tree));
            case '6':
                printf("\n O número de folhas da árvore é %d ", contarFolhas(tree));
                break;
                break;
            case '7':
                printf("\n O número de nós da árvore é %d ", contarNos(tree));
                break;
            case 'q':
                exit(0);
            default :
                printf("\n invalid entry\n");

        }
    }
}

Arvore criarArvoreVazia( ){
    Arvore ap;
    ap = NULL;
    return ap;
}

Arvore construirNovoNo(int valor){
    No *novo = malloc(sizeof(No));

    novo->elemento = valor;
    novo->esq = NULL;
    novo->dir = NULL;

    return novo;
}

Arvore inserirElemento(Arvore ap, int valor){
    if(ap == NULL){
        return construirNovoNo(valor);
    }
    else if (ap->elemento < valor)
        ap->dir = inserirElemento(ap->dir, valor);
    else if (ap->elemento > valor)
        ap->esq = inserirElemento(ap->esq, valor);

    return ap;
}

Arvore encontrarElementro(Arvore ap, int valor){
    if(ap == NULL){
        return 0;
    }

    while(ap->elemento != valor){
        if(ap != NULL) {
            if(ap->elemento > valor){
                ap = ap->esq;
            }
            else {
                ap = ap->dir;
            }
            if(ap == NULL){
                return 0;
            }
        }
    }
    return 1;
}

int contarNos(Arvore ap) {
    int c = 1;

    if (ap != NULL) {
        c += contarNos(ap->esq);
        c += contarNos(ap->dir);
        return c;
    }
    else return 0;
}

int contarFolhas(Arvore ap){
    if(ap == NULL)
        return 0;
    else if(ap->esq == NULL && ap->dir == NULL)
        return 1;
    else
        return 1+ contarFolhas(ap->esq) + contarFolhas(ap->dir);
}

int obterAltura(Arvore ap){
    if (ap != NULL){
        int alturaEsq = obterAltura(ap->esq);
        int alturaDir = obterAltura(ap->dir);

        if (alturaEsq > alturaDir){
            return alturaEsq + 1;
        } else {
            return alturaDir + 1;
        }
    } else {
        return -1;
    }
}

void mostrarRaiz(Arvore ap){
    if (ap != NULL)
        printf(" %d  ",ap->elemento);
}

void mostrarArvoreERD(Arvore ap){
    if (ap != NULL){
        mostrarArvoreERD(ap->esq);
        mostrarRaiz(ap);
        mostrarArvoreERD(ap->dir);}
}

void mostrarArvoreRED(Arvore ap){
    if (ap != NULL){
        mostrarRaiz(ap);
        mostrarArvoreRED(ap->esq);
        mostrarArvoreRED(ap->dir);}
}

void mostrarArvoreEDR(Arvore ap){ // eRd
    if (ap != NULL){
        mostrarArvoreEDR(ap->esq);
        mostrarArvoreEDR(ap->dir);}
        mostrarRaiz(ap);
}

void mostrarArvoreBFS(Arvore ap){
    No *p, *e, *d;
    bool vazia;
    Fila f;

    if (ap != NULL){
        p = ap;
        criarFilaVazia(&f);
        pushFila(&f,p);
        do {
            p = acessarFila(&f);
            mostrarRaiz(p);
            popFila(&f);

            e = p->esq;
            if (e != NULL)
                pushFila(&f,e);

            d = p->dir;
            if (d != NULL)
                pushFila(&f,d);
        } while (verificarFilaVazia(&f) == FALSE);
    }
    else
        printf("\n arvore vazia \n");
}




