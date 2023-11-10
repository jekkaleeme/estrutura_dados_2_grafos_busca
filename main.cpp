#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct adjacente {
    int vertice;
    struct adjacente* prox;
} ADJACENTE;

typedef struct vertice {
    ADJACENTE* c_;
} VERTICE;

typedef struct grafo {
    int vertices;
    int arestas;
    VERTICE* v_adjacente;
} GRAFO;

GRAFO* novo_grafo(int v) {
    int i;
    GRAFO* g = (GRAFO*)malloc(sizeof(GRAFO));
    g->vertices = v;
    g->arestas = 0;
    g->v_adjacente = (VERTICE*)malloc(v * sizeof(VERTICE));

    for (i = 0; i < v; i++) {
        g->v_adjacente[i].c_ = NULL;
    }
    return g;
}

ADJACENTE* criaAdj(int v) {
    ADJACENTE* t = (ADJACENTE*)malloc(sizeof(ADJACENTE));
    t->vertice = v;
    t->prox = NULL;
    return t;
}

void nova_aresta(GRAFO* gr, int vi, int vf) {
    if (!gr) return;
    ADJACENTE* novo = criaAdj(vf);
    novo->prox = gr->v_adjacente[vi].c_;
    gr->v_adjacente[vi].c_ = novo;
    gr->arestas++;
}

void BFS(GRAFO* gr, int inicio) {
    int* visitados = (int*)malloc(gr->vertices * sizeof(int));
    for (int i = 0; i < gr->vertices; i++) {
        visitados[i] = 0;
    }

    int* fila = (int*)malloc(gr->vertices * sizeof(int));
    int front = 0;
    int behind = 0;

    visitados[inicio] = 1;
    fila[behind++] = inicio;

    printf("Busca em Largura a partir do vertice %d: ", inicio);

    while (front != behind) {
        int atual = fila[front++];
        printf("%d ", atual);

        int* adjacentes = (int*)malloc(gr->vertices * sizeof(int));
        int numero_adjacentes = 0;

        ADJACENTE* ad = gr->v_adjacente[atual].c_;
        while (ad) {
            int vizinho = ad->vertice;
            if (!visitados[vizinho]) {
                adjacentes[numero_adjacentes++] = vizinho;
                visitados[vizinho] = 1;
            }
            ad = ad->prox;
        }

        for (int i = 0; i < numero_adjacentes - 1; i++) {
            for (int j = 0; j < numero_adjacentes - i - 1; j++) {
                if (adjacentes[j] > adjacentes[j + 1]) {
                    int t = adjacentes[j];
                    adjacentes[j] = adjacentes[j + 1];
                    adjacentes[j + 1] = t;
                }
            }
        }

        for (int i = 0; i < numero_adjacentes; i++) {
            fila[behind++] = adjacentes[i];
        }

        free(adjacentes);
    }

    printf("\n");

    free(visitados);
    free(fila);
}

void DFS(GRAFO* gr, int inicio) {
    int* visitados = (int*)malloc(gr->vertices * sizeof(int));
    for (int i = 0; i < gr->vertices; i++) {
        visitados[i] = 0;
    }

    printf("Busca em Profundidade a partir do vertice %d: ", inicio);
    DFSRecursivo(gr, inicio, visitados);
    printf("\n");

    free(visitados);
}

void DFSRecursivo(GRAFO* gr, int vertice, int* visitados) {
    visitados[vertice] = 1;
    printf("%d ", vertice);

    int* adjacentes = (int*)malloc(gr->vertices * sizeof(int));
    int numero_adjacentes = 0;

    ADJACENTE* ad = gr->v_adjacente[vertice].c_;
    while (ad) {
        int vizinho = ad->vertice;
        if (!visitados[vizinho]) {
            adjacentes[numero_adjacentes++] = vizinho;
        }
        ad = ad->prox;
    }

    for (int i = 0; i < numero_adjacentes - 1; i++) {
        for (int j = 0; j < numero_adjacentes - i - 1; j++) {
            if (adjacentes[j] > adjacentes[j + 1]) {
                int t = adjacentes[j];
                adjacentes[j] = adjacentes[j + 1];
                adjacentes[j + 1] = t;
            }
        }
    }

    for (int i = 0; i < numero_adjacentes; i++) {
        int vizinho = adjacentes[i];
        if (!visitados[vizinho]) {
            DFSRecursivo(gr, vizinho, visitados);
        }
    }
    free(adjacentes);
}

int main() {
    
    GRAFO* gr = novo_grafo(15);

    nova_aresta(gr, 0, 1);
    nova_aresta(gr, 0, 2);
    nova_aresta(gr, 1, 3);
    nova_aresta(gr, 1, 4);
    nova_aresta(gr, 1, 5);
    nova_aresta(gr, 3, 6);
    nova_aresta(gr, 3, 7);
    nova_aresta(gr, 5, 8);
    nova_aresta(gr, 5, 9);
    nova_aresta(gr, 7, 10);
    nova_aresta(gr, 7, 11);
    nova_aresta(gr, 7, 12);
    nova_aresta(gr, 9, 13);
    nova_aresta(gr, 9, 14);
    
    GRAFO* gr2 = novo_grafo(10);

    nova_aresta(gr2, 0, 1);
    nova_aresta(gr2, 1, 2);
    nova_aresta(gr2, 1, 4);
    nova_aresta(gr2, 2, 3);
    nova_aresta(gr2, 2, 4);
    nova_aresta(gr2, 2, 9);
    nova_aresta(gr2, 3, 4);
    nova_aresta(gr2, 4, 5);
    nova_aresta(gr2, 4, 6);
    nova_aresta(gr2, 4, 7);
    nova_aresta(gr2, 5, 6);
    nova_aresta(gr2, 7, 8);
    nova_aresta(gr2, 7, 9);

    BFS(gr, 1);
    DFS(gr2, 0);

    return 0;
}