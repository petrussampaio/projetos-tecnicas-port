#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aluno.h"

Aluno* criaAluno(int mat, char* nome, float n1, float n2, float n3) {
    Aluno* al = (Aluno*) malloc(sizeof(Aluno));
    if (al != NULL) {
        al->matricula = mat;
        strcpy(al->nome, nome);
        al->n1 = n1;
        al->n2 = n2;
        al->n3 = n3;
    }
    return al;
}

void liberaAluno(Aluno* al) {
    free(al);
}

void imprimeAluno(Aluno* al) {
    printf("Matricula: %d\n", al->matricula);
    printf("Nome: %s\n", al->nome);
    printf("Notas: %.2f %.2f %.2f\n", al->n1, al->n2, al->n3);
}

void imprimeListaAlunos(ListaAlunos* lista) {
    ListaAlunos* p = lista;
    while (p != NULL) {
        imprimeAluno(&p->aluno);
        p = p->prox;
    }
}

void imprimeListaAlunosMat(ListaAlunos* lista) {
    ListaAlunos* p = lista;
    while (p != NULL) {
        printf("%d ", p->aluno.matricula);
        p = p->prox;
    }
    printf("\n");
}

int buscaAlunoLista(ListaAlunos* lista, int mat, Aluno *al){
    ListaAlunos* p = lista;
    while (p != NULL && p->aluno.matricula != mat) {
        p = p->prox;
    }
    if (p == NULL) {
        return 0;
    } else {
        *al = p->aluno;
        return 1;
    }
}

void percorrer(ListaAlunos *l) {
    ListaAlunos *p = l;
    while (p != NULL) {
        printf("Matricula: %d\n", p->aluno.matricula);
        printf("Nome: %s\n", p->aluno.nome);
        printf("Notas: %.2f %.2f %.2f\n", p->aluno.n1, p->aluno.n2, p->aluno.n3);
        p = p->prox;
    }
}

ListaAlunos* inserirAlunoLista(ListaAlunos *l, Aluno al) {
    //inserção no final da lista
    ListaAlunos *novo = (ListaAlunos*) malloc(sizeof(ListaAlunos));
    novo->aluno = al;
    novo->prox = NULL;
    if (l == NULL) {
        l = novo;
    } else {
        ListaAlunos *p = l;
        while (p->prox != NULL) {
            p = p->prox;
        }
        p->prox = novo;
    }
}

int removerAlunoLista(ListaAlunos *l, int mat) {
    ListaAlunos *p = l;
    ListaAlunos *ant = NULL;
    while (p != NULL && p->aluno.matricula != mat) {
        ant = p;
        p = p->prox;
    }
    if (p == NULL) {
        return 0;
    }
    if (ant == NULL) {
        l = p->prox;
    } else {
        ant->prox = p->prox;
    }
    free(p);
    return 1;
}