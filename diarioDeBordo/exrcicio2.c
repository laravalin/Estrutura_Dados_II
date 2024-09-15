// Lara Mendes Valin

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//estrutura de um nó da árvore AVL
typedef struct No {
    int chave;           
    struct No *esq;      
    struct No *dir;      
    int altura;          
} No;

// retorna o maior entre dois valores inteiros
int max(int a, int b) {
    return (a > b) ? a : b;
}

// retorna a altura de um nó, se for NULL, retorna -1 (indicando ausência do nó)
int altura(No *no) {
    if (no == NULL) {
        return -1;
    } else {
        return no->altura;
    }
}

// cálculo do fator de balanceamento de um nó
int balanceamento(No *no) {
    if (no == NULL) {
        return 0;
    } else {
        return altura(no->esq) - altura(no->dir);
    }
}

// inicializa o nó sem filhos e altura 0
No *novoNo(int chave) {
    No *novo = (No *)malloc(sizeof(No));
    novo->chave = chave;
    novo->esq = NULL;
    novo->dir = NULL;
    novo->altura = 0;
    return novo;
}

// raliza rotação à direita
No *rotacaoDireita(No *y) {
    No *x = y->esq;      
    No *T2 = x->dir;     

    // realiza a rotação
    x->dir = y;
    y->esq = T2;

    // atualiza as alturas dos nós
    y->altura = max(altura(y->esq), altura(y->dir)) + 1;
    x->altura = max(altura(x->esq), altura(x->dir)) + 1;

    return x;
}

// realiza rotação à esquerda
No *rotacaoEsquerda(No *x) {
    No *y = x->dir;      
    No *T2 = y->esq;     

    // realiza a rotação
    y->esq = x;
    x->dir = T2;

    // atualiza as alturas dos nós
    x->altura = max(altura(x->esq), altura(x->dir)) + 1;
    y->altura = max(altura(y->esq), altura(y->dir)) + 1;

    return y;
}

// insere um novo nó na árvore 
No *inserir(No *raiz, int chave) {
    if (raiz == NULL)
        return novoNo(chave);

    if (chave < raiz->chave)
        raiz->esq = inserir(raiz->esq, chave);
    else if (chave > raiz->chave)
        raiz->dir = inserir(raiz->dir, chave);
    else
        return raiz;  

    raiz->altura = max(altura(raiz->esq), altura(raiz->dir)) + 1;

    // calcula o fator de balanceamento
    int balance = balanceamento(raiz);

    // desbalanceamento à esquerda (Rotação simples à direita)
    if (balance > 1 && chave < raiz->esq->chave)
        return rotacaoDireita(raiz);

    // desbalanceamento à direita (Rotação simples à esquerda)
    if (balance < -1 && chave > raiz->dir->chave)
        return rotacaoEsquerda(raiz);

    // desbalanceamento esquerda-direita (Rotação dupla esquerda-direita)
    if (balance > 1 && chave > raiz->esq->chave) {
        raiz->esq = rotacaoEsquerda(raiz->esq);
        return rotacaoDireita(raiz);
    }

    // desbalanceamento direita-esquerda (Rotação dupla direita-esquerda)
    if (balance < -1 && chave < raiz->dir->chave) {
        raiz->dir = rotacaoDireita(raiz->dir);
        return rotacaoEsquerda(raiz);
    }

    return raiz;
}

// imprime árvore
void emOrdem(No *raiz) {
    if (raiz != NULL) {
        emOrdem(raiz->esq);
        printf("%d ", raiz->chave);  
        emOrdem(raiz->dir);
    }
}

int main() {
    No *raiz = NULL; 
  
    // insere elementos na árvore
    raiz = inserir(raiz, 10);
    raiz = inserir(raiz, 20);
    raiz = inserir(raiz, 30);
    raiz = inserir(raiz, 40);
    raiz = inserir(raiz, 50);
    raiz = inserir(raiz, 25);

    // imprime árvore
    printf("Árvore AVL:\n");
    emOrdem(raiz);

    return 0;
}
