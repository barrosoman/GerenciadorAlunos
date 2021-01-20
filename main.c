#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gerenciadorAlunos.h"
Registry_t reg;

int main() {
    reg.qtdStuds = 0;
    reg.alunos = (Aluno_t *)malloc(sizeof(Aluno_t));

    printf("Bem vindo, o que deseja fazer?\n");
    menuActions();

    return EXIT_SUCCESS;
}
