#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "curso.h"
#include "lista.h"

void menu (Curso *arv)
{
    int opcao;
    while (1)
    {
        printf ("Digite a opcao desejada\n");
        printf ("1) Inserir curso\n2) Excluir curso\n3) Imprimir cursos\n4) Inserir aluno\n5) Excluir aluno\n");
        printf ("6) Imprimir alunos\n7) Imprimir vinculos\n8) Encerrar programa\n");
        scanf ("%d", &opcao);

        switch (opcao)
        {
            case 1:
                arv = insereCurso (arv);
                break;
            case 2:
                arv = removeCurso (arv);
                break;
            case 3:
                imprimeArv (arv);
                break;
            case 4:
                arv = insereAluno (arv);
                break;
            case 5:
                arv = removeAluno (arv);
                break;
            case 6:
                imprimeListaAlunos(arv);
                break;
            case 7:
                imprimeVinculos (arv);
                break;
            case 8:
                free (arv);
                return;
        }
    }
}

int main()
{   
    Curso *arv = NULL;

    menu (arv);

    return 0;
}