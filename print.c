#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gerenciadorAlunos.h"

void printOneStudInfo(stud_Index iAluno) {
    printf("\n%d -\n", iAluno + 1);
    printf("\tNome: %s\n", reg.alunos[iAluno].nome);
    printf("\tSobrenome: %s\n", reg.alunos[iAluno].sobrenome);
    printf("\tNotas: ");
    for (int j = 0; j < reg.alunos[iAluno].totalNotas; j++) {
        printf("%.2f ", reg.alunos[iAluno].notas[j]);
    }
    printf("\n\n");
}


void printAllStudInfo() {
    if (reg.qtdStuds == 0) {
        printf("Não há ninguém cadastrado.\n\n");
        return;
    }
    for (int i = 0; i < reg.qtdStuds; i++) {
        printOneStudInfo(i);
    }
}


void consolidarNotas() {
    int mediaNotas;

    if (reg.qtdStuds == 0) {
        return;
    }

    for (int i = 0; i < reg.qtdStuds; i++) {
        mediaNotas = 0;
        printOneStudInfo(i);
        for (int j = 0; j < reg.alunos[i].totalNotas; j++) {
            mediaNotas += reg.alunos[i].notas[j];
        }

        mediaNotas = mediaNotas/reg.alunos[i].totalNotas;

        printf ("Aluno(a)%spassou com média %d.\n",
        	(mediaNotas >= 5) ? " " : " não ", mediaNotas);
    }
}
