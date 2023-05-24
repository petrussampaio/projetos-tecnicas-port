#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

Grafo *cria_grafo(int nro_vertices, int grau_max, int eh_ponderado) {
    Grafo *gr = (Grafo*) malloc(sizeof(struct grafo));
    if (gr != NULL) {
        int i;
        gr->nro_vertices = nro_vertices;
        gr->grau_max = grau_max;
        gr->eh_ponderado = (eh_ponderado != 0) ? 1:0;
        gr->grau = (int*) calloc(nro_vertices, sizeof(int));
        gr->arestas = (int**) malloc(nro_vertices * sizeof(int*));
        for (i = 0; i < nro_vertices; i++)
            gr->arestas[i] = (int*) malloc(grau_max * sizeof(int));
        if (gr->eh_ponderado) {
            gr->pesos = (float**) malloc(nro_vertices * sizeof(float*));
            for (i = 0; i < nro_vertices; i++)
                gr->pesos[i] = (float*) malloc(grau_max * sizeof(float));
        }
    }
    return gr;
}

void libera_grafo(Grafo *gr) {
    if (gr != NULL) {
        int i;
        for (i = 0; i < gr->nro_vertices; i++)
            free(gr->arestas[i]);
        free(gr->arestas);
        if (gr->eh_ponderado) {
            for (i = 0; i < gr->nro_vertices; i++)
                free(gr->pesos[i]);
            free(gr->pesos);
        }
        free(gr->grau);
        free(gr);
    }
}

int insere_aresta(Grafo *gr, int orig, int dest, int eh_digrafo, float peso) {
    if (gr == NULL)
        return 0;
    if (orig < 0 || orig >= gr->nro_vertices)
        return 0;
    if (dest < 0 || dest >= gr->nro_vertices)
        return 0;
    gr->arestas[orig][gr->grau[orig]] = dest;
    if (gr->eh_ponderado)
        gr->pesos[orig][gr->grau[orig]] = peso;
    gr->grau[orig]++;
    if (eh_digrafo == 0)
        insere_aresta(gr, dest, orig, 1, peso);
    return 1;
}

int remove_aresta(Grafo *gr, int orig, int dest, int eh_digrafo) {
    if (gr == NULL)
        return 0;
    if (orig < 0 || orig >= gr->nro_vertices)
        return 0;
    if (dest < 0 || dest >= gr->nro_vertices)
        return 0;
    int i = 0;
    while (i < gr->grau[orig] && gr->arestas[orig][i] != dest)
        i++;
    if (i == gr->grau[orig])
        return 0;
    gr->grau[orig]--;
    gr->arestas[orig][i] = gr->arestas[orig][gr->grau[orig]];
    if (gr->eh_ponderado)
        gr->pesos[orig][i] = gr->pesos[orig][gr->grau[orig]];
    if (eh_digrafo == 0)
        remove_aresta(gr, dest, orig, 1);
    return 1;
}

void imprime_grafo(Grafo *gr) {
    if (gr == NULL)
        return;
    int i, j;
    for (i = 0; i < gr->nro_vertices; i++) {
        printf("%d: ", i);
        for (j = 0; j < gr->grau[i]; j++) {
            if (gr->eh_ponderado)
                printf("%d(%.2f), ", gr->arestas[i][j], gr->pesos[i][j]);
            else
                printf("%d, ", gr->arestas[i][j]);
        }
        printf("\n");
    }
}

void busca_largura_grafo(Grafo *gr, int ini, int *visitado) {
    int i, vert, NV, cont = 1;
    int *fila, IF = 0, FF = 0;
    for (i = 0; i < gr->nro_vertices; i++)
        visitado[i] = 0;
    NV = gr->nro_vertices;
    fila = (int*) malloc(NV * sizeof(int));
    FF++;
    fila[FF] = ini;
    visitado[ini] = cont;
    while (IF != FF) {
        IF = (IF + 1) % NV;
        vert = fila[IF];
        cont++;
        for (i = 0; i < gr->grau[vert]; i++) {
            if (!visitado[gr->arestas[vert][i]]) {
                FF = (FF + 1) % NV;
                fila[FF] = gr->arestas[vert][i];
                visitado[gr->arestas[vert][i]] = cont;
            }
        }
    }
    free(fila);
}

//Função auxiliar para busca em profundidade
void busca_profundidade(Grafo *gr, int ini, int *visitado, int cont) {
    int i;
    visitado[ini] = cont;
    for (i = 0; i < gr->grau[ini]; i++) {
        if (!visitado[gr->arestas[ini][i]])
            busca_profundidade(gr, gr->arestas[ini][i], visitado, cont+1);
    }
}

//Função principal: faz a interface com o usuário 
void busca_profundidade_grafo(Grafo *gr, int ini, int *visitado) {
    int i, cont = 1;
    for (i = 0; i < gr->nro_vertices; i++)
        visitado[i] = 0;
    busca_profundidade(gr, ini, visitado, cont);
}

//Função auxiliar para procura do menor caminho
int procura_menor_distancia(float *dist, int *visitado, int NV) {
    int i, menor = -1, primeiro = 1;
    for (i = 0; i < NV; i++) {
        if (dist[i] >= 0 && visitado[i] == 0) {
            if (primeiro) {
                menor = i;
                primeiro = 0;
            } else {
                if (dist[menor] > dist[i])
                    menor = i;
            }
        }
    }
    return menor;
}

//Função principal Dijsktra: faz a interface com o usuário
void menor_caminho_grafo(Grafo *gr, int ini, int *ant, float *dist) {
    int i, cont, NV, ind, *visitado, u;
    cont = NV = gr->nro_vertices;
    visitado = (int*) malloc(NV * sizeof(int));
    for (i = 0; i < NV; i++) {
        ant[i] = -1;
        dist[i] = -1;
        visitado[i] = 0;
    }
    dist[ini] = 0;
    while (cont > 0) {
        u = procura_menor_distancia(dist, visitado, NV);
        if (u == -1)
            break;
        visitado[u] = 1;
        cont--;
        for (i = 0; i < gr->grau[u]; i++) {
            ind = gr->arestas[u][i];
            if (dist[ind] < 0) {
                //dist[ind] = dist[u] + 1;
                dist[ind] = dist[u] + gr->pesos[u][i];
                ant[ind] = u;
              
            } else {
                if (dist[ind] > dist[u] + 1) {
                    //dist[ind] = dist[u] + 1;
                    dist[ind] = dist[u] + gr->pesos[u][i];
                    ant[ind] = u;
                }
            }
        }
    }
    free(visitado);
}