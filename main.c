#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct lista
{
    int matricula;
    char nome[30];
    int ano;
    struct lista *prox;
} Lista;

typedef struct curso
{
    int codigo;
    char nome[30];
    char centro[4];
    Lista *lista;
    struct curso *esq;
    struct curso *dir;
} Curso;

Curso *freeNo (Curso *raiz, int codigoLocal)
{
    if (raiz == NULL)
    {
        return NULL;
    }
    else if (raiz->codigo > codigoLocal)
    {
        raiz->esq = freeNo (raiz->esq, codigoLocal);
    }
    else if (raiz->codigo < codigoLocal)
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
            raiz->codigo = f->codigo;
            f->codigo = codigoLocal;
            raiz->esq = freeNo(raiz->esq, codigoLocal);
        }
    }

    return raiz;
}   

Curso *remover (Curso *raiz)
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
        printf ("Codigo: %d\t", raiz->codigo);
        printf ("Nome: %s\t", raiz->nome);
        printf ("Centro: %s\n", raiz->centro);
        imprimeArv (raiz->dir);
    }
}

Curso *criaNo (Curso *raiz, int codigoLocal, char nomeLocal[30], char centroLocal[4])
{
    
    if(raiz == NULL)
    {
        raiz = (Curso*)malloc(sizeof(Curso));
        raiz->codigo = codigoLocal;
        strcpy(raiz->nome, nomeLocal);
        strcpy(raiz->centro, centroLocal);
        raiz->lista = NULL;
        raiz->esq = raiz->dir = NULL;
    }
    else if (codigoLocal < raiz->codigo)
    {
        raiz->esq = criaNo (raiz->esq, codigoLocal, nomeLocal, centroLocal);
    }
    else
    {
        raiz->dir = criaNo (raiz->dir, codigoLocal, nomeLocal, centroLocal);
    }
    
    return raiz;
}

Curso *insere (Curso *raiz){
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

    raiz = criaNo(raiz, codigoLocal, nomeLocal, centroLocal);

    return raiz;
}


int main()
{   
    Curso *arv = NULL;
    Lista *lista = NULL;

    arv = insere (arv);
    arv = insere (arv);
    arv = insere (arv);
    arv = insere (arv);
    imprimeArv (arv);
    arv = remover (arv);
    imprimeArv (arv);
    arv = remover (arv);
    imprimeArv (arv);
    arv = remover (arv);
    imprimeArv (arv);
    arv = remover (arv);
    imprimeArv (arv);
    arv = remover (arv);
    imprimeArv (arv);

    return 0;
}