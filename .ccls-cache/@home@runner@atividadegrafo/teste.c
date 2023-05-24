#define INFINITY 99999

void menor_caminho_grafo(Grafo *gr, int ini, int *ant, float *dist) {
    int i, cont, NV, ind;
    int *visitado, u, A, v;
    A = gr->nro_vertices;
    visitado = (int*) malloc(A * sizeof(int));
    for (i = 0; i < A; i++) {
        ant[i] = -1;
        dist[i] = INFINITY;
        visitado[i] = 0;
    }
    dist[ini] = 0;
    u = ini;
    cont = 0;
    while (u != -1 && cont < A) {
        visitado[u] = 1;
        for (i = 0; i < gr->grau[u]; i++) {
            v = gr->arestas[u][i];
            if (!visitado[v]) {
                if (dist[v] > (dist[u] + gr->pesos[u][i])) {
                    ant[v] = u;
                    dist[v] = dist[u] + gr->pesos[u][i];
                }
            }
        }
        u = -1;
        for (i = 0; i < A; i++) {
            if (!visitado[i] && dist[i] < INFINITY) {
                if (u == -1) u = i;
                else if (dist[i] < dist[u]) u = i;
            }
        }
        cont++;
    }
    free(visitado);
}