typedef struct curso
{
    int codigoCurso;
    char nomeCurso[30];
    char centroCurso[4];
    struct lista *listaAlunos;
    struct curso *esq;
    struct curso *dir;
} Curso;

void imprimeArv (Curso *raiz);

Curso *freeNo (Curso *raiz, int codigoLocal);

Curso *removeCurso (Curso *raiz);

Curso *criaNoCurso (Curso *raiz, int codigoLocal, char nomeLocal[30], char centroLocal[5]);

Curso *insereCurso (Curso *raiz);