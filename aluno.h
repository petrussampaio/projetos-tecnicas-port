typedef struct aluno {
    int matricula;
    char nome[30];
    float n1, n2, n3;
} Aluno;

// Criando uma lista de Alunos
typedef struct lista {
    Aluno aluno;
    struct lista *prox;
} ListaAlunos;


Aluno* criaAluno(int mat, char* nome, float n1, float n2, float n3);
void liberaAluno(Aluno* al);
void imprimeAluno(Aluno* al);
void imprimeListaAlunos(ListaAlunos* lista);
void imprimeListaAlunosMat(ListaAlunos* lista);
int buscaAlunoLista(ListaAlunos* lista, int mat, Aluno *al);
void percorrer(ListaAlunos *l);
ListaAlunos* inserirAlunoLista(ListaAlunos *l, Aluno al);
int removerAlunoLista(ListaAlunos *l, int mat);