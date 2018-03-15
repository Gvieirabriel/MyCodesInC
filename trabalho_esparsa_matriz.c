#include<stdio.h>

typedef struct Bloco
{
    float dado;
    int lin, col;
    struct Bloco *prox;
} Matriz_Esparsa;

void inicializa_lista(Matriz_Esparsa **N)
{
    *N = NULL;
}

Matriz_Esparsa * Cria_Matriz_Esparsa()
{
    Matriz_Esparsa *p;
    p = (Matriz_Esparsa *) malloc(sizeof(Matriz_Esparsa));
    if(!p)
    {
        printf("Problema de alocacao");
        exit(0);
    }
    return p;
}

void insere_fim_lista(Matriz_Esparsa **N, float dado, int lin, int col)
{
    Matriz_Esparsa *novo, * aux;
    novo = Cria_Matriz_Esparsa();
    novo->dado = dado;
    novo->lin=lin;
    novo->col=col;
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

void remove_propria_lista(Matriz_Esparsa **N)
{
    if(*N != NULL)
    {
        Matriz_Esparsa *aux;
        while(aux!=NULL)
        {
            aux= (*N)->prox;
            free(*N);
            *N=aux;
        }
    }
}

float busca_valor(Matriz_Esparsa *N, int lin, int col)
{
    Matriz_Esparsa *aux;
    for(aux = N; aux != NULL; aux = aux->prox)
        if(aux->lin==lin&&aux->col==col)
            return aux->dado;
    return 0;
}

Matriz_Esparsa *entra_matriz(int *lin, int *col)
{
    Matriz_Esparsa *result;
    inicializa_lista(&result);
    int valor_lin, valor_col, loop;
    float valor;
    printf("\nEntre com a qtd de linhas: ");
    scanf("%d", lin);
    printf("\nEntre com a qtd de colunas: ");
    scanf("%d", col);
    printf("\n\nSua matriz possui um valor diferente de zero?(n=0): ");
    scanf("%d", &loop);
    while(loop!=0)
    {
        do
        {
            printf("\nEntre com o valor: ");
            scanf("%f", &valor);
        }
        while(valor==0);
        printf("\nEntre com a linha: ");
        scanf("%d", &valor_lin);
        printf("\nEntre com a coluna: ");
        scanf("%d", &valor_col);
        if(busca_valor(result,valor_lin,valor_col)==0)
            if((valor_lin>0&&valor_lin<=*lin)&&(valor_col>0&&valor_col<=*col))
                insere_fim_lista(&result, valor, valor_lin, valor_col);
            else
                printf("\nLinha/Coluna invalida!");
        else
            printf("\nPosicao ja possui valor!");
        printf("\n\nSua matriz possui um valor diferente de zero?(n=0): ");
        scanf("%d", &loop);
    }
    return result;
}


void imprime_diagonal_principal(Matriz_Esparsa *N, int lin, int col)
{
    int i,j;
    for(i=1; i<=lin; i++)
    {
        for(j=1; j<=col; j++)
        {
            printf("  ");
            if(i==j)
                if(busca_valor(N,i,j)!=0)
                    printf(" %.1f ", busca_valor(N,i,j));
        }
        printf("\n");
    }
}


void imprime_matriz(Matriz_Esparsa *N, int lin, int col)
{
    int i,j;
    for(i=1; i<=lin; i++)
    {
        for(j=1; j<=col; j++)
            printf(" %.1f ", busca_valor(N,i,j));
        printf("\n");
    }
}

void matriz_transposta(Matriz_Esparsa *N, int lin, int col)
{
    int i,j;
    for(i=1; i<=col; i++)
    {
        for(j=1; j<=lin; j++)
            printf(" %.1f ", busca_valor(N,j,i));
        printf("\n");
    }
}

Matriz_Esparsa * soma_matriz(Matriz_Esparsa *M1,Matriz_Esparsa *M2, int lin, int col)
{
    int i,j;
    Matriz_Esparsa *result;
    inicializa_lista(&result);
    for(i=1; i<=lin; i++)
        for(j=1; j<=col; j++)
            if((busca_valor(M1,i,j))+(busca_valor(M2,i,j)!=0))
                insere_fim_lista(&result,(busca_valor(M1,i,j))+(busca_valor(M2,i,j)),i,j);
    return result;
}

Matriz_Esparsa * multiplicacao_matriz(Matriz_Esparsa *M1,Matriz_Esparsa *M2, int lin, int col,int c)
{
    int i,j,temp = c;
    float soma;
    Matriz_Esparsa *result;
    inicializa_lista(&result);
    for(i=lin; i>=1; i--)
    {
        for(j=col; j>=1; j--)
        {
            soma = 0;
            temp = c;
            while(temp>0){
                soma += busca_valor(M1,i,temp)*busca_valor(M2,temp,j);
                temp--;
            }
            if(soma!=0)
                insere_fim_lista(&result,soma,i,j);
        }
    }
    return result;
}

Matriz_Esparsa * sub_matriz(Matriz_Esparsa *M1,Matriz_Esparsa *M2, int lin, int col)
{
    int i,j;
    Matriz_Esparsa *result;
    inicializa_lista(&result);
    for(i=1; i<=lin; i++)
        for(j=1; j<=col; j++)
            if(busca_valor(M1,i,j)-(busca_valor(M2,i,j)!=0))
                insere_fim_lista(&result,(busca_valor(M1,i,j))-(busca_valor(M2,i,j)),i,j);
    return result;
}

int main()
{
    Matriz_Esparsa *matriz_1,*matriz_2,*matriz_resultante;
    int l_m1, c_m1, l_m2, c_m2,valor_lin,valor_col, menu, matriz_escolhida, loop = 0;
    float controle;

    inicializa_lista(&matriz_1);
    inicializa_lista(&matriz_2);
    inicializa_lista(&matriz_resultante);

    printf("\tMatriz 1\n");
    matriz_1 = entra_matriz(&l_m1,&c_m1);
    printf("\n\tMatriz 2\n");
    matriz_2 = entra_matriz(&l_m2,&c_m2);
    printf("\n\tMatrizes Esparsas\n");
    printf("\n 1 - Imprime os dados da matriz escolhida \n 2 - Imprime a diagonal principal da matriz escolhida \n 3 - Soma das Matrizes \n 4 - Subtracao das Matrizes \n 5 - Multiplicacao das Matrizes \n 6 - Matrizes transpostas \n 7 - Busca na matriz \n 0 - Sair \n");
    while(loop==0)
    {
        printf("\nEscolha sua opcao: ");
        scanf("%d", &menu);
        switch(menu)
        {
        case 1:
            printf("\nEscolha a matriz (1/2): ");
            scanf("%d", &matriz_escolhida);
            printf("\n");
            if(matriz_escolhida==1)
                imprime_matriz(matriz_1,l_m1,c_m1);
            else if(matriz_escolhida==2)
                imprime_matriz(matriz_2,l_m2,c_m2);
            else
                printf("\nMatriz invalida, retornado ao menu!");
            break;

        case 2:
            printf("\nEscolha a matriz (1/2): ");
            scanf("%d", &matriz_escolhida);
            printf("\n");
            if(matriz_escolhida==1)
                imprime_diagonal_principal(matriz_1,l_m1,c_m1);
            else if(matriz_escolhida==2)
                imprime_diagonal_principal(matriz_2,l_m2,c_m2);
            else
                printf("\nMatriz invalida, retornado ao menu!");
            break;

        case 3:
            if(l_m1!=l_m2||c_m1!=c_m2)
            {
                printf("\nMatrizes precisam ter tamanho iguais");
                break;
            }
            printf("\nSoma das matrizes: \n");
            matriz_resultante = soma_matriz(matriz_1,matriz_2,l_m1,c_m1);
            printf("\n");
            imprime_matriz(matriz_resultante,l_m1,c_m1);
            break;

        case 4:
            if(l_m1!=l_m2||c_m1!=c_m2)
            {
                printf("\nMatrizes precisam ter tamanho iguais");
                break;
            }
            printf("\nSubtracao das matrizes: \n");
            printf("\n(M1 - M2) digite 1, (M2 - M1) digite 2: ");
            scanf("%d", &matriz_escolhida);
            if(matriz_escolhida==1)
                matriz_resultante = sub_matriz(matriz_1,matriz_2,l_m1,c_m1);
            else if(matriz_escolhida==2)
                matriz_resultante = sub_matriz(matriz_2,matriz_1,l_m1,c_m1);
            else
                printf("\nValor invalido!");
            printf("\n");
            imprime_matriz(matriz_resultante,l_m1,c_m1);
            break;
        case 5:
            if(c_m1!=l_m2)
            {
                printf("\nMatrizes não podem ser multiplicadas - numero de coluna(m1) e linhas(m2) diferente");
                break;
            }
            printf("\nMultiplicação das matrizes: \n");
            printf("\n(M1 x M2) digite 1, (M2 x M1) digite 2: ");
            scanf("%d", &matriz_escolhida);
            if(matriz_escolhida==1)
                matriz_resultante = multiplicacao_matriz(matriz_1,matriz_2,l_m1,c_m2,c_m1);
            else if(matriz_escolhida==2)
                matriz_resultante = multiplicacao_matriz(matriz_2,matriz_1,l_m2,c_m1,c_m2);
            else
                printf("\nValor invalido!");
            printf("\n");
            imprime_matriz(matriz_resultante,l_m1,c_m1);
            break;
        case 6:
            printf("\nMatriz transposta: \n");
            printf("\nEscolha a matriz (1/2): ");
            scanf("%d", &matriz_escolhida);
            printf("\n");
            if(matriz_escolhida==1)
                matriz_transposta(matriz_1,l_m1,c_m1);
            else if(matriz_escolhida==2)
                matriz_transposta(matriz_2,l_m2,c_m2);
            else
                printf("\nMatriz invalida, retornado ao menu!");
            break;

        case 7:
            printf("\nEntre com a linha: ");
            scanf("%d", &valor_lin);
            printf("\nEntre com a coluna: ");
            scanf("%d", &valor_col);
            printf("\nEscolha a matriz (1/2): ");
            scanf("%d", &matriz_escolhida);
            printf("\n");
            if(matriz_escolhida==1)
                controle = busca_valor(matriz_1,valor_lin,valor_col);
            else if(matriz_escolhida==2)
                controle = busca_valor(matriz_1,valor_lin,valor_col);
            else
                printf("\nMatriz invalida, retornado ao menu!");
            if(controle!=0.0)
                printf("Valor encontrado: %.1f \n",controle);
            else
                printf("Valor nao encontrado\n");
            break;

        case 0:
            loop = 1;
            remove_propria_lista(&matriz_1);
            remove_propria_lista(&matriz_2);
            printf("\nEncerrando processo!\n\n");
            break;

        default:
            printf("\nOpcao invalida");
        }
    }
    return 0;
}
