#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


struct no{
    int elemento;
    struct no * esq;
    struct no * dir;

}*raiz;

int altura(struct no *tree);
void escrever(int rel , int pos, struct no* raiz , char* lado , int nivel);
void desenharArvore(struct no *raiz);

int **A;

void desenharArvore(struct no *raiz){
    A=NULL;

    int i,j;

    int h= altura(raiz);
    int nn =pow(2,h + 1) - 1;

    A = (int **)malloc((h+1+1)*sizeof(int *));
    for(int i = 1;i <= h + 1; i++)
        A[i] = (int *)malloc((nn + 1)*sizeof(int));

    for(i = 1; i <= h + 1; i++)
        for(j = 1;j <= nn; j++)
            A[i][j] = 0;

    escrever(nn + 1, (nn + 1) / 2, raiz, "esq", 1);

    for(i = 1; i <= h + 1; i++){
        for(j = 1; j <= nn; j++){
            if(A[i][j]!=0)
                printf("%d",A[i][j]);
            else
                printf(" ");
        }
        printf("\n\n\n");
    }

    free(A);
}

void escrever(int rel , int pos, struct no *raiz , char *lado , int nivel){
    if(raiz == NULL)
        return;

    if(strcmp(lado, "esq") == 0){
        A[nivel][rel - pos] = raiz->elemento;

        escrever(rel - pos, pos / 2, raiz->esq, "esq", nivel + 1);
        escrever(rel - pos, pos / 2, raiz->dir, "dir", nivel + 1);
    }
    else{
        A[nivel][rel + pos] = raiz->elemento;
        escrever(rel + pos, pos / 2, raiz->esq, "esq", nivel + 1);
        escrever(rel + pos, pos / 2, raiz->dir, "dir", nivel + 1);
    }
}

int altura(struct no *tree){
    if(tree){
        int tamanhoEsq= altura(tree->esq);
        int tamanhoDir= altura(tree->dir);
        if(tamanhoEsq > tamanhoDir)
            return tamanhoEsq + 1;
        else
            return tamanhoDir + 1;
    }

    return -1;
}