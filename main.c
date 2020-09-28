/*
  Arquivo: main.c
  Autor: Pedro Di Santi
  Data: 20/08/2020 18:39
  Atualizado em: 27/09/2020 20:55
  Descrição:
    Este programa tem como finalidade explorar a manipulação de uma Árvore Binária. Ela implementa a criação de uma nova
        árvore, onde novos elementos podem ser inseridos, buscados, removidos, encontrados sucessores e antecessores,
        além de ancestrais em comum.
    Além disso, podemos desenhar a árvore inserida de maneira gráfica. Também temos a implementação do caminhamento bfs,
        do caminhamentos recursivo eRd, do caminhamento recursivo Red e do caminhamento edR.
    Por fim, podemos calcular a quantidade de nós e a altura da árvore inserida.
  Funções baseadas em: https://pucsp.sharepoint.com/sites/EDNL/Material%20de%20Aula/CODIGOS/MODELO%20PROGRAMA.c
  De: Lisbete Madsen Barbosa
  Em: 19/03/13 14:49
*/

#include <stdio.h>
#include <stdlib.h>
#include "Booleano.h"
#include "FilaPointer.h"
#include "PilhaPointer.h"
#include "desenharArvore.h"


typedef struct No{
    int chave;
    struct No * pai;
    struct No * esq;
    struct No * dir;
} No;

typedef No *Arvore;

Arvore criarArvoreVazia( );
Arvore buscarItem(Arvore, int);
Arvore inserirElemento(Arvore, int);

No * minValor(No*);
No * maxValor(No*);
No * rodarDireita(No*);
No * criarNoVazio(int);
No * rodarEsquerda(No*);
No * rodarDuplaDireita(No*);
No * rodarDuplaEsquerda(No*);
No * obterSucessor(Arvore, No*);
No * obterAnterior(Arvore, No*);
No * obterAncestral(Arvore , No*, No*);
No * buscarItemRecursivo(Arvore, int);
No * obterAncestralR(Arvore , No*, No*);

int contarNos(Arvore);
int obterAltura(Arvore);
int contarFolhas(Arvore);

void mostrarRaiz(Arvore);
void mostrarArvore(Arvore);
void mostrarUltimo(Arvore);
void mostrarPrimeiro(Arvore);
void mostrarArvoreBFS(Arvore);
void mostrarArvoreRED(Arvore);
void mostrarArvoreERD(Arvore);
void mostrarArvoreEDR(Arvore);

int main(){
    char ch = 'i';
    int valor;
    Arvore arvore = criarArvoreVazia();


    printf("\n"
           "______________MENU_______________"
           "\n "
           "(1) - Inserir item na árvore \n "
           "(2) - Encontrar item na árvore \n "
           "(3) - Desenhar árvore \n "
           "(4) - Mostrar árvore Red, eRd, edR, bfs \n "
           "(5) - Mostrar informações da árvore \n "
           "(6) - Rotacionar árvore para direita \n "
           "(7) - Rotacionar árvore para esquerda \n "
           "(8) - Rotacionar árvore para dupla direita \n "
           "(9) - Rotacionar árvore para dupla esquerda \n "
           "(10) - Mostrar anterior e sucessor \n "
           "(Q) - Sair\n"
           "__________________________________"
    );

    arvore = inserirElemento(arvore, 20);
    arvore = inserirElemento(arvore, 10);
    arvore = inserirElemento(arvore, 25);
    arvore = inserirElemento(arvore, 8);
    arvore = inserirElemento(arvore, 12);
    arvore = inserirElemento(arvore, 11);
    arvore = inserirElemento(arvore, 22);
    arvore = inserirElemento(arvore, 24);

    while(ch != 'q'){
        printf("\n COMANDO: ");
        scanf(" %c",&ch);

        switch(ch)
        {
            case '1' :
                printf("\n Digite o item a ser inserido: ");
                scanf(" %d", &valor);
                arvore = inserirElemento(arvore, valor);

                break;
            case '2' :
                printf("\n Digite o item a ser buscado: ");
                scanf("%d", &valor);

                //arvore = buscarItem(arvore, valor);
                arvore = buscarItemRecursivo(arvore, valor);

                if(arvore == NULL)
                    printf(" O item %d não foi encontrado.\n", valor);
                else
                    printf("\n O item %d foi encontrado.", arvore->chave);

                break;
            case '3' :
                desenharArvore((struct no *) arvore);
                //mostrarArvore(arvore);
                break;
            case '4':
                printf("\n Árvore Red: ");
                mostrarArvoreRED(arvore);

                printf("\n Árvore eRd: ");
                mostrarArvoreERD(arvore);

                printf("\n Árvore edR: ");
                mostrarArvoreEDR(arvore);

                printf("\n Árvore bfs: ");
                mostrarArvoreBFS(arvore);

                break;
            case '5':
                mostrarPrimeiro(arvore);
                mostrarUltimo(arvore);

                printf("\n A altura da árvore é %d ", obterAltura(arvore));

                printf("\n O número de folhas da árvore é %d ", contarFolhas(arvore));

                printf("\n O número de nós da árvore é %d \n", contarNos(arvore));

                break;
//            case '6':
//                printf("\n Digite o item a sofrer rotação para a direita: ");
//                scanf("%d", &valor);
//                arvore = buscarItemRecursivo(arvore, valor);
//                arvore = rodarDireita(arvore);
//
//                break;
//            case '7':
//                printf("\n Digite o item a sofrer rotação para a esquerda: ");
//                scanf("%d", &valor);
//                arvore = buscarItemRecursivo(arvore, valor);
//                arvore = rodarEsquerda(arvore);
//                break;
//            case '8':
//                printf("\n Digite o item a sofrer rotação dupla direita: ");
//                scanf("%d", &valor);
//                arvore = buscarItemRecursivo(arvore, valor);
//                arvore = rodarDuplaDireita(arvore);
//                break;
//            case '9':
//                printf("\n Digite o item a sofrer rotação dupla esquerda: ");
//                scanf("%d", &valor);
//                arvore = buscarItemRecursivo(arvore, valor);
//                arvore = rodarDuplaEsquerda(arvore);
                break;
            case '6':
                printf("\n Digite o item a ser encontrado: ");
                scanf("%d", &valor);
                No *no = criarNoVazio(valor);

                No *ant = obterAnterior(arvore, no);
                if (ant != NULL)
                    printf(" O nó sucessor é %d. \n", ant->chave);
                else
                    printf("\n Não existe sucessor. \n");

                No *suc = obterSucessor(arvore, no);
                if (ant != NULL)
                    printf(" O nó anterior é %d.\n", suc->chave);
                else
                    printf("\n Não existe anterior. \n");

                break;
            case 'q':
                printf("\n Finalizando! :)\n");
                exit(0);
            default :
                printf("\n Nenhuma opção encontrada!\n");

        }
    }
}

