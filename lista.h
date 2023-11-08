typedef struct lista
{
    int matriculaAluno;
    char nomeAluno[30];
    int anoAluno;
    struct lista *prox;
} Lista;

Lista *insereLista (Lista *listaAlunos, int matriculaAlunoLocal, char nomeAlunoLocal[30], int anoAlunoLocal);

Curso *criaAluno(Curso *raiz, int codigoLocal);

Curso *excluirAluno (Curso *raiz, int codigoLocal);

Curso *removeAluno (Curso *raiz);

Curso *insereAluno (Curso *raiz);

void percorreArvore(Curso *raiz,  int codigoLocal);

void imprimeListaAlunos(Curso *raiz);

void imprimeVinculos (Curso *raiz);