#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "curso.h"
#include "lista.h"

void imprimeArv (Curso *raiz)
{
    if (raiz != NULL)
    {
        imprimeArv (raiz->esq);
        printf ("Codigo: %d", raiz->codigoCurso);
        printf ("\t\t\t\tNome: %s", raiz->nomeCurso);
        printf ("\t\t\t\tCentro: %s\n", raiz->centroCurso);
        imprimeArv (raiz->dir);
    }
}

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
    printf("Digite o codigo do curso que deseja remover: ");
    scanf(" %d", &codigoLocal);
    raiz = freeNo(raiz, codigoLocal);

    return raiz;
}

Curso *criaNoCurso (Curso *raiz, int codigoLocal, char nomeLocal[30], char centroLocal[5])
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
    char nomeLocal[30], centroLocal[5];

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
