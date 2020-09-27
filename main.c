/*
  Arquivo: main.c
  Autor: Pedro Di Santi
  Data: 20/08/2020 18:39
  Última atualização: 27/09/2020 13:00
  Descrição:
    Este programa tem como finalidade explorar a manipulação de uma Árvore Binária. Ela implementa a criação de uma nova
        árvore, onde novos elementos podem ser inseridos, pesquisados, etc. Além dessas funções básicas, podemos
        trabalhar rotações direita e dupla direita, esquerda e dupla esquerda.
    Podemos mostrá-la utilizando uma maneira não recursiva utilizando de pilha no encaminhamento eRd.
    Por fim, podemos encontrar a altura da árvore inserida, o primeiro e último elemento.
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

typedef No* ArvoreBB;

No * criarNoVazio(int);
No * obterAncestral(ArvoreBB, No*, No*);
No * obterAncestralR(ArvoreBB, No*, No*);
No * buscarABB(ArvoreBB, int);
ArvoreBB criarArvoreVazia();
ArvoreBB inserirNo(ArvoreBB, No*);
ArvoreBB inserir(ArvoreBB, int);
void mostrarArvore(ArvoreBB);
void mostrarPrimeiro(ArvoreBB);
void mostrarUltimo(ArvoreBB);
int obterAltura(ArvoreBB);
No * obterSucessor(ArvoreBB, No*);
No * obterAnterior(ArvoreBB ap, No* n);

int main() {
    int valor;
    char ch = 'i';

    ArvoreBB arvore = criarArvoreVazia();

    printf("\n"
           "______________MENU_______________"
           "\n "
           "(1) - Inserir item na árvore \n "
           "(2) - Mostrar árvore \n "
           "(3) - Mostrar ancestral \n "
           "(4) - Obter sucessor \n "
           "(Q) - Sair\n"
           "__________________________________"
    );

    while(ch != 'q'){
        printf("\n COMANDO: ");
        scanf(" %c",&ch);

        switch(ch){
            case '1' :
                printf("\n Digite o item a ser inserido: ");
                scanf("%d", &valor);
                No *novo = criarNoVazio(valor);
                arvore = inserirNo(arvore, novo);
                break;
            case '2' :
                mostrarArvore(arvore);
                break;
            case '3' :
                printf("\n Digite o primeiro nó: ");
                scanf("%d", &valor);
                No *noP = criarNoVazio(valor);
                printf("\n Digite o segundo nó: ");
                scanf("%d", &valor);
                No *noQ = criarNoVazio(valor);
                No *anc = obterAncestral(arvore, noP, noQ);
                printf(" (Não Recursivo) O nó ancestral é %d.\n", anc->chave);
                No *ancR = obterAncestralR(arvore, noP, noQ);
                printf(" (Recursivo) O nó ancestral é %d.\n", ancR->chave);
                break;
            case '4' :
                printf("\n Digite o nó: ");
                scanf("%d", &valor);
                No *no = criarNoVazio(valor);
                No *suc = obterSucessor(arvore, no);
                printf(" O nó sucessor é %d.\n", suc->chave);
                break;
            case '5' :
                printf("\n Digite o nó: ");
                scanf("%d", &valor);
                No *noAnt = criarNoVazio(valor);
                No *ant = obterAnterior(arvore, noAnt);
                printf(" O nó anterior é %d.\n", ant->chave);
                break;
            case 'q':
                printf("\n !Finalizando! :)\n");
                exit(0);
            default :
                printf("\n Nenhuma opção encontrada.\n");
        }
    }
}

No * criarNoVazio(int valor){
    No *novo = malloc(sizeof(No));
    novo->chave = valor;
    return novo;
}

No* obterAncestral(ArvoreBB ap, No* p, No* q){
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

No* obterAncestralR(ArvoreBB ap, No* p, No* q){
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

No* buscarABB(ArvoreBB ap, int valor){
    No *p;

    if(ap == NULL)
        p = NULL;
    else if(ap->chave == valor)
        p = ap;
    else{
        p = buscarABB(ap->esq, valor);
        if(p == NULL)
            p = buscarABB(ap->dir, valor);
    }
    return p;
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

No * obterSucessor(ArvoreBB ap, No* n){
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

No * obterAnterior(ArvoreBB ap, No* n){
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

ArvoreBB criarArvoreVazia( ){
    ArvoreBB ap;
    ap = NULL;
    return ap;
}

ArvoreBB inserirNo(ArvoreBB ap, No* novo){
    int y;
    No *p, *ant;

    novo->esq = NULL;
    novo->dir = NULL;

    if (ap == NULL) {
        novo->pai = NULL;
        ap = novo;
    } else {
        p = ap;
        y = novo->chave;

        while (p != NULL) {
            ant = p;
            if (y < p->chave)
                p = p->esq;
            else
                p = p->dir;
        }

        if (y < ant->chave)
            ant->esq = novo;
        else
            ant->dir = novo;

        novo->pai = ant;
    }

    return ap;
}

ArvoreBB inserir(ArvoreBB ap, int valor){
    if(ap == NULL)
        return criarNoVazio(valor);
    else if (ap->chave < valor)
        ap->dir = inserir(ap->dir, valor);
    else if (ap->chave > valor)
        ap->esq = inserir(ap->esq, valor);

    return ap;
}

void mostrarArvore(ArvoreBB ap){
    No *p;
    Pilha s;
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
                printf("%d ",p->chave);
                popPilha(&s);
                p = p->dir;
            } else
                fim = TRUE;
        } while(fim == FALSE);
    }
    else
        printf("\n Árvore vazia \n");
}

void mostrarPrimeiro(ArvoreBB ap){
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

void mostrarUltimo(ArvoreBB ap){
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

int obterAltura(ArvoreBB ap){
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

