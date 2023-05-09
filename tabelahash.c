#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aluno.h"
#include "tabelahash.h"

Hash* criaHash(int table_size) {
    Hash *ha = (Hash*) malloc(sizeof(Hash));
    if (ha != NULL) {
        int i;
        ha->TABLE_SIZE = table_size;
        ha->itens = (Aluno**) malloc(table_size * sizeof(Aluno*));
        if (ha->itens == NULL) {
            free(ha);
            return NULL;
        }
        ha->qtd = 0;
        for (i = 0; i < ha->TABLE_SIZE; i++) {
            ha->itens[i] = NULL;
        }
    }
    return ha;
}

void liberaHash(Hash *ha) {
    if (ha != NULL) {
        int i;
        for (i = 0; i < ha->TABLE_SIZE; i++) {
            if (ha->itens[i] != NULL) {
                free(ha->itens[i]);
            }
        }
        free(ha->itens);
        free(ha);
    }
}

int chaveDivisao(int chave, int TABLE_SIZE) {
    return (chave & 0x7FFFFFFF) % TABLE_SIZE;
}

int chaveMultiplicacao(int chave, int TABLE_SIZE) {
    float A = 0.6180339887; // constante qualquer: 0 < A < 1
    float val = chave * A;
    val = val - (int) val;
    return (int) (TABLE_SIZE * val);
}

int chaveDobra(int chave, int TABLE_SIZE) {
    int num_bits = 10; // depende da chave e da TABLE_SIZE. É recomendado que seja um número de bits que seja um divisor do tamanho da chave, para que todas as partes da chave sejam usadas de forma equilibrada
    int parte1 = chave >> num_bits;
    int parte2 = chave & (TABLE_SIZE-1);
    return (parte1 ^ parte2);
}

int valorString(char *str) {
    int i, valor = 7; // valor primo qualquer para evitar que a string seja nula
    int tam = strlen(str);
    for (i = 0; i < tam; i++) {
        valor = 31 * valor + (int) str[i]; // 31 é um número primo qualquer, frequentemente utilizado em funções de hashing
    }
    return valor;
}

// Funções de inserção e busca quando NÃO HÁ COLISÕES!!!
int insereHash_SemColisao(Hash *ha, Aluno al) {
    if (ha == NULL || ha->qtd == ha->TABLE_SIZE) {
        return 0;
    }
    int chave = al.matricula;
    //int chave = valorString(al.nome);
    int pos = chaveDivisao(chave, ha->TABLE_SIZE);
    //int pos = chaveMultiplicacao(chave, ha->TABLE_SIZE);
    //int pos = chaveDobra(chave, ha->TABLE_SIZE);
    Aluno* novo;
    novo = (Aluno*) malloc(sizeof(Aluno));
    if (novo == NULL) {
        return 0;
    }
    *novo = al;
    ha->itens[pos] = novo;
    ha->qtd++;
    return 1;
}

int buscaHash_SemColisao(Hash *ha, int mat, Aluno *al) {
    if (ha == NULL) {
        return 0;
    }
    int pos = chaveDivisao(mat, ha->TABLE_SIZE);
    //int pos = chaveMultiplicacao(mat, ha->TABLE_SIZE);
    //int pos = chaveDobra(mat, ha->TABLE_SIZE);
    if (ha->itens[pos] == NULL) {
        return 0;
    }
    *al = *(ha->itens[pos]);
    return 1;
}

int removeHash_SemColisao(Hash *ha, int mat) {
    if (ha == NULL) {
        return 0;
    }
    int pos = chaveDivisao(mat, ha->TABLE_SIZE);
    //int pos = chaveMultiplicacao(mat, ha->TABLE_SIZE);
    //int pos = chaveDobra(mat, ha->TABLE_SIZE);
    if (ha->itens[pos] == NULL) {
        return 0;
    }
    free(ha->itens[pos]);
    ha->itens[pos] = NULL;
    ha->qtd--;
    return 1;
}

