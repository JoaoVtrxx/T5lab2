#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct lista
{
    int matriculaAluno;
    char nomeAluno[30];
    int anoAluno;
    struct lista *prox;
} Lista;

typedef struct curso
{
    int codigoCurso;
    char nomeCurso[30];
    char centroCurso[4];
    Lista *listaAlunos;
    struct curso *esq;
    struct curso *dir;
} Curso;

Curso *freeNo (Curso *raiz, int codigoLocal)
{
    if (raiz == NULL)
    {   
        printf("Nao encontrado. \n");
        return NULL;
    }
    else if (raiz->codigoCurso > codigoLocal)
    {
        raiz->esq = freeNo (raiz->esq, codigoLocal);
    }
    else if (raiz->codigoCurso < codigoLocal)
    {
        raiz->dir = freeNo (raiz->dir, codigoLocal);
    }
    else
    {
        if (raiz->esq == NULL && raiz->dir == NULL)
        {
            free(raiz);
            return NULL;
        }
        else if(raiz->esq == NULL)
        {
            Curso *t = raiz;
            raiz = raiz->dir;
            free(t);
        }
        else if(raiz->dir == NULL){
            Curso *t = raiz;
            raiz = raiz->esq;
            free(t);
        }
        else
        {
            Curso *f = raiz->esq;
            while(f->dir != NULL)
            {
                f = f->dir;
            }
            raiz->codigoCurso = f->codigoCurso;
            f->codigoCurso = codigoLocal;
            raiz->esq = freeNo(raiz->esq, codigoLocal);
        }
    }

    return raiz;
}   

Curso *removeCurso (Curso *raiz)
{
    int codigoLocal;
    printf("Digite o codigo do curso que deseja remover: \n");
    scanf(" %d", &codigoLocal);
    raiz = freeNo(raiz, codigoLocal);

    return raiz;
}

void imprimeArv (Curso *raiz)
{
    if (raiz != NULL)
    {
        imprimeArv (raiz->esq);
        printf ("Codigo: %d\t", raiz->codigoCurso);
        printf ("Nome: %s\t", raiz->nomeCurso);
        printf ("Centro: %s\n", raiz->centroCurso);
        imprimeArv (raiz->dir);
    }
}

Curso *criaNoCurso (Curso *raiz, int codigoLocal, char nomeLocal[30], char centroLocal[4])
{
    
    if(raiz == NULL)
    {
        raiz = (Curso*)malloc(sizeof(Curso));
        raiz->codigoCurso = codigoLocal;
        strcpy(raiz->nomeCurso, nomeLocal);
        strcpy(raiz->centroCurso, centroLocal);
        raiz->listaAlunos = NULL;
        raiz->esq = raiz->dir = NULL;
    }
    else if (codigoLocal < raiz->codigoCurso)
    {
        raiz->esq = criaNoCurso (raiz->esq, codigoLocal, nomeLocal, centroLocal);
    }
    else
    {
        raiz->dir = criaNoCurso (raiz->dir, codigoLocal, nomeLocal, centroLocal);
    }
    
    return raiz;
}

Curso *insereCurso (Curso *raiz)
{
    int codigoLocal;
    char nomeLocal[30], centroLocal[4];

    printf ("Digite o codigo do curso: ");
    scanf ("%d", &codigoLocal);
    getchar ();
    printf ("Informe o nome do curso: ");
    fgets (nomeLocal, sizeof(nomeLocal), stdin);
    nomeLocal[strcspn(nomeLocal, "\n")] = '\0';
    
    printf ("Informe o centro do curso: ");
    fgets (centroLocal, sizeof(centroLocal), stdin);
    centroLocal[strcspn(centroLocal, "\n")] = '\0';

    raiz = criaNoCurso(raiz, codigoLocal, nomeLocal, centroLocal);

    return raiz;
}

