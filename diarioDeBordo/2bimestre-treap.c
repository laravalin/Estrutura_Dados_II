//Lara Mendes Valin

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// estrutura do nó da Treap
typedef struct NoTreap {
    int chave;
    int prioridade;
    struct NoTreap* esquerdo;
    struct NoTreap* direito;
} NoTreap;

// função para criar um novo nó
NoTreap* criarNo(int chave) {
    NoTreap* novoNo = (NoTreap*)malloc(sizeof(NoTreap));
    novoNo->chave = chave;
    novoNo->prioridade = rand() % 100;  
    novoNo->esquerdo = NULL;
    novoNo->direito = NULL;
    return novoNo;
}

// função para rotacionar o nó para a direita
NoTreap* rotacionarDireita(NoTreap* no) {
    NoTreap* novoNo = no->esquerdo;
    no->esquerdo = novoNo->direito;
    novoNo->direito = no;
    return novoNo;
}

// função para rotacionar o nó para a esquerda
NoTreap* rotacionarEsquerda(NoTreap* no) {
    NoTreap* novoNo = no->direito;
    no->direito = novoNo->esquerdo;
    novoNo->esquerdo = no;
    return novoNo;
}

// função para inserir um novo nó na Treap
NoTreap* inserir(NoTreap* no, int chave) {
    if (no == NULL) {
        return criarNo(chave);
    }

    if (chave < no->chave) {
        no->esquerdo = inserir(no->esquerdo, chave);
        if (no->esquerdo->prioridade > no->prioridade) {
            no = rotacionarDireita(no);
        }
    } else {
        no->direito = inserir(no->direito, chave);
        if (no->direito->prioridade > no->prioridade) {
            no = rotacionarEsquerda(no);
        }
    }

    return no;
}

// função para remover um nó da Treap
NoTreap* remover(NoTreap* no, int chave) {
    if (no == NULL) {
        return NULL;
    }

    if (chave < no->chave) {
        no->esquerdo = remover(no->esquerdo, chave);
    } else if (chave > no->chave) {
        no->direito = remover(no->direito, chave);
    } else {
        if (no->esquerdo == NULL) {
            NoTreap* temp = no->direito;
            free(no);
            return temp;
        } else if (no->direito == NULL) {
            NoTreap* temp = no->esquerdo;
            free(no);
            return temp;
        }

        if (no->esquerdo->prioridade > no->direito->prioridade) {
            no = rotacionarDireita(no);
            no->direito = remover(no->direito, chave);
        } else {
            no = rotacionarEsquerda(no);
            no->esquerdo = remover(no->esquerdo, chave);
        }
    }

    return no;
}

// função para percorrer a Treap em ordem crescente
void inorder(NoTreap* no) {
    if (no != NULL) {
        inorder(no->esquerdo);
        printf("%d ", no->chave);
        inorder(no->direito);
    }
}

int main() {
    srand(time(NULL));  // inicializar no de número aleatório
    NoTreap* treap = NULL;

    // chaves a serem inseridas na Treap
    int chaves[] = {50, 30, 20, 40, 70, 60, 80};
    int n = sizeof(chaves) / sizeof(chaves[0]);

    // inserir chaves na Treap
    for (int i = 0; i < n; i++) {
        treap = inserir(treap, chaves[i]);
    }

    printf("Elementos da Treap em ordem:\n");
    inorder(treap);
    printf("\n");

    // remover chave 50 e imprimir novamente
    treap = remover(treap, 50);
    printf("Elementos da Treap em ordem após remover 50:\n");
    inorder(treap);
    printf("\n");

    return 0;
}