// Funções de inserção e busca quando HÁ COLISÕES!!!
// ENDEREÇAMENTO ABERTO!!!
int insereHash_EnderAberto(Hash *ha, Aluno al) {
    if (ha == NULL || ha->qtd == ha->TABLE_SIZE) {
        return 0;
    }
    int chave = al.matricula;
    //int chave = valorString(al.nome);
    int i, pos, newPos;
    pos = chaveDivisao(chave, ha->TABLE_SIZE);
    //pos = chaveMultiplicacao(chave, ha->TABLE_SIZE);
    //pos = chaveDobra(chave, ha->TABLE_SIZE);
    for (i = 0; i < ha->TABLE_SIZE; i++) {
        newPos = sondagemLinear(pos, i, ha->TABLE_SIZE);
        //newPos = sondagemQuadratica(pos, i, ha->TABLE_SIZE);
        //newPos = duploHash(pos, chave, i, ha->TABLE_SIZE);
        if (ha->itens[newPos] == NULL) {
            Aluno* novo;
            novo = (Aluno*) malloc(sizeof(Aluno));
            if (novo == NULL) {
                return 0;
            }
            *novo = al;
            ha->itens[newPos] = novo;
            ha->qtd++;
            return 1;
        }
    }
    return 0;
}

int buscaHash_EnderAberto(Hash *ha, int mat, Aluno *al) {
    if (ha == NULL) {
        return 0;
    }
    int i, pos, newPos;
    pos = chaveDivisao(mat, ha->TABLE_SIZE);
    //pos = chaveMultiplicacao(mat, ha->TABLE_SIZE);
    //pos = chaveDobra(mat, ha->TABLE_SIZE);
    for (i = 0; i < ha->TABLE_SIZE; i++) {
        newPos = sondagemLinear(pos, i, ha->TABLE_SIZE);
        //newPos = sondagemQuadratica(pos, i, ha->TABLE_SIZE);
        //newPos = duploHash(pos, mat, i, ha->TABLE_SIZE);
        if (ha->itens[newPos] == NULL) {
            return 0;
        }
        if (ha->itens[newPos]->matricula == mat) {
            *al = *(ha->itens[newPos]);
            return 1;
        }
    }
    return 0;
}

int removeHash_EnderAberto(Hash *ha, int mat) {
    if (ha == NULL) {
        return 0;
    }
    int i, pos, newPos;
    pos = chaveDivisao(mat, ha->TABLE_SIZE);
    //pos = chaveMultiplicacao(mat, ha->TABLE_SIZE);
    //pos = chaveDobra(mat, ha->TABLE_SIZE);
    for (i = 0; i < ha->TABLE_SIZE; i++) {
        newPos = sondagemLinear(pos, i, ha->TABLE_SIZE);
        //newPos = sondagemQuadratica(pos, i, ha->TABLE_SIZE);
        //newPos = duploHash(pos, mat, i, ha->TABLE_SIZE);
        if (ha->itens[newPos] == NULL) {
            return 0;
        }
        if (ha->itens[newPos]->matricula == mat) {
            free(ha->itens[newPos]);
            ha->itens[newPos] = NULL;
            ha->qtd--;
            return 1;
        }
    }
    return 0;
}

int sondagemLinear(int pos, int i, int TABLE_SIZE) {
    return ((pos + i) & 0x7FFFFFFF) % TABLE_SIZE;
}

int sondagemQuadratica(int pos, int i, int TABLE_SIZE) {
    pos = pos + 2*i + 5*i*i; // função quadrática c1 = 2, c2 = 5
    return (pos & 0x7FFFFFFF) % TABLE_SIZE;
}

int duploHash(int H1, int chave, int i, int TABLE_SIZE) {
    int H2 = chaveDivisao(chave, TABLE_SIZE-1) + 1;
    //int H2 = chaveMultiplicacao(chave, TABLE_SIZE-1) + 1;
    //int H2 = chaveDobra(chave, TABLE_SIZE-1) + 1;
    return ((H1 + i*H2) & 0x7FFFFFFF) % TABLE_SIZE;
}

