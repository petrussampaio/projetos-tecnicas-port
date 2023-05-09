#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aluno.h"
#include "tabelahash.h"

#define TABLE_SIZE 1427

int main() {
    // criando um vetor de alunos
    Aluno *alunos[4];
    alunos[0] = criaAluno(123, "Joao", 10, 10, 10);
    alunos[1] = criaAluno(456, "Maria", 10, 10, 10);
    alunos[2] = criaAluno(789, "Jose", 10, 10, 10);
    alunos[3] = criaAluno(1550, "Lucas", 10, 10, 10);

    // criando uma tabela hash endereçamento aberto
    Hash *ha = criaHash(TABLE_SIZE);

    insereHash_EnderAberto(ha, *alunos[0]);
    insereHash_EnderAberto(ha, *alunos[1]);
    insereHash_EnderAberto(ha, *alunos[2]);
    insereHash_EnderAberto(ha, *alunos[3]);

    imprimeHash(ha);

    Aluno *buscado = (Aluno*) malloc(sizeof(Aluno));
    buscaHash_EnderAberto(ha, 1550, buscado);
    imprimeAluno(buscado);

    liberaHash(ha);

    printf("\n\nAgora com enderecamento separado\n\n\n");

    //criando uma tabela hash com endereco separado
    HashSeparado *haSeparado = criaHashSeparado(TABLE_SIZE);

    insereHash_EnderSepatado(haSeparado, *alunos[0]);
    insereHash_EnderSepatado(haSeparado, *alunos[1]);
    insereHash_EnderSepatado(haSeparado, *alunos[2]);
    insereHash_EnderSepatado(haSeparado, *alunos[3]);

    HashSeparado *haSeparadoo = criaHashSeparado(3);

  insereHash_EnderSepatado(haSeparadoo, *criaAluno(2, "D", 10, 10, 10));
  insereHash_EnderSepatado(haSeparadoo, *criaAluno(0, "Q", 10, 10, 10));
  insereHash_EnderSepatado(haSeparadoo, *criaAluno(0, "B", 10, 10, 10));

  insereHash_EnderSepatado(haSeparadoo, *criaAluno(1, "I", 10, 10, 10));
  insereHash_EnderSepatado(haSeparadoo, *criaAluno(2, "M", 10, 10, 10));

  insereHash_EnderSepatado(haSeparadoo, *criaAluno(0, "H", 10, 10, 10));
  insereHash_EnderSepatado(haSeparadoo, *criaAluno(2, "G", 10, 10, 10));

  insereHash_EnderSepatado(haSeparadoo, *criaAluno(1, "U", 10, 10, 10));
  insereHash_EnderSepatado(haSeparadoo, *criaAluno(2, "A", 10, 10, 10));

  insereHash_EnderSepatado(haSeparadoo, *criaAluno(1, "C", 10, 10, 10));
  insereHash_EnderSepatado(haSeparadoo, *criaAluno(1, "R", 10, 10, 10));
  insereHash_EnderSepatado(haSeparadoo, *criaAluno(2, "S", 10, 10, 10));
  insereHash_EnderSepatado(haSeparadoo, *criaAluno(2, "J", 10, 10, 10));

    imprimeHashSeparado(haSeparado);

    imprimeHashSeparado(haSeparadoo);

    buscaHash_EnderSeparado(haSeparado, 1550, buscado);
    imprimeAluno(buscado);
    
    for (int i = 0; i < 4; i++) {
        liberaAluno(alunos[i]);
    }

    return 0;
}