Arvore criarArvoreVazia( ){
    Arvore ap;
    ap = NULL;
    return ap;
}

No * criarNoVazio(int valor){
    No *novo = malloc(sizeof(No));
    novo->chave = valor;
    return novo;
}

Arvore inserirElemento(Arvore ap, int valor){
    if(ap == NULL){
        return criarNoVazio(valor);
    }
    else if (ap->chave < valor)
        ap->dir = inserirElemento(ap->dir, valor);
    else if (ap->chave > valor)
        ap->esq = inserirElemento(ap->esq, valor);

    return ap;
}

Arvore buscarItem(Arvore ap, int valor){
    if(ap == NULL){
        return NULL;
    }

    while(ap->chave != valor){
        if(ap != NULL) {
            if(ap->chave > valor){
                ap = ap->esq;
            }
            else if(ap->chave < valor){
                ap = ap->dir;
            }
            else{
                return NULL;
            }
        }
    }
    return ap;
}

No * buscarItemRecursivo(Arvore ap, int valor){
    No *p;

    if(ap == NULL)
        p = NULL;
    else if(ap->chave == valor)
        p = ap;
    else{
        p = buscarItemRecursivo(ap->esq, valor);
        if(p == NULL)
            p = buscarItemRecursivo(ap->dir, valor);
    }
    return p;
}

No * obterAncestral(Arvore ap, No* p, No* q){
    No *anc, *c;
    bool fim;
    int a, b;
    anc = NULL;

    if(ap != NULL){
        if((p != NULL) && (q != NULL)){
            a = p->chave;
            b = q->chave;
            if((a != ap->chave) && (b != ap->chave)){
                c = ap;
                fim = FALSE;
                do {
                    if ((a < c->chave) && (b < c->chave)) {
                        anc = c;
                        c = c->esq;
                    }
                    else if ((a > c->chave) && (b > c->chave)) {
                        anc = c;
                        c = c->dir;
                    } else {
                        fim = TRUE;
                        if ((a != c->chave) && (b != c->chave)) {
                            anc = c;
                        }
                    }
                } while(fim == FALSE);
            }
        }
    }
    return anc;
}

No * obterAncestralR(Arvore ap, No* p, No* q){
    No *anc, *e, *d;
    int a, b;

    if((ap == NULL) || (p == NULL) || (q == NULL)){
        anc = NULL;
    } else {
        a = p->chave;
        b = q->chave;
        if((a == ap->chave) || (b == ap->chave)){
            anc = NULL;
        } else {
            e = ap->esq;
            d = ap->dir;
            if((a == e->chave) || (a == d->chave)){
                anc = ap;
            } else{
                if((b == e->chave) || (b == d->chave)){
                    anc = ap;
                } else {
                    anc = ap;
                    if((a < ap->chave) && (b < ap->chave)){
                        anc = obterAncestralR(ap->esq, p, q);
                    } else{
                        if((a > ap->chave) && (b > ap->chave)){
                            anc = obterAncestralR(ap->dir, p, q);
                        }
                    }
                }
            }
        }
    }
    return anc;
}

