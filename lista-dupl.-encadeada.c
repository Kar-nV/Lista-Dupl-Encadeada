// inclui as bibliotecas
#include <stdio.h>
#include <stdlib.h>

// define uma estrutura do no e ponteiros proximo e anterior

typedef struct no
{
    int valor;
    struct no *proximo;
    struct no *anterior;
} No;

// procedure para inserir no inicio
void inserir_no_inicio(No **lista, int num)
{
    No *novo = malloc(sizeof(No));

    if (novo)
    {
        novo->valor = num;
        novo->proximo = *lista; // inicio da lista
        novo->anterior = NULL;  // primeiro no
        if (*lista)
            (*lista)->anterior = novo; // verifica se existe algum outro numero na lista
        *lista = novo;
    }
    else
        printf("Erro ao alocar memoria!\n");
}

// procedure para inserção ao fim
void inserir_no_fim(No **lista, int num)
{
    No *aux, *novo = malloc(sizeof(No));

    if (novo)
    {
        novo->valor = num;
        novo->proximo = NULL;

        // primeiro no?
        if (*lista == NULL)
        {
            *lista = novo;
            novo->anterior = NULL; // unico no da lista
        }
        else
        {
            aux = *lista;
            while (aux->proximo)
                aux = aux->proximo;
            aux->proximo = novo;
            novo->anterior = aux;
        }
    }
    else
        printf("Erro ao alocar memoria!\n");
}

// procedure para inserção no meio
void inserir_no_meio(No **lista, int num, int ant)
{
    No *aux, *novo = malloc(sizeof(No));

    if (novo)
    {
        novo->valor = num;
        // e o primeiro?
        if (*lista == NULL)
        {
            novo->proximo = NULL;
            novo->anterior = NULL;
            *lista = novo;
        }
        else
        {
            aux = *lista;
            while (aux->valor != ant && aux->proximo) // verifica se o valor e diferente
                aux = aux->proximo;
            novo->proximo = aux->proximo;
            aux->proximo->anterior = novo; // proximo no com o novo no
            novo->anterior = aux;
            aux->proximo = novo;
        }
    }
    else
        printf("Erro ao alocar memoria!\n");
}

void inserir_ordenado(No **lista, int num)
{
    No *aux, *novo = malloc(sizeof(No));

    if (novo)
    {
        novo->valor = num;
        // a lista esta vazia?
        if (*lista == NULL)
        {
            novo->proximo = NULL;
            novo->anterior = NULL;
            *lista = novo;
        } // e um numero menor?
        else if (novo->valor < (*lista)->valor)
        {
            novo->proximo = *lista;
            (*lista)->anterior = novo; // ponteiro para o no anterior recebe o novo no
            *lista = novo;
        }
        else
        {
            aux = *lista;
            while (aux->proximo && novo->valor > aux->proximo->valor)
                aux = aux->proximo;
            novo->proximo = aux->proximo;
            aux->proximo->anterior = novo;
            novo->anterior = aux;
            aux->proximo = novo;
        }
    }
    else
        printf("Erro ao alocar memoria!\n");
}

// procedure para remocao de no
No *remover(No **lista, int num)
{

    No *aux, *remover = NULL;

    if (*lista)
    {
        if ((*lista)->valor == num)
        {
            remover = *lista;
            *lista = remover->proximo;
            if (*lista)
                (*lista)->anterior = NULL;
        }
        else
        {
            aux = *lista;
            while (aux->proximo && aux->proximo->valor != num)
                aux = aux->proximo;
            if (aux->proximo)
            {
                remover = aux->proximo;
                aux->proximo = remover->proximo;
                if (aux->proximo)
                    aux->proximo->anterior = aux;
            }
        }
    }
    return remover;
}

// procedure que busca do inicio ao fim
No *buscar(No **lista, int num)
{
    No *aux, *no = NULL;

    aux = *lista;
    while (aux && aux->valor != num)
        aux = aux->proximo;
    if (aux)
        no = aux;
    return no;
}

void imprimir(No *no)
{
    printf("\n\tLista: ");
    while (no)
    {
        printf("%d ", no->valor);
        no = no->proximo;
    }
    printf("\n\n");
}

No *ultimo(No **lista)
{
    No *aux = *lista; // recebe o inicio da lista e percorre ate o final da lista
    while (aux->proximo)
        aux = aux->proximo;
    return aux;
}

void imprimirContrario(No *no) // imprime do final ate o começo da lista
{
    printf("\n\tLista: ");
    while (no)
    {
        printf("%d ", no->valor);
        no = no->proximo;
    }
    printf("\n\n");
}

int main()
{

    int opcao, valor, anterior;
    No *removido, *lista = NULL;

    do
    {
        printf("\n\t0 - Sair\n\t1 - InserirI\n\t2 - InserirF\n\t3 - InserirM\n\t4 - InserirO\n\t5 - Remover\n\t6 - Imprimir\n\t7 - Buscar\n\t8 - ImprimirC\n"); // menu de escolhas dos casos
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            scanf("%d", &valor);
            inserir_no_inicio(&lista, valor);
            break;
        case 2:
            printf("Digite um valor: ");
            scanf("%d", &valor);
            inserir_no_fim(&lista, valor);
            break;
        case 3:
            printf("Digite um valor e o valor de referencia: ");
            scanf("%d%d", &valor, &anterior);
            inserir_no_meio(&lista, valor, anterior);
            break;
        case 4:
            printf("Digite um valor: ");
            scanf("%d", &valor);
            inserir_ordenado(&lista, valor);
            break;
        case 5:
            printf("Digite um valor a ser removido: ");
            scanf("%d", &valor);
            removido = remover(&lista, valor);
            if (removido)
            {
                printf("Elemento a ser removido: %d\n", removido->valor);
                free(removido);
            }
            else
                printf("Elemento inexistente!\n");
            break;
        case 6:
            imprimir(lista);
            break;
        case 7:
            printf("Digite um valor a ser buscado: ");
            scanf("%d", &valor);
            removido = buscar(&lista, valor);
            if (removido)
                printf("Elemento encontrado: %d\n", removido->valor);
            else
                printf("Elemento nao encontrado!\n");
            break;
        case 8:
            imprimirContrario(ultimo(&lista));
            break;
        default:
            if (opcao != 0)
                printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}