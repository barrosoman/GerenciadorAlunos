
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gerenciadorAlunos.h"
void registerStudent() {
	stud_Index iAluno = reg.qtdStuds;
	increaseRegistrySize (1);

    editNome(iAluno);
    editSobrenome(iAluno);
    editNotas(iAluno);
}


void editStudent(stud_Index iAluno) {
    char choice;

    printf("O que editar de %s %s?\n", reg.alunos[iAluno].nome, reg.alunos[iAluno].sobrenome);
    while(1) {
        printOneStudInfo(iAluno);
        printOptions(EDIT_MENU);
        scanf(" %c", &choice);
        system(clean);

        switch (choice) {
            case NOME:
                editNome(iAluno);
                break;
            case SOBRENOME:
                editSobrenome(iAluno);
                break;
            case NOTA:
                editNotas(iAluno);
                break;
            case EXIT:
                return;
                break;
            default:
                break;
        }
    }
}


void editNotas(stud_Index iAluno) {
    int totalNotas;
    printf("Quantas provas o aluno fez?\
            \nTotal: ");
    scanf(" %d", &totalNotas);

    Aluno_t *currAluno = &reg.alunos[iAluno];


    currAluno -> totalNotas=totalNotas;
    incStudTotalNotas(0, iAluno);

    for (int i = 0; i < totalNotas; i++) {
        printf("%dª Prova: ", i + 1);
        scanf(" %f", &reg.alunos[iAluno].notas[i]);
    }
    system(clean);
}


void editNomeGeneric(const char *prompt, char *field) {
    printf("%s do Aluno: ", prompt);
    scanf(" %[^\n]s", field);
    system(clean);
}


void editNome(stud_Index iAluno) {
    editNomeGeneric("Nome", reg.alunos[iAluno].nome);
}


void editSobrenome(stud_Index iAluno) {
    editNomeGeneric("Sobrenome", reg.alunos[iAluno].sobrenome);
}
