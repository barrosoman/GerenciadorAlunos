
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gerenciadorAlunos.h"
void saveData() {
    FILE *fp;
    char nomeArquivo[40];
    printf("Salvar em que arquivo?\n");
    scanf(" %s", nomeArquivo);
    fp = fopen(nomeArquivo, "w");
    sendData(fp);
}


void sendData(FILE *fp) {
    /* Passando por cada estudante no array, imprime seus dado a um arquivo
       arbitrário */
    for (int i = 0; i < reg.qtdStuds; i++) {
        fprintf(fp, "%s %s", reg.alunos[i].nome, reg.alunos[i].sobrenome);

        for (int j = 0; j < reg.alunos[i].totalNotas; j++) {
            fprintf(fp, " %.2f", reg.alunos[i].notas[j]);
        }
        fputc('\n', fp);
    }
}
