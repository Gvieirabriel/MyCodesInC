#include <stdio.h>

#define MAX_VETOR 5

//Lista
typedef struct Vetor
{
    int dados[MAX_VETOR];
    int inicio, fim;
} Tipo_Lista;


//Funcoes da lista
int inicializa_lista(Tipo_Lista *v)
{
    printf("\nLista inicializada");
    v->fim = 0;
    v->inicio = 0;
    return 0;
}

int insere_fim_lista(Tipo_Lista *v, int dado)
{
    if(v->fim < MAX_VETOR)
    {
        v->dados[v->fim] = dado;
        (v->fim)++;
        printf("\nElemento inserido no final da lista!");
        return 1;
    }
    printf("\nNao se pode inserir pois a lista esta cheia!");
    return 0;
}

int insere_ordenado(Tipo_Lista *v, int dado)
{
    int j,i,temp=0;
    if(v->fim==0)
    {
        insere_inicio_lista(v,dado);
        return 1;
    }
    else
    {
        for(i=v->fim-1; i >= 0; i--)
            if(i==v->fim-1&&dado>v->dados[i])
            {
                insere_fim_lista(v,dado);
                return 1;
            }
            else if(dado > v->dados[i])
                temp = i;
            else if(i==0&&dado>=v->dados[i])
            {
                insere_inicio_lista(v,dado);
                return 1;
            }
        if(v->fim < MAX_VETOR&&temp!=0)
        {
            for(j=v->fim; j>temp; j--)
                v->dados[j] = v->dados[j-1];
            v->dados[temp] = dado;
            (v->fim)++;
            printf("\nElemento inserido!");
            return 1;
        }
    }
    printf("\nNao se pode inserir pois a lista esta cheia!");
    return 0;
}

int insere_inicio_lista(Tipo_Lista *v, int dado)
{
    int i = v->fim;
    if(v->fim < MAX_VETOR)
    {
        for(i; i>0; i--)
            v->dados[i] = v->dados[i-1];
        v->dados[v->inicio] = dado;
        (v->fim)++;
        printf("\nElemento inserido no inicio da lista!");
        return 1;
    }
    else
    {
        printf("\nNao se pode inserir pois a lista esta cheia!");
    }
    return 0;
}

int exclui_fim_lista(Tipo_Lista *v)
{
    (v->fim)--;
    printf("\nUltimo elemento Excluido!");
    return 0;
}

int exclui_inicio_lista(Tipo_Lista *v)
{
    int i = 0;
    int temp = v->fim;
    for(i; i<(temp-1); i++)
        v->dados[i] = v->dados[i+1];
    (v->fim)--;
    printf("\nPrimeiro elemento Excluido!");
    return 0;
}

int exclui_elemento(Tipo_Lista *v, int dado)
{
    int i, temp;
    temp = busca_lista(v,dado);
    if(temp==4)
    {
        exclui_fim_lista(v);
        return 1;
    }
    if(temp!=-1)
    {
        for(i=temp; i < v->fim-1; i++)
            v->dados[i] = v->dados[i+1];
        (v->fim)--;
        printf("\nElemento %d excluido!",dado);
        return 1;
    }
    else
    {
        printf("\nElemento nao encontrado!",dado);
        return 0;
    }
}

int imprime_lista(Tipo_Lista V)
{
    int i;
    printf("\n\t");
    if(V.fim != 0)
    {
        for(i=0; i < V.fim; i++)
            printf(" %d ", V.dados[i]);
        return 1;
    }
    printf("\n");
    return 0;
}

int busca_lista(Tipo_Lista *v, int dado)
{
    int i, temp,achou;
    temp=achou=0;
    for(i=0; i < v->fim; i++)
    {
        if(v->dados[i] == dado)
        {
            temp = i;
            achou = 1;
            break;
        }
    }
    if(achou)
        return temp;
    return -1;
}

int main()
{
    Tipo_Lista lista;
    int operacao, entrada,inicial, controle = 1;
    inicial = 0;
    printf("\tLista linear Estatica\n");
    printf("\n 1 - Inicializa lista \n 2 - Insere no inicio da lista \n 3 - Insere no fim da lista \n 4 - Insere ordenado na lista \n 5 - Exclui do inicia da lista \n 6 - Exclui do fim da lista \n 7 - Exclui um elemento qualquer da lista \n 8 - Imprime os dados da lista \n 9 - Sair");
    while(controle==1)
    {
        printf("\n\nEscolha sua opcao: ");
        scanf("%d",&operacao);
        if(inicial==0)
        {
            while(operacao!=1)
            {
                printf("\nNecessario iniciar a lista primeiro!");
                printf("\n\nEscolha sua opcao: ");
                scanf("%d",&operacao);
            }
            inicial = 1;
        }
        switch( operacao )
        {
        case 1:
            inicializa_lista(&lista);
            break;
        case 2:
            printf("\nEntre com o valor: ");
            scanf("%d",&entrada);
            insere_inicio_lista(&lista,entrada);
            break;
        case 3:
            printf("\nEntre com o valor: ");
            scanf("%d",&entrada);
            insere_fim_lista(&lista,entrada);
            break;
        case 4:
            printf("\nEntre com o valor: ");
            scanf("%d",&entrada);
            insere_ordenado(&lista,entrada);
            break;
        case 5:
            exclui_inicio_lista(&lista);
            break;
        case 6:
            exclui_fim_lista(&lista);
            break;
        case 7:
            printf("\nEntre com o valor: ");
            scanf("%d",&entrada);
            exclui_elemento(&lista,entrada);
            break;
        case 8:
            imprime_lista(lista);
            break;
        case 9:
            controle = 0;
            break;
        default:
            printf("Você digitou uma operacao invalida!");
        }
    }
    return 0;
}
