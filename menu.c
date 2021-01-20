
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gerenciadorAlunos.h"
void menuActions() {
    char option;
    while (1) {
        printOptions(ACOES_MENU);
        scanf(" %c", &option);

        system(clean);

        switch (option) {
            case SHOW:
                printAllStudInfo();
                break;
            case REGISTER:
                registerStudent();
                break;
            case EDIT:
                printAllStudInfo();
                menuEditStudent();
                break;
            case CONSOLIDAR:
                consolidarNotas();
                break;
            case SALVAR:
                saveData();
                break;
            case IMPORTAR:
                import();
                break;
            case EXIT:
                /*atexit*/
                /* freeAll(); */
                return;
        }
    }
}


void menuEditStudent() {
    stud_Index iAluno;

    if (reg.qtdStuds == 0) {
        return;
    }

    printf("Editar informações de qual aluno? (Aperte 0 para voltar)\
        \nEscolha: ");
    scanf(" %d", &iAluno);

    if (iAluno == EXIT) {
        return;
    }

    system(clean);
    editStudent(iAluno - 1);
}


void printOptions(int menu) {
    switch (menu) {
        case ACOES_MENU:
            printf("\n1 - Mostrar todos alunos cadastrados.\
                \n2 - Cadastrar um aluno.\
                \n3 - Editar um aluno.\
                \n4 - Consolidar notas.\
                \n5 - Salvar informações em um arquivo.\
                \n6 - Importar dados de arquivo\
                \n0 - Fechar programa.\
                \nEscolha: ");
            break;
        case EDIT_MENU:
            printf("1 - Editar nome.\
                    \n2 - Editar sobrenome.\
                    \n3 - Editar notas.\
                    \n0 - Terminar edição.\
                    \nEscolha: ");
            break;
    }
}
