#include<stdio.h>

typedef struct Bloco
{
    int dado;
    struct Bloco *prox;
} Nodo;

void inicializa_lista(Nodo **N)
{
    *N = NULL;
}

Nodo * Cria_Nodo()
{
    Nodo *p;
    p = (Nodo *) malloc(sizeof(Nodo));
    if(!p)
    {
        printf("Problema de alocação");
        exit(0);
    }
    return p;
}

void insere_fim_lista(Nodo **N, int dado)
{
    Nodo *novo, * aux;
    novo = Cria_Nodo();
    novo->dado = dado;
    novo->prox = NULL;
    if(*N == NULL)
        *N = novo;
    else
    {
        aux = *N;
        while(aux->prox != NULL)
        {
            aux = aux->prox;
        }
        aux->prox = novo;
    }
}

void insere_inicio_lista(Nodo **N, int dado)
{
    Nodo *novo;
    novo = Cria_Nodo();
    novo->dado = dado;
    novo->prox = *N;
    *N = novo;
}

int insere_ordenado(Nodo **N, int dado)
{
    Nodo *aux;
    aux=*N;
    if((*N==NULL)||(dado<aux->dado))
        return 0;

    while(aux->prox != NULL)
    {
        if(dado<(aux->prox->dado))
            break;
        aux = aux->prox;
    }

    if(dado>aux)
    {
        return-1;
    }

    Nodo *n=Cria_Nodo();
    n->dado=dado;
    n->prox=aux->prox;
    aux->prox=n;
    return 1;
}

int remove_inicio_lista(Nodo **N, int *dado)
{
    Nodo *aux;
    if(*N == NULL)
        return 0;
    else
    {
        *dado = (*N)->dado;
        aux = (*N)->prox;
        free(*N);
        *N = aux;
    }
    return 1;
}

int remove_fim_lista(Nodo **N, int *dado)
{
    Nodo *aux,*hd;
    if(*N == NULL) //verifica se a lista está vazia
        return 0;
    else
    {
        hd=aux=*N;
        while(aux->prox!=NULL)
        {
            hd=aux;
            aux=aux->prox;
        }
        *dado = aux->dado;
        free(aux);
        hd->prox=NULL;

    }
    return 1;
}

int remove_lista(Nodo **N, int dado)
{
    Nodo *aux,*sv;
    if(*N == NULL) //verifica se a lista está vazia
        return 0;



    aux=sv=*N;
    if(aux->dado==dado)
    {
        return -2;
    }
    while(aux->prox!=NULL&&aux->prox->dado!=dado)
    {
        //printf("--- %d --: ",aux->dado);
        aux=aux->prox;

    }

    if(aux->prox==NULL)
    {
        return -1;
    }
    sv=aux->prox;
    aux->prox=aux->prox->prox;
    free(sv);
    return 1;
}

void remove_propria_lista(Nodo **N)
{
    if(*N != NULL)
    {
        Nodo *aux;
        while(aux!=NULL)
        {
            aux= (*N)->prox;
            free(*N);
            *N=aux;
        }
    }
}
void imprime_lista_ecandeada(Nodo *N)
{
    Nodo *aux;
    if(N == NULL)
        printf("\n A lista está vazia!!");
    else
    {
        for(aux = N; aux != NULL; aux = aux->prox)
            printf(" %d ", aux->dado);
    }
}

int main()
{
    Nodo *MyList;
    int menu, valor, loop = 0;
    inicializa_lista(&MyList);
    printf("\tLista Encadeada\n");
    printf(" 1 - Insere no inicio da lista \n 2 - Insere no fim da lista \n 3 - Insere ordenado na lista \n 4 - Exclui do inicia da lista \n 5 - Exclui do fim da lista \n 6 - Exclui um elemento qualquer da lista \n 7 - Imprime os dados da lista \n 8 - Sair");
    while(loop==0)
    {
        int controller;
        printf("\n\nEscolha sua opcao: ");
        scanf("%d", &menu);
        switch(menu)
        {
        case 1:
            printf("\nEntre com o valor: ");
            scanf("%d", &valor);
            insere_inicio_lista(&MyList, valor);
            break;
        case 2:
            printf("\nEntre com o valor: ");
            scanf("%d", &valor);
            insere_fim_lista(&MyList, valor);
            break;
        case 3:
            printf("\nInforme o valor a ser inserido: ");
            scanf("%d", &valor);
            controller=insere_ordenado(&MyList, valor);
            if(controller==0)
                insere_inicio_lista(&MyList, valor);
            if(controller==-1)
                insere_fim_lista(&MyList, valor);
            break;
        case 4:
            if(remove_inicio_lista(&MyList, &valor) == 0)
                printf("\nA lista está vazia!!");
            else
                printf("\nO valor excluido do inicio da lista foi: %d", valor);
            break;
        case 5:
            if(remove_fim_lista(&MyList, &valor) == 0)
                printf("\nA lista está vazia!!");
            else
                printf("\nO valor excluido do fim da lista foi: %d", valor);
            break;
        case 6:
            printf("\nInforme o valor a ser excluido da lista:");
            scanf("%d", &valor);
            controller=remove_lista(&MyList, valor);
            if(controller== 0)
            {
                printf("\nA lista está vazia!!");
                break;
            }
            if(controller==-1)
            {
                printf("\nO valor não foi encontrado!!");
                break;
            }
            if(controller==-2)
                remove_inicio_lista(&MyList,&valor);
            break;
        case 7:
            imprime_lista_ecandeada(MyList);
            break;
        case 8:
            loop = 1;
            remove_propria_lista(&MyList);
            printf("\n\n\nEncerrando processo!");
            break;
        default:
            printf("\nOpcao invalida");
        }
    }
    return 0;
}
