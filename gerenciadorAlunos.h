#pragma once

#ifdef _WIN32
    #define clean "cls"
#elif __linux
    #define clean "clear"
#else
    #define clean ""
#endif


enum escolhasAcoes{
    ACOES_MENU = 1,
    SHOW = '1',
    REGISTER = '2',
    EDIT = '3',
    CONSOLIDAR = '4',
    SALVAR = '5',
    IMPORTAR = '6',
    EXIT = '0',
};

enum escolhasEdit{
    EDIT_MENU = 2,
    NOME = '1',
    SOBRENOME = '2',
    NOTA = '3',
};

typedef struct aluno {
    char nome[100], sobrenome[100];
    float *notas;
    int totalNotas;
} Aluno_t;


typedef struct registry {
    int qtdStuds;
    Aluno_t *alunos;
} Registry_t;

extern Registry_t reg;


typedef int stud_Index;

/* Funções de menu */
void menuActions();
void menuEditStudent();

/* Funções de adição/edição de reg.alunos */
void registerStudent();
void editStudent(stud_Index iAluno);
void editNomeGeneric(const char *prompt, char *field);
void editNome(stud_Index iAluno);
void editSobrenome(stud_Index iAluno);
void editNotas(stud_Index iAluno);

/* Funções para printar informações */
void printOptions(int menu);
void printOneStudInfo(stud_Index iAluno);
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
void incStudTotalNotas (int increment, stud_Index iAluno);
void increaseRegistrySize (int increment);
