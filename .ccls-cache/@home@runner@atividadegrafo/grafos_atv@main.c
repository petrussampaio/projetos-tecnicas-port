#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

void mostra_vetor(int *vet, int tam) {
    int i;
    for (i = 0; i < tam; i++)
        printf("%d ", vet[i]);
    printf("\n");
}

void mostra_vetor2(float *vet, int tam) {
    int i;
    for (i = 0; i < tam; i++)
        printf("%.2f ", vet[i]);
    printf("\n");
}

int main() {
    Grafo *gr = cria_grafo(5, 5, 1);
    int eh_digrafo = 1;
    insere_aresta(gr, 0, 1, eh_digrafo, 1);
    insere_aresta(gr, 1, 3, eh_digrafo, 1);
    insere_aresta(gr, 1, 2, eh_digrafo, 3);
    insere_aresta(gr, 2, 4, eh_digrafo, 4);
    insere_aresta(gr, 3, 0, eh_digrafo, 4);
    insere_aresta(gr, 3, 4, eh_digrafo, 2);
    insere_aresta(gr, 4, 1, eh_digrafo, 5);
    imprime_grafo(gr);
    
    //Exemplo do busca_largura_grafo
    int vis[5];
    busca_largura_grafo(gr, 0, vis);
    //Mostre o vetor vis
    printf("Vetor vis: ");
    mostra_vetor(vis, 5);
    
    //Exemplo do busca_profundidade_grafo
    int visitado[5];
    busca_profundidade_grafo(gr, 0, visitado);
    //Mostre o vetor visitado
    printf("Vetor visitado: ");
    mostra_vetor(visitado, 5);

    //Exemplo do menor_caminho_grafo
    int ant[5];
    float dist[5];
    menor_caminho_grafo(gr, 0, ant, dist);
    //Mostre o vetor ant
    printf("Vetor ant: ");
    mostra_vetor(ant, 5);
    //Mostre o vetor dist
    printf("Peso aresta: ");
    mostra_vetor2(dist, 5);

    libera_grafo(gr);
    return 0;
}