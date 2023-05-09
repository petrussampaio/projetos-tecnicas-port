typedef struct hashEnderAberto {
    int qtd, TABLE_SIZE;
    Aluno **itens;
} Hash;

typedef struct hashEnderSeparado {
    int qtd, TABLE_SIZE;
    ListaAlunos **itens;
} HashSeparado;

// Funcoes para manipulacao da tabela hash com enderecamento aberto
Hash* criaHash(int TABLE_SIZE);
void liberaHash(Hash *ha);

// Funcoes para manipulacao da tabela hash com enderecamento separado
HashSeparado* criaHashSeparado(int TABLE_SIZE);
void liberaHashSeparado(HashSeparado *ha);

// Funcoes hash
int chaveDivisao(int chave, int TABLE_SIZE);
int chaveMultiplicacao(int chave, int TABLE_SIZE);
int chaveDobra(int chave, int TABLE_SIZE);

// Converter string para int
int valorString(char *str);

// Funcoes de sondagem
int sondagemLinear(int pos, int i, int TABLE_SIZE);
int sondagemQuadratica(int pos, int i, int TABLE_SIZE);
int duploHash(int H1, int chave, int i, int TABLE_SIZE);

// Funcoes de insercao, busca e remocao na tabela hash sem colisao
int insereHash_SemColisao(Hash *ha, Aluno al);
int buscaHash_SemColisao(Hash *ha, int mat, Aluno *al);
int removeHash_SemColisao(Hash *ha, int mat);

// Funcoes de insercao, busca e remocao na tabela hash com colisao (enderecamento aberto)
int insereHash_EnderAberto(Hash *ha, Aluno al);
int buscaHash_EnderAberto(Hash *ha, int mat, Aluno *al);
int removeHash_EnderAberto(Hash *ha, int mat);

// Funcoes de insercao, busca e remocao na tabela hash com colisao (enderecamento separado)
int insereHash_EnderSepatado(HashSeparado *ha, Aluno al);
int buscaHash_EnderSeparado(HashSeparado *ha, int mat, Aluno *al);
int removeHash_EnderSeparado(HashSeparado *ha, int mat);

// Funcoes auxiliares
void imprimeHash(Hash *ha);
void imprimeHashSeparado(HashSeparado *ha);