#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "curso.h"
#include "lista.h"

Lista *insereLista (Lista *listaAlunos, int matriculaAlunoLocal, char nomeAlunoLocal[30], int anoAlunoLocal)
{
    Lista *novo = (Lista*)malloc(sizeof(Lista));
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
        printf("Nao encontrado.\n");
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

Curso *excluirAluno (Curso *raiz, int codigoLocal)
{
    if (raiz == NULL)
    {
        printf("Nao encontrado.\n");
        return NULL;
    }
    else if (raiz->codigoCurso > codigoLocal)
    {
        raiz->esq = excluirAluno (raiz->esq, codigoLocal);
    }
    else if (raiz->codigoCurso < codigoLocal)
    {
        raiz->dir = excluirAluno (raiz->dir, codigoLocal);
    }
    else
    {
        int matriculaLocal;
        percorreArvore (raiz, codigoLocal);
        printf ("Digite a matricula do aluno que deseja remover: ");
        scanf ("%d", &matriculaLocal);
        Lista *p = raiz->listaAlunos;
        Lista *ant = NULL;
        
        while(p != NULL && p->matriculaAluno != matriculaLocal)
        {
            ant = p;
            p = p->prox;
        }
        if (p == NULL)
        {
            printf ("Aluno nao encontrado.\n");
        }
        else
        {
            if (ant == NULL)
            {
                raiz->listaAlunos = p->prox;
            }
            else
            {
                ant->prox = p->prox;
            }
            free (p);
        }
    }
    return raiz;
}

Curso *removeAluno (Curso *raiz)
{
    int codigoLocal;

    printf("Digite o codigo do curso em que deseja remover o aluno: ");
    scanf("%d", &codigoLocal);

    raiz = excluirAluno(raiz, codigoLocal);

    return raiz;
}

Curso *insereAluno (Curso *raiz)
{   
    int codigoLocal;

    printf("Digite o codigo do curso em que deseja inserir o aluno: ");
    scanf("%d", &codigoLocal);

    raiz = criaAluno(raiz, codigoLocal);

    return raiz;
}

void percorreArvore(Curso *raiz,  int codigoLocal)
{
    if(raiz == NULL)
    {
        printf("Nao encontrado.\n");
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

        if(p == NULL)
        {
            printf("Lista vazia.\n");
        }
        else
        {
            while(p != NULL)
            {
                printf("Nome: %s\t\t\t\t\tMatricula: %d\n", p->nomeAluno, p->matriculaAluno);
                p = p->prox;
            }
        }
    }
}


void imprimeListaAlunos(Curso *raiz)
{
    int codigoLocal;

    printf("Digite o codigo do curso que deseja imprimir a lista de alunos: ");
    scanf("%d", &codigoLocal);

    percorreArvore(raiz, codigoLocal);
}

void imprimeVinculos (Curso *raiz)
{
    if (raiz != NULL)
    {
        imprimeVinculos	(raiz->esq);
        printf ("Codigo: %d\t\t\t\t\t", raiz->codigoCurso);
        printf ("Nome: %s\t\t\t\t\t", raiz->nomeCurso);
        printf ("Centro: %s\n", raiz->centroCurso);

        printf ("Alunos matriculados em %s: \n", raiz->nomeCurso);
        Lista *p = raiz->listaAlunos;
        if(p == NULL)
        {
            printf("Lista vazia.\n");
        }
        else
        {
            while(p != NULL)
            {
                printf("Nome: %s\t\t\t\t\tMatricula: %d\n", p->nomeAluno, p->matriculaAluno);
                p = p->prox;
            }
            printf ("\n");
        }
        imprimeVinculos (raiz->dir);
    }
}