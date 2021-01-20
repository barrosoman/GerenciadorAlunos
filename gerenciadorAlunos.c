#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
    #define clean "cls"
#elif __linux
    #define clean "clear"
#else
    #define clean ""
#endif

enum escolhasAcoes{
    ACOES_MENU      =  1,
    SHOW            = '1',
    REGISTER        = '2',
    EDIT            = '3',
    CONSOLIDAR      = '4',
    SALVAR          = '5',
    IMPORTAR        = '6',
    EXIT            = '0',
};

enum escolhasEdit{
    EDIT_MENU       =  2,
    NOME            = '1',
    SOBRENOME       = '2',
    NOTA            = '3',
};

typedef struct aluno {
    char nome[100],
         sobrenome[100];
    float *notas;
    int totalNotas;
} Aluno_t;


typedef struct registry {
    int qtdStuds;
    Aluno_t *alunos;
} Registry_t;

Registry_t reg;

typedef int studIndex;

/* Funções de menu */
void menuActions();
void menuEditStudent();

/* Funções de adição/edição de reg.alunos */
void registerStudent();
void editStudent(studIndex iAluno);
void editNomeGeneric(const char *prompt, char *field);
void editNome(studIndex iAluno);
void editSobrenome(studIndex iAluno);
void editNotas(studIndex iAluno);

/* Funções para printar informações */
void printOptions(int menu);
void printOneStudInfo(studIndex iAluno);
void printAllStudInfo();

/* Função para dar free() em todos arrays */
void freeAll();

/* Função para consolidar notas */
void consolidarNotas();

/* Funções para salvar dados em um arquivo */
void saveData();
void sendData(FILE *fp);

/* Funções para importar dados de um arquivo */
void import();
void importAllStudInfo(char *nomeArquivo);

/* Funções auxiliares */
int isNumber(char *buffer);
int getTotalLines(char *nomeArquivo);
void debug(int input, int input2);

/* Funções para realloc de arrays */
void incStudTotalNotas (int increment, studIndex iAluno);
void increaseRegistrySize (int increment);

void analyzeImportData(FILE *fp, char *buffer, studIndex iAluno);

int main() {
    reg.qtdStuds = 0;
    reg.alunos = (Aluno_t *)malloc(sizeof(Aluno_t));

    printf("Bem vindo, o que deseja fazer?\n");
    menuActions();

    return EXIT_SUCCESS;
}


void increaseRegistrySize(int increment) {
    reg.qtdStuds += increment;
	reg.alunos = (Aluno_t *)realloc(reg.alunos,
		(reg.qtdStuds) * sizeof(Aluno_t));
}


void incStudTotalNotas(int increment, studIndex iAluno) {
    reg.alunos[iAluno].notas = (float *)realloc(reg.alunos[iAluno].notas,
            sizeof(float) * (reg.alunos[iAluno].totalNotas + increment));
}