Lista *insereLista(Lista *listaAlunos, int matriculaAlunoLocal, char nomeAlunoLocal[30], int anoAlunoLocal)
{
    Lista *novo = (Lista*) malloc(sizeof(Lista));
    novo->matriculaAluno = matriculaAlunoLocal;
    strcpy(novo->nomeAluno, nomeAlunoLocal);
    novo->anoAluno = anoAlunoLocal;

    Lista *ant = NULL;
    Lista *p = listaAlunos;

    while(p != NULL && p->matriculaAluno < matriculaAlunoLocal)
    {
        ant = p;
        p = p->prox;
    }

    if(ant == NULL)
    {
        novo->prox = listaAlunos;
        listaAlunos = novo;
    }
    else
    {
        novo->prox = ant->prox;
        ant->prox = novo;
    }
    
    return listaAlunos;
}

Curso *criaAluno(Curso *raiz, int codigoLocal)
{
    if(raiz == NULL)
    {
        printf("Nao encontrado. \n");
        return NULL;
    }
    else if (raiz->codigoCurso > codigoLocal)
    {
        raiz->esq = criaAluno (raiz->esq, codigoLocal);
    }
    else if (raiz->codigoCurso < codigoLocal)
    {
        raiz->dir = criaAluno (raiz->dir, codigoLocal);
    }
    else{
        int matriculaAlunoLocal;
        char nomeAlunoLocal[30];
        int anoAlunoLocal;

        printf("Digite a matricula do aluno: ");
        scanf(" %d", &matriculaAlunoLocal);

        printf("Digite o ano de ingresso do aluno: ");
        scanf(" %d", &anoAlunoLocal);

        getchar ();
        printf ("Informe o nome do aluno: ");
        fgets (nomeAlunoLocal, sizeof(nomeAlunoLocal), stdin);
        nomeAlunoLocal[strcspn(nomeAlunoLocal, "\n")] = '\0';

        raiz->listaAlunos = insereLista(raiz->listaAlunos, matriculaAlunoLocal, nomeAlunoLocal, anoAlunoLocal);
    }

    return raiz;
}

Curso *insereAluno(Curso *raiz)
{   
    int codigoLocal;

    printf("Digite o codigo do curso em que deseja inserir o aluno: \n");
    scanf(" %d", &codigoLocal);

    raiz = criaAluno(raiz, codigoLocal);

    return raiz;
}

void percorreArvore(Curso *raiz,  int codigoLocal)
{
    if(raiz == NULL)
    {
        printf("Nao encontrado. \n");
    }
    else if (raiz->codigoCurso > codigoLocal)
    {
        percorreArvore (raiz->esq, codigoLocal);
    }
    else if (raiz->codigoCurso < codigoLocal)
    {
        percorreArvore (raiz->dir, codigoLocal);
    }
    else{
        Lista *p = raiz->listaAlunos;

        if(p == NULL){
            printf("Lista vazia.\n");
        }
        else
        {
            while(p != NULL){
                printf("Nome: %s\n", p->nomeAluno);
                p = p->prox;
            }
        }
    }
}

void imprimeListaAlunos(Curso *raiz)
{
    int codigoLocal;

    printf("Digite o codigo do curso que deseja imprimir a lista de alunos: \n");
    scanf(" %d", &codigoLocal);

    percorreArvore(raiz, codigoLocal);
    
}

int main()
{   
    Curso *arv = NULL;

    arv = insereCurso (arv);
    arv = insereCurso (arv);
    // arv = insereCurso (arv);
    // arv = insereCurso (arv);
    imprimeArv (arv);
    // arv = removeCurso (arv);
    // imprimeArv (arv);
    // arv = removeCurso (arv);
    // imprimeArv (arv);
    // arv = removeCurso (arv);
    // imprimeArv (arv);
    // arv = removeCurso (arv);
    // imprimeArv (arv);
    // arv = removeCurso (arv);

    arv = insereAluno (arv);
    arv = insereAluno (arv);

    imprimeListaAlunos(arv);
    imprimeListaAlunos(arv);

    // imprimeArv (arv);

    return 0;
}
