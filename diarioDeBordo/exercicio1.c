//Lara Mendes Valin

#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int valor;              
    struct No* esquerda;   
    struct No* direita;    
} No;

// cria novo nó
No* criarNo(int valor) {
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->valor = valor;
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    return novoNo;
}

// insere um valor
No* inserir(No* raiz, int valor) {
    if (raiz == NULL) {
        return criarNo(valor);
    }

    if (valor < raiz->valor) {
        raiz->esquerda = inserir(raiz->esquerda, valor);
    } else if (valor > raiz->valor) {
        raiz->direita = inserir(raiz->direita, valor);
    }
    return raiz;
}

// busca um valor
No* buscar(No* raiz, int valor) {
    if (raiz == NULL || raiz->valor == valor) {
        return raiz;
    }

    if (valor < raiz->valor) {
        return buscar(raiz->esquerda, valor);
    }
    return buscar(raiz->direita, valor);
}

// encontra o nó com o menor valor
No* encontraMenor(No* raiz) {
    while (raiz->esquerda != NULL) {
        raiz = raiz->esquerda;
    }
    return raiz;
}

// exclui um valor da árvore 
No* excluir(No* raiz, int valor) {
    if (raiz == NULL) {
        return raiz;
    }

    if (valor < raiz->valor) {
        raiz->esquerda = excluir(raiz->esquerda, valor);
    } else if (valor > raiz->valor) {
        raiz->direita = excluir(raiz->direita, valor);
    } else {
        if (raiz->esquerda == NULL) {
            No* temp = raiz->direita;
            free(raiz);
            return temp;
        } else if (raiz->direita == NULL) {
            No* temp = raiz->esquerda;
            free(raiz);
            return temp;
        }
        No* temp = encontraMenor(raiz->direita);
        raiz->valor = temp->valor;
        raiz->direita = excluir(raiz->direita, temp->valor);
    }
    return raiz;
}

// liberar memória
void liberarArvore(No* raiz) {
    if (raiz != NULL) {
        liberarArvore(raiz->esquerda);
        liberarArvore(raiz->direita);
        free(raiz);
    }
}

// imprime a árvore 
void imprimirArvore(No* raiz, int nivel) {
    if (raiz != NULL) {
        imprimirArvore(raiz->direita, nivel + 1);
        for (int i = 0; i < nivel; i++) {
            printf("    ");
        }
        printf("%d\n", raiz->valor);
        imprimirArvore(raiz->esquerda, nivel + 1);
    }
}

int main() {
    No* raiz = NULL; // inicializa a arvore vazia

    // insere valores
    raiz = inserir(raiz, 17);
    raiz = inserir(raiz, 32);
    raiz = inserir(raiz, 21);
    raiz = inserir(raiz, 45);
    raiz = inserir(raiz, 12);
    raiz = inserir(raiz, 28);
    raiz = inserir(raiz, 38);
    raiz = inserir(raiz, 50);

    printf("Árvore binária antes da exclusão:\n");
        imprimirArvore(raiz, 0);
    
        // busca um valor na árvore
        No* buscado = buscar(raiz, 50);
        if (buscado) {
            printf("Valor buscado: %d\n", buscado->valor);
        } else {
            printf("Valor não encontrado.\n");
        }
    
        // exclui um Valor
        raiz = excluir(raiz, 28);
        printf("Valor 28 excluído.\n");
    
        // imprime após a exclusão
        printf("arvore após a exclusão:\n");
        imprimirArvore(raiz, 0);
    
        // libera memória
        liberarArvore(raiz);
    
        return 0;
    }
