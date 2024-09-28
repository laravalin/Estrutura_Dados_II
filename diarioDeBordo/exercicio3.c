//Lara Mendes Valin

#include <stdio.h>
#include <stdlib.h>

#define VERMELHO 0
#define PRETO 1

typedef struct no {
    int chave;
    int cor;
    struct no *esquerda, *direita, *pai;
} No;

No *raiz = NULL;

No *criarNo(int chave) {
    No *novoNo = (No*)malloc(sizeof(No));
    novoNo->chave = chave;
    novoNo->cor = VERMELHO;
    novoNo->esquerda = novoNo->direita = novoNo->pai = NULL;
    return novoNo;
}

void rotacionaEsquerda(No *x) {
    No *y = x->direita;
    x->direita = y->esquerda;
    if (y->esquerda != NULL) y->esquerda->pai = x;
    y->pai = x->pai;
    if (x->pai == NULL) raiz = y;
    else if (x == x->pai->esquerda) x->pai->esquerda = y;
    else x->pai->direita = y;
    y->esquerda = x;
    x->pai = y;
}

void rotacionaDireita(No *x) {
    No *y = x->esquerda;
    x->esquerda = y->direita;
    if (y->direita != NULL) y->direita->pai = x;
    y->pai = x->pai;
    if (x->pai == NULL) raiz = y;
    else if (x == x->pai->direita) x->pai->direita = y;
    else x->pai->esquerda = y;
    y->direita = x;
    x->pai = y;
}

void correcao(No *novoNo) {
    No *pai = NULL;
    No *avo = NULL;

    while ((novoNo != raiz) && (novoNo->cor == VERMELHO) && (novoNo->pai->cor == VERMELHO)) {
        pai = novoNo->pai;
        avo = pai->pai;

        // o pai é filho à esquerda do avô
        if (pai == avo->esquerda) {
            No *tio = avo->direita;
            //o tio é VERMELHO
            if (tio != NULL && tio->cor == VERMELHO) {
                avo->cor = VERMELHO;
                pai->cor = PRETO;
                tio->cor = PRETO;
                novoNo = avo;
            } else {
                // o novo nóo é filho à direita
                if (novoNo == pai->direita) {
                    rotacionaEsquerda(pai);
                    novoNo = pai;
                    pai = novoNo->pai;
                }
                // o novo nó é filho à esquerda
                rotacionaDireita(avo);
                int temp = pai->cor;
                pai->cor = avo->cor;
                avo->cor = temp;
                novoNo = pai;
            }
        } else { //o pai é filho à direita do avô
            No *tio = avo->esquerda;
            // o tio é VERMELHO
            if (tio != NULL && tio->cor == VERMELHO) {
                avo->cor = VERMELHO;
                pai->cor = PRETO;
                tio->cor = PRETO;
                novoNo = avo;
            } else {
                // o novo nó é filho à esquerda
                if (novoNo == pai->esquerda) {
                    rotacionaDireita(pai);
                    novoNo = pai;
                    pai = novoNo->pai;
                }
                // o novo nó é filho à direita
                rotacionaEsquerda(avo);
                int temp = pai->cor;
                pai->cor = avo->cor;
                avo->cor = temp;
                novoNo = pai;
            }
        }
    }
    raiz->cor = PRETO; // raiz preta
}

void inserir(int chave) {
    No *novoNo = criarNo(chave);
    if (raiz == NULL) {
        novoNo->cor = PRETO; 
        raiz = novoNo;
        return;
    }

    No *pai = NULL;
    No *atual = raiz;

    // encontra posição  para o novo nó
    while (atual != NULL) {
        pai = atual;
        if (novoNo->chave < atual->chave) {
            atual = atual->esquerda;
        } else {
            atual = atual->direita;
        }
    }

    novoNo->pai = pai;
    if (novoNo->chave < pai->chave) {
        pai->esquerda = novoNo;
    } else {
        pai->direita = novoNo;
    }

    correcao(novoNo);
}

void imprimirArvore(No *raiz, int espaco) {
    if (raiz == NULL) return;
    espaco += 10;
  
    imprimirArvore(raiz->direita, espaco);

    printf("\n");
    for (int i = 10; i < espaco; i++) printf(" ");
    printf("%d(%s)\n", raiz->chave, raiz->cor == VERMELHO ? "VERMELHO" : "PRETO");

    imprimirArvore(raiz->esquerda, espaco);
}

int main() {
    inserir(40);
    inserir(20);
    inserir(60);
    inserir(10);
    inserir(30);
    inserir(50);
    inserir(70);
    inserir(80);
    inserir(90);
    inserir(22);

    printf("Árvore Rubro-Negra:\n");
    printf("Raiz:\n"); // para indicar a raiz 
    imprimirArvore(raiz, 0);
    return 0;
}