void imprimeHash(Hash *ha) {
    if (ha == NULL) {
        return;
    }
    int i;
    printf("Tabela Hash:\n");
    for (i = 0; i < ha->TABLE_SIZE; i++) {
        if (ha->itens[i] != NULL) {
            printf("Posição: %d. Aluno: %d\n", i, ha->itens[i]->matricula);  
        } 
    }
    printf("\n");
}

// Funções de hash separado
HashSeparado* criaHashSeparado(int TABLE_SIZE) {
    HashSeparado* ha = (HashSeparado*) malloc(sizeof(HashSeparado));
    if (ha != NULL) {
        int i;
        ha->TABLE_SIZE = TABLE_SIZE;
        ha->itens = (ListaAlunos**) malloc(TABLE_SIZE * sizeof(ListaAlunos*));
        if (ha->itens == NULL) {
            free(ha);
            return NULL;
        }
        for (i = 0; i < TABLE_SIZE; i++) {
            ha->itens[i] = NULL;
        }
    }
    return ha;
}
void liberaHashSeparado(HashSeparado *ha){
    if (ha != NULL) {
        int i;
        for (i = 0; i < ha->TABLE_SIZE; i++) {
            if (ha->itens[i] != NULL) {
                free(ha->itens[i]);
            }
        }
        free(ha->itens);
        free(ha);
    }
}

// Funções de inserção e busca quando HÁ COLISÕES!!!
// ENDEREÇAMENTO SEPARADO!!!
int insereHash_EnderSepatado(HashSeparado *ha, Aluno al) {
    if (ha == NULL || ha->qtd == ha->TABLE_SIZE) {
        return 0;
    }
    int chave = al.matricula;
    //int chave = valorString(al.nome);
    int pos = chaveDivisao(chave, ha->TABLE_SIZE);
    //int pos = chaveMultiplicacao(chave, ha->TABLE_SIZE);
    //int pos = chaveDobra(chave, ha->TABLE_SIZE);
    ListaAlunos *lista = ha->itens[pos];
    if (lista == NULL) {
        lista = (ListaAlunos*) malloc(sizeof(ListaAlunos));
        if (lista == NULL) {
            return 0;
        }
        // inicializa a lista pois é a primeira inserção
        lista->aluno = al;
        lista->prox = NULL;
        ha->itens[pos] = lista;
    } else {
        // lista já existe, insere no final da lista
        inserirAlunoLista(lista, al);
    }
    return 1;
}

int buscaHash_EnderSeparado(HashSeparado *ha, int mat, Aluno *al) {
    if (ha == NULL) {
        return 0;
    }
    int pos = chaveDivisao(mat, ha->TABLE_SIZE);
    //int pos = chaveMultiplicacao(mat, ha->TABLE_SIZE);
    //int pos = chaveDobra(mat, ha->TABLE_SIZE);
    ListaAlunos *lista = ha->itens[pos];
    if (lista == NULL) {
        return 0;
    }
    return buscaAlunoLista(lista, mat, al);
}

int removeHash_EnderSeparado(HashSeparado *ha, int mat) {
    if (ha == NULL) {
        return 0;
    }
    int pos = chaveDivisao(mat, ha->TABLE_SIZE);
    //int pos = chaveMultiplicacao(mat, ha->TABLE_SIZE);
    //int pos = chaveDobra(mat, ha->TABLE_SIZE);
    ListaAlunos *lista = ha->itens[pos];
    if (lista == NULL) {
        return 0;
    }
    if (lista->aluno.matricula == mat) {
        // remove o primeiro aluno da lista
        ha->itens[pos] = lista->prox;
        free(lista);
        return 1;
    }
    return removerAlunoLista(lista, mat);
}

void imprimeHashSeparado(HashSeparado *ha) {
    if (ha == NULL) {
        return;
    }
    int i;
    printf("Tabela Hash:\n");
    for (i = 0; i < ha->TABLE_SIZE; i++) {
        if (ha->itens[i] != NULL) {
            printf("Posição: %d. Alunos: ", i);
            imprimeListaAlunosMat(ha->itens[i]);
        } 
    }
    printf("\n");
}