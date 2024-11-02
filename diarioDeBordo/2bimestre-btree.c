//Lara Mendes Valin

#include <stdio.h>
#include <stdlib.h>

#define ORDEM 3  // ordem da b-tree (máximo de filhos por nó)

// estrutura de um nó da b-tree
typedef struct No {
    int chaves[ORDEM - 1];  
    struct No* filhos[ORDEM];
    int numChaves;
    int folha; 
} No;

// cria um novo nó
No* criarNo(int folha) {
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->numChaves = 0;
    novoNo->folha = folha;
    return novoNo;
}

// divide um nó
void dividirNo(No* pai, int indice, No* filho) {
    No* novoNo = criarNo(filho->folha);
    novoNo->numChaves = ORDEM / 2 - 1;

    for (int i = 0; i < ORDEM / 2 - 1; i++) {
        novoNo->chaves[i] = filho->chaves[i + ORDEM / 2];
    }

    if (!filho->folha) {
        for (int i = 0; i < ORDEM / 2; i++) {
            novoNo->filhos[i] = filho->filhos[i + ORDEM / 2];
        }
    }

    filho->numChaves = ORDEM / 2 - 1;

    for (int i = pai->numChaves; i >= indice + 1; i--) {
        pai->filhos[i + 1] = pai->filhos[i];
    }
    pai->filhos[indice + 1] = novoNo;

    for (int i = pai->numChaves - 1; i >= indice; i--) {
        pai->chaves[i + 1] = pai->chaves[i];
    }
    pai->chaves[indice] = filho->chaves[ORDEM / 2 - 1];
    pai->numChaves++;
}

// auxilia inserção de uma chave em um nó não cheio
void inserirNoNaoCheio(No* no, int chave) {
    int i = no->numChaves - 1;

    if (no->folha) {
        while (i >= 0 && chave < no->chaves[i]) {
            no->chaves[i + 1] = no->chaves[i];
            i--;
        }
        no->chaves[i + 1] = chave;
        no->numChaves++;
    } else {
        while (i >= 0 && chave < no->chaves[i]) {
            i--;
        }
        i++;
        if (no->filhos[i]->numChaves == ORDEM - 1) {
            dividirNo(no, i, no->filhos[i]);
            if (chave > no->chaves[i]) {
                i++;
            }
        }
        inserirNoNaoCheio(no->filhos[i], chave);
    }
}

// insere uma chave na b-tree
void inserir(No** raiz, int chave) {
    No* r = *raiz;
    if (r->numChaves == ORDEM - 1) {
        No* novoNo = criarNo(0);
        *raiz = novoNo;
        novoNo->filhos[0] = r;
        dividirNo(novoNo, 0, r);
        inserirNoNaoCheio(novoNo, chave);
    } else {
        inserirNoNaoCheio(r, chave);
    }
}

// imprime a b-tree em ordem
void imprimirBTree(No* no) {
    int i;
    for (i = 0; i < no->numChaves; i++) {
        if (!no->folha) {
            imprimirBTree(no->filhos[i]);
        }
        printf("%d ", no->chaves[i]);
    }
    if (!no->folha) {
        imprimirBTree(no->filhos[i]);
    }
}

// imprime a b-tree de forma hierárquica
void imprimirHierarquicamente(No* no, int nivel) {
    if (no == NULL) {
        return;
    }

    // imprimir os filhos
    for (int i = 0; i < no->numChaves; i++) {
        if (!no->folha) {
            imprimirHierarquicamente(no->filhos[i], nivel + 1);
        }
        // indentação para mostrar o nível da árvore
        for (int j = 0; j < nivel; j++) {
            printf("   ");
        }
        printf("%d\n", no->chaves[i]);
    }
    
    // imprimir o último filho se não for uma folha
    if (!no->folha) {
        imprimirHierarquicamente(no->filhos[no->numChaves], nivel + 1);
    }
}

// função principal
int main() {
    No* raiz = criarNo(1); // cria a raiz como uma folha
    int chaves[] = {15, 25, 3, 8, 11, 35, 9, 18};
    int n = sizeof(chaves) / sizeof(chaves[0]);

    for (int i = 0; i < n; i++) {
        inserir(&raiz, chaves[i]);
    }

    printf("elementos da b-tree em ordem:\n");
    imprimirBTree(raiz);
    printf("\n");

    printf("estrutura da b-tree:\n");
    imprimirHierarquicamente(raiz, 0);

    return 0;
}