void registerStudent() {
	studIndex iAluno = reg.qtdStuds;
	increaseRegistrySize (1);

    editNome(iAluno);
    editSobrenome(iAluno);
    editNotas(iAluno);
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
    studIndex iAluno;

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


void editStudent(studIndex iAluno) {
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


/* Função para edição de notas */
void editNotas(studIndex iAluno) {
    Aluno_t *currAluno = &reg.alunos[iAluno];
    int totalNotas;

    printf("Quantas provas o aluno fez?\
            \nTotal: ");
    scanf(" %d", &totalNotas);

    currAluno->totalNotas = totalNotas;
    incStudTotalNotas(0, iAluno);

    for (int i = 0; i < totalNotas; i++) {
        printf("%dª Prova: ", i + 1);
        scanf(" %f", &currAluno->notas[i]);
    }
    system(clean);
}

/* Função genérica para edição de nomes */
void editNomeGeneric(const char *prompt, char *field) {
    printf("%s do Aluno: ", prompt);
    scanf(" %[^\n]s", field);
    system(clean);
}


void editNome(studIndex iAluno) {
    editNomeGeneric("Nome", reg.alunos[iAluno].nome);
}


void editSobrenome(studIndex iAluno) {
    editNomeGeneric("Sobrenome", reg.alunos[iAluno].sobrenome);
}


/* Imprime informação de um aluno */
void printOneStudInfo(studIndex iAluno) {
    printf("\n%d -\n", iAluno + 1);
    printf("\tNome: %s\n", reg.alunos[iAluno].nome);
    printf("\tSobrenome: %s\n", reg.alunos[iAluno].sobrenome);
    printf("\tNotas: ");
    for (int j = 0; j < reg.alunos[iAluno].totalNotas; j++) {
        printf("%.2f ", reg.alunos[iAluno].notas[j]);
    }
    printf("\n\n");
}


/* Chama a função de imprimir informação de um aluno
   para todos alunos */
void printAllStudInfo() {
    if (reg.qtdStuds == 0) {
        printf("Não há ninguém cadastrado.\n\n");
        return;
    }
    for (int i = 0; i < reg.qtdStuds; i++) {
        printOneStudInfo(i);
    }
}


/* Função para liberar memória alocada com malloc */
void freeAll() {
    for (int i = 0; i < reg.qtdStuds; i++) {
        free(reg.alunos[i].notas);
    }
    free(reg.alunos);
}


/* Função para mostrar se um aluno passou ou não */
void consolidarNotas() {
    float mediaNotas;

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

        printf ("Aluno(a)%spassou com média %.2f.\n",
        	(mediaNotas >= 5) ? " " : " não ", mediaNotas);
    }
}


/* Função usada para importar informações de um arquivo */
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


/* Analisa os dados no arquivo para importar os dados
   organizadamente */
void importAllStudInfo(char *nomeArquivo) {
    FILE *fp = fopen(nomeArquivo, "r");
    char buffer[200];

    int qtdStudsOld = reg.qtdStuds;
    int increment = getTotalLines(nomeArquivo);
    increaseRegistrySize(increment);

    for (int i = qtdStudsOld; i < reg.qtdStuds; i++) {
        analyzeImportData(fp, buffer ,i);
    }
    fclose(fp);
}

void analyzeImportData(FILE *fp, char *buffer, studIndex iAluno) {
    int totalNotas = 0;

    /* A primeira palavra é sempre o nome */
    fscanf(fp, "%s", reg.alunos[iAluno].nome);
    do {
        /* Prepara a próxima palavra para ser analisada */
        fscanf(fp, "%s", buffer);

        /* Verifica se a palavra é uma palavra ou não */
        if (!isNumber(buffer)) {
            /* Se buffer for uma palavra, ela é concatenada ao sobrenome */
            strcat(reg.alunos[iAluno].sobrenome, buffer);
            strcat(reg.alunos[iAluno].sobrenome, " ");
        } else {
            /* Se for um número, é inserida a uma nota do aluno */
            incStudTotalNotas(1, iAluno);
            reg.alunos[iAluno].notas = (float *)realloc(reg.alunos[iAluno].notas,
                    sizeof(float) * (totalNotas+1));
            sscanf(buffer, "%f", &reg.alunos[iAluno].notas[totalNotas]);
            totalNotas++;
        }
    } while(getc(fp) != '\n');
    reg.alunos[iAluno].totalNotas = totalNotas;
}


/* Função para verificar se um pedaço de texo é um número ou uma palavra */
int isNumber(char *buffer) {
    char *foo;

    /* Transforma buffer em um número e insere o valor em foo  */
    strtof(buffer, &foo);

    /* Se foo for igual a buffer, o texto em buffer é um número */
    if (foo == buffer) {
        return 0;
    }

    /* Se não, o texto é só uma palavra */
        return 1;
}


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
    fclose(fp);
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
