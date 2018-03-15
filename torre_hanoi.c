#include <stdio.h>

int discos = 8;
#define torres 4

typedef struct Nodo_Pilha
{
    int elemento;
    struct Nodo_Pilha *prox;
}*NODOPTR;

NODOPTR pilha1=NULL;
NODOPTR pilha2=NULL;
NODOPTR pilha3=NULL;
NODOPTR pilha4=NULL;

NODOPTR Cria_Nodo( )
{
    NODOPTR p;
    p = (NODOPTR) malloc(sizeof(struct Nodo_Pilha));
    if(!p)
    {
        printf("Problemas na Alocação!!!");
        exit(0);
    }
    return p;
}
void push(int dado, NODOPTR *pilha)
{
    NODOPTR nodo;
    nodo= Cria_Nodo( );
    nodo->elemento = dado;
    nodo->prox = *pilha;
    *pilha = nodo;
}

NODOPTR *retorna_pilha(int i)
{
    if(i==1)
        return &pilha1;
    else if(i==2)
        return &pilha2;
    else if(i==3)
        return &pilha3;
    else
        return &pilha4;
}

int pop(NODOPTR *pilha)
{
    NODOPTR nodo;
    int elem;
    if(!*pilha)
        return -1;
    nodo = *pilha;
    elem = nodo->elemento;
    *pilha = nodo->prox;
    free(nodo);
    return elem;
}

int printp(NODOPTR *pilha)
{
    NODOPTR nodo, temp=NULL;
    int elem;
    if(!*pilha)
        return -1;

    nodo = *pilha;
    while(nodo!=NULL)
    {
        elem = nodo->elemento;
        push(elem,&temp);
        nodo = nodo->prox;
    }
    while(temp!=NULL)
    {
        elem = temp->elemento;
        printf(" %d ",elem);
        temp = temp->prox;
    }
}

void inicializa_torres()
{
    push(8,&pilha1);
    push(7,&pilha1);
    push(6,&pilha1);
    push(5,&pilha1);
    push(4,&pilha1);
    push(3,&pilha1);
    push(2,&pilha1);
    push(1,&pilha1);
}

int calcula_torre_temp(int orig,int dest)
{
    int i, tmp;
    for (i = 1; i < torres; i++)
        if (i != orig && i != dest)
            tmp = i;
    return tmp;
}

void print()
{
    int  t;
    for (t = 1 ; t <= torres; t++ )
    {
        printf("||");
        printp(retorna_pilha(t));
        printf("\n");
    }
    _sleep(100);
}

///Funcao Recursiva
void movetorre (int n, int orig, int dest,int *count)
{
    int temp = calcula_torre_temp(orig,dest);
    *count +=1;
    if (n==1)
    {
        printf("\nMover disco 1 da torre %d para a torre %d\n", orig, dest);
        push(pop(retorna_pilha(orig)),retorna_pilha(dest));
        print();
        return;
    }
    movetorre(n-1,orig,temp,count);
    printf("\nMover disco %d da torre %d para a torre %d\n", n, orig, dest);
    push(pop(retorna_pilha(orig)),retorna_pilha(dest));
    print();
    movetorre(n-1,temp,dest,count);
};

int main()
{
    printf("\t\t\t\tTORRE DE HANOI\n\n");
    int i,count = 0;
    inicializa_torres();
    movetorre(discos,1,torres,&count);
    printf("\nMovimentos: %d",count);
    return 0;
}
