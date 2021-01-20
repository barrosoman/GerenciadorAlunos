
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gerenciadorAlunos.h"
void import() {
    char nomeArquivo[100];
    do {
        printf("Importar de que arquivo?\
                \nArquivo: ");
        scanf(" %s", nomeArquivo);
        system(clean);
    } while (fopen(nomeArquivo, "r") == NULL);
    importAllStudInfo(nomeArquivo);
}


void importAllStudInfo(char *nomeArquivo) {
    FILE *fp = fopen(nomeArquivo, "r");
    char buffer[200];
    int totalNotas;

    int qtdStudsOld = reg.qtdStuds;
    int increment = getTotalLines(nomeArquivo);
    increaseRegistrySize(increment);

    for (int i = qtdStudsOld; i < reg.qtdStuds; i++) {
        totalNotas = 0;
        fscanf(fp, "%s", reg.alunos[i].nome);
        do {
            fscanf(fp, "%s", buffer);
            if (!isNumber(buffer)) {
                strcat(reg.alunos[i].sobrenome, buffer);
                strcat(reg.alunos[i].sobrenome, " ");
            } else {
                /* incStudTotalNotas(1); */
                reg.alunos[i].notas = (float *)realloc(reg.alunos[i].notas,
                        sizeof(float) * (totalNotas+1));
                sscanf(buffer, "%f", &reg.alunos[i].notas[totalNotas]);
                totalNotas++;
            }
        } while(getc(fp) != '\n');
        reg.alunos[i].totalNotas = totalNotas;
    }
    fclose(fp);
}
