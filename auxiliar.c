#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gerenciadorAlunos.h"

int isNumber(char *buffer) {
    char *foo;

    strtod(buffer, &foo);

    if (foo == buffer) {
        return 0;
    }
        return 1;
}


int getTotalLines(char *nomeArquivo) {
    FILE *fp;
    int count = 0;
    char c;

    /* Abre o arquivo para leitura */
    fp = fopen(nomeArquivo, "r");

    /* Extrai caractere por caractere e se achar um '\n',
       soma 1 ao total de linhas */
    for (c = getc(fp); c != EOF; c = getc(fp))
        if (c == '\n')
            count = count + 1;
    fclose(fp);
    return count;
}

void debug(int input, int input2) {
    printf("\n\t[DEBUG] %d %d\n\n", input, input2);
    getchar();
    getchar();
}


void freeAll() {
    for (int i = 0; i < reg.qtdStuds; i++) {
        free(reg.alunos[i].notas);
    }
    free(reg.alunos);
}


void increaseRegistrySize(int increment) {
    reg.qtdStuds += increment;
	reg.alunos = (Aluno_t *)realloc(reg.alunos,
		(reg.qtdStuds) * sizeof(Aluno_t));
}


void incStudTotalNotas(int increment, stud_Index iAluno) {
    reg.alunos[iAluno].notas = (float *)realloc(reg.alunos[iAluno].notas,
            sizeof(float) * (reg.alunos[iAluno].totalNotas + increment));
}
