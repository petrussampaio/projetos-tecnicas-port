typedef struct grafo {
    int eh_ponderado;
    int nro_vertices;
    int grau_max;
    int **arestas;
    float **pesos;
    int *grau;
} Grafo;

Grafo *cria_grafo(int nro_vertices, int grau_max, int eh_ponderado);
void libera_grafo(Grafo *gr);
int insere_aresta(Grafo *gr, int orig, int dest, int eh_digrafo, float peso);
int remove_aresta(Grafo *gr, int orig, int dest, int eh_digrafo);
void imprime_grafo(Grafo *gr);

void busca_largura_grafo(Grafo *gr, int ini, int *visitado);
void busca_profundidade_grafo(Grafo *gr, int ini, int *visitado);
void menor_caminho_grafo(Grafo *gr, int ini, int *ant, float *dist);