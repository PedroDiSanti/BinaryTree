/* Pilha de pointer */
#include "Booleano.h"

#define Max 20
typedef struct {
    void * apont;
    int item;
}Casa;

typedef struct {
    int topo;
    Casa tabela[Max];
} Pilha;

//protótipos
void criarPilhaVazia(Pilha *);
void *acessarTopo(Pilha *);
bool verificarPilhaVazia(Pilha *);
bool verificarPilhaCheia(Pilha *);
void pushPilha(Pilha *, void *);
void popPilha(Pilha *);

// implementações
void criarPilhaVazia(Pilha *a){
    a->topo = 0;
}

void *acessarTopo(Pilha *a){
    int k;
    void *t;
    if (a->topo != 0){
        k = a->topo - 1;
        t = a->tabela[k].apont;
    }else
        t = NULL;
    return t;
}

bool verificarPilhaVazia(Pilha *a){
    int vazia;
    if (a->topo == 0) vazia = TRUE; else vazia = FALSE;
    return vazia;
}

bool verificarPilhaCheia(Pilha *a){
    int cheia;
    if (a->topo == Max) cheia = TRUE; else cheia = FALSE;
    return cheia;
}

void pushPilha(Pilha *a, void *novo){
    int k;
    k = a->topo;
    if (a->topo < Max) {
        a->tabela[k].item = 0;	a->tabela[k].apont = novo;
        a->topo = k + 1;
    }
}

void popPilha(Pilha *a){
    int k;
    k = a->topo;
    if (a->topo != 0){
        a->topo = k-1;
    }
}

