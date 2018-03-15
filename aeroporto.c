#include <stdio.h>
#include <windows.h>
typedef struct Bloco
{
    char nom_voo[30];///nome do voo
    int identificador;
    int num_pas;///numero de passageiros
    int capacidade;///capacidade maxima do voo
    char origem[30];///origem do voo
    char destino[30];///destino do voo
    struct Bloco *prox;
} Nodo;

void inicializa_fila(Nodo **N)///inicializa a fila
{
    *N = NULL;
}

Nodo * Cria_Nodo() ///aloca memória para o nodo
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

void remove_propria_fila(Nodo **N)
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

void insere_fim_fila(Nodo **N,Nodo *TEMP)
{
    Nodo *novo, * aux;
    if(TEMP==NULL)
    {
        novo = Cria_Nodo();
        ///dados aviao
        char nome[30];
        int passageiros, cap,iden;
        char org[30];
        char dst[30];
        fflush(stdin);
        printf("\nDigite o nome do voo:\n");
        gets(nome);
        printf("\nInforme identificador:\n");
        scanf("%d", &iden);
        printf("\nInforme numero de passageiros a bordo:\n");
        scanf("%d", &passageiros);
        printf("\nInforme capacidade do voo:\n");
        scanf("%d", &cap);
        fflush(stdin);
        printf("\nOrigem do voo:\n");
        gets(org);
        fflush(stdin);
        printf("\nDestino do voo:\n");
        gets(dst);

        sprintf(novo->nom_voo,"%s",nome);
        novo->num_pas = passageiros;
        novo->capacidade = cap;
        novo->identificador = iden;
        sprintf(novo->origem,"%s",org);
        sprintf(novo->destino,"%s",dst);
    }
    else
        novo = TEMP;
        novo->prox = NULL;
    if(*N == NULL)
        *N = novo;
    else
    {
        aux = *N;
        while(aux->prox != NULL)
            aux = aux->prox;
        aux->prox = novo;
    }
}

int remove_inicio_fila(Nodo **N)
{
    Nodo *aux;
    if(*N == NULL) ///verifica se a fila está vazia
        return 0;
    else
    {
        aux = (*N)->prox;
        free(N);
        *N = aux;
    }
}

void imprime_fila_encadeada(Nodo *N)
{
    int tam=1;
    Nodo *aux;
    if(N == NULL)
        printf("\n A fila está vazia!!");
    else
    {
        for(aux = N; aux != NULL; aux = aux->prox)
        {
            printf("\nOrdem na fila: %d\nNome do voo: %s\nIdentificador do voo: %d\nPassageiros a bordo: %d\nCapacidade de voo: %d\nOrigem: %s\nDestino: %s\n\n",tam,aux->nom_voo,aux->identificador,aux->num_pas,aux->capacidade,aux->origem,aux->destino);
            tam++;
        }
    }
}

Nodo * imprime_primeiro(Nodo *N)
{
    Nodo *aux;
    if(N == NULL)
    {
        printf("\n A fila está vazia!!");
        return NULL;
    }
    else
    {
        aux = N;
        printf("\nNome do voo: %s\nIdentificador do voo: %d\nPassageiros a bordo: %d\nCapacidade de voo: %d\nOrigem: %s\nDestino: %s\n\n",aux->nom_voo,aux->identificador,aux->num_pas,aux->capacidade,aux->origem,aux->destino);
        return aux;
    }
}

int filar_tamanho_fila(Nodo *N)
{
    int tam=0;
    Nodo *aux;
    if(N == NULL)
        printf("\n A fila está vazia!!");
    else
    {
        for(aux = N; aux != NULL; aux = aux->prox)
            tam++;
    }
    return tam;
}

void anim_pousa()
{
    Sleep(100);
    system("@cls||clear");
    printf("\n\n      |\n");
    printf("  --=oOo=--\n\n\n");
    printf("-------------");
    Sleep(1100);
    system("@cls||clear");
    printf("\n\n      |\n");
    printf("  --=oOo=--\n\n");
    printf("-------------");
    Sleep(1100);
    system("@cls||clear");
    printf("\n\n      |\n");
    printf("  --=oOo=--\n");
    printf("-------------");
    Sleep(1100);
    system("@cls||clear");
    printf("\n\n      |\n");
    printf("  --=oOo=--\n");
    printf("-------------");
    system("@cls||clear");
}

void anim_decola()
{
    Sleep(100);
    system("@cls||clear");
    printf("\n\n      |\n");
    printf("  --=oOo=--\n");
    printf("-------------");
    Sleep(1100);
    system("@cls||clear");
    printf("\n\n      |\n");
    printf("  --=oOo=--\n\n");
    printf("-------------");
    Sleep(1100);
    system("@cls||clear");
    printf("\n\n      |\n");
    printf("  --=oOo=--\n\n\n");
    printf("-------------");
    Sleep(1100);
    system("@cls||clear");
    printf("\n\n      |\n");
    printf("  --=oOo=--\n\n\n\n");
    printf("-------------");
    system("@cls||clear");
}

int main()
{
    Nodo *fila_pouso, *fila_decolagem, *aux;
    int menu, esc_fila;
    printf("\n\tAeroporto\n");
    inicializa_fila(&fila_pouso);
    inicializa_fila(&fila_decolagem);
    do
    {
        printf("\n1 - Inclui voo na fila de pouso \n2 - Inclui voo na fila de decolagem \n3 - Numero de voos esperandop/ POUSAR \n4 - Numero de voos esperando p/ DECOLAR \n5 - Autorizar primeiro voo da fila de pouso \n6 - Autorizar primeiro voo da fila de decolagem \n7 - Imprime fila de pouso\n8 - Imprime fila de decolagem \n9 - Primeiro voo na fila de pouso \n10 - Primeiro voo na fila de decolagem \n0 - Sair\n");
        scanf("%d", &menu);
        switch(menu)
        {
        case 0:
            printf("\n\n\nSAINDO DO PROGRAMA!");
            remove_propria_fila(&fila_pouso);
            remove_propria_fila(&fila_decolagem);
            break;
        case 1:
            printf("\nInserindo voo na fila de pouso:\n");
            insere_fim_fila(&fila_pouso,NULL);
            break;
        case 2:
            printf("\nInserindo voo na fila de decolagem:\n");
            insere_fim_fila(&fila_decolagem,NULL);
            break;
        case 3:
            printf("\nNumero de voos esperando para pousar: %d\n",filar_tamanho_fila(fila_pouso));
            break;
        case 4:
            printf("\nNumero de voos esperando para decolar: %d\n",filar_tamanho_fila(fila_decolagem));
            break;
        case 5:
            printf("\nAutorizando pouso do voo\n");
            aux = imprime_primeiro(fila_pouso);
            Sleep(1500);
            remove_inicio_fila(&fila_pouso);
            insere_fim_fila(&fila_decolagem,aux);
            anim_pousa();
            break;
        case 6:
            printf("\nAutorizando decolagem do voo\n");
            aux = imprime_primeiro(fila_decolagem);
            Sleep(1500);
            remove_inicio_fila(&fila_decolagem);
            anim_decola();
            break;
        case 7:
            imprime_fila_encadeada(fila_pouso);
            break;
        case 8:
            imprime_fila_encadeada(fila_decolagem);
            break;
        case 9:
            aux = imprime_primeiro(fila_pouso);
            break;
        case 10:
            aux = imprime_primeiro(fila_decolagem);
            break;
        default:
            printf("\nOpcao Invalida!!!");
        }
    }
    while(menu != 0);
    return 0;
}