No * minValor(No * n){
    No *atual = n;

    while (atual->esq != NULL) {
        atual = atual->esq;
    }
    return atual;
}

No * maxValor(No* n){
    No *atual = n;

    while(atual->dir != NULL){
        atual = atual->dir;
    }

    return atual;
}

No * obterSucessor(Arvore ap, No* n){
    No *sucessor = NULL;

    if (n->dir != NULL)
        return minValor(n->dir);

    while (ap != NULL) {
        if (n->chave < ap->chave) {
            sucessor = ap;
            ap = ap->esq;
        }
        else if (n->chave > ap->chave)
            ap = ap->dir;
        else
            break;
    }
    return sucessor;
}

No * obterAnterior(Arvore ap, No* n){
    No *anterior = NULL;

    if(n->esq != NULL) {
        return maxValor(n->esq);
    }

    while (ap != NULL){
        if (n->chave == ap->chave){
            break;
        } else if (n->chave < ap->chave){
            ap = ap->esq;
        } else if (n->chave > ap->chave){
            anterior = ap;
            ap = ap->dir;
        }
    }
    return anterior;
}

No* rodarDireita(No* p){
    No *y, *re;
    re = p;
    if (p != NULL){
        y = p->esq;
        if (y != NULL){
            p->esq = y->dir;
            y->dir = p;
            re = y;
        }
    }
    return re;
}

No* rodarEsquerda(No* p){
    No *y, *re;
    re = p;
    if (p != NULL){
        y = p->dir;
        if (y != NULL){
            p->dir = y->esq;
            y->esq = p;
            re = y;
        }
    }
    return re;
}

No* rodarDuplaDireita(No* p){
    No *y, *z, *re;
    re = p;
    if (p != NULL){
        y = p->esq;
        if ((y != NULL) && (y->dir != NULL)){
            z = y->dir;
            y->dir = z->esq;
            p->esq = z->dir;
            z->esq = y;
            z->dir = p;
            re = z;
        }
    }
    return re;
}

No* rodarDuplaEsquerda(No* p){
    No *y, *z, *re;
    re = p;
    if (p != NULL){
        y = p->dir;
        if ((y != NULL) && (y->esq != NULL)){
            z = y->esq;
            y->esq = z->dir;
            p->dir = z->esq;
            z->esq = p;
            z->dir = y;
            re = z;
        }
    }
    return re;
}

int contarNos(Arvore ap) {
    int c = 1;

    if (ap != NULL) {
        c += contarNos(ap->esq);
        c += contarNos(ap->dir);
        return c;
    }
    else
        return 0;
}

int contarFolhas(Arvore ap){
    if(ap == NULL)
        return 0;
    else if(ap->esq == NULL && ap->dir == NULL)
        return 1;
    else
        return 1 + contarFolhas(ap->esq) + contarFolhas(ap->dir);
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
        printf(" %d  ",ap->chave);
}

void mostrarArvore(Arvore ap){
    Pilha s;
    No *p;
    bool fim;
    if(ap!= NULL){
        criarPilhaVazia(&s);
        fim = FALSE;
        p = ap;
        do {
            while(p != NULL) {
                pushPilha(&s,p);
                p = p->esq;
            }
            if(verificarPilhaVazia(&s)==FALSE){
                p = acessarTopo(&s);
                printf("\n %d \n",p->chave);
                popPilha(&s);
                p = p->dir;
            } else
                fim = TRUE;
        } while(fim == FALSE);
    }
    else
        printf("\n arvore vazia \n");
}

void mostrarArvoreERD(Arvore ap){
    if (ap != NULL){
        mostrarArvoreERD(ap->esq);
        mostrarRaiz(ap);
        mostrarArvoreERD(ap->dir);
    }
}

void mostrarArvoreRED(Arvore ap){
    if (ap != NULL){
        mostrarRaiz(ap);
        mostrarArvoreRED(ap->esq);
        mostrarArvoreRED(ap->dir);}
}

void mostrarArvoreEDR(Arvore ap){
    if (ap != NULL){
        mostrarArvoreEDR(ap->esq);
        mostrarArvoreEDR(ap->dir);
        mostrarRaiz(ap);
    }
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

void mostrarPrimeiro(Arvore ap){
    No *p;

    if(ap== NULL)
        printf("\n Árvore vazia.");
    else{
        p = ap;

        while(p->esq != NULL)
            p = p->esq;
        printf("\n O primeiro nó visitado é %d", p->chave);
    }
}

void mostrarUltimo(Arvore ap){
    No *p;

    if(ap == NULL)
        printf("\n Árvore vazia.");
    else{
        p = ap;

        while(p->dir != NULL)
            p = p->dir;
        printf("\n O último nó visitado é %d", p->chave);
    }
}

