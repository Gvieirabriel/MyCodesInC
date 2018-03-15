#include <string.h>
#include <time.h>
#include <windows.h>

typedef struct Nodo_Pilha
{
    int elemento;
    struct Nodo_Pilha *prox;
}*NODOPTR;

NODOPTR pilha=NULL;

#define X 30
#define Y 30

char matriz[X][Y];

enum floor {PAREDE=219,BECO=176,LIVRE=32,SAIDA=81,RATO=1,VISITADA=46};

int getrand(int min,int max)
{
    return(rand()%(max-min)+min);
}

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
void push(int dado)
{
    NODOPTR nodo;
    nodo= Cria_Nodo( );
    nodo->elemento = dado;
    nodo->prox = pilha;
    pilha = nodo;
}

int pop( )
{
    NODOPTR nodo;
    int elem;
    if(!pilha)
    {
        printf("A pilha está vazia!!!");
        return -1;
    }
    nodo = pilha;
    elem = nodo->elemento;
    pilha = nodo->prox;
    free(nodo);
    return elem;
}

void hidecursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

int saida_proxima()
{
    int i,j;
    retorna_posicao(&i,&j);
    if(matriz[i][j-1]==SAIDA)
    {
        matriz[i][j] = VISITADA;
        matriz[i][j-1] = RATO;
        push(converte_posicao(i,j-1));
        return -1;
    }
    else if(matriz[i][j+1]==SAIDA)
    {
        matriz[i][j] = VISITADA;
        matriz[i][j+1] = RATO;
        push(converte_posicao(i,j+1));
        return -1;
    }
    else if(matriz[i+1][j]==SAIDA)
    {
        matriz[i][j] = VISITADA;
        matriz[i+1][j] = RATO;
        push(converte_posicao(i+1,j));
        return -1;
    }
    else if(matriz[i-1][j]==SAIDA)
    {
        matriz[i][j] = VISITADA;
        matriz[i-1][j] = RATO;
        push(converte_posicao(i-1,j));
        return -1;
    }
    else
        return 0;
}


void inicia_matriz(int *controle)
{
    inicia_mapa();
    if(inicia_saida()==1){
        printf("\nLabirinto sem solucao, pois saida nao esta livre\n");
        *controle = 1;
    }else
    imprime_matriz();
}

void inicia_mapa()
{
    int i,j,c=0;
    for(i=0; i<X; i++)
        for(j=0; j<Y; j++)
            if(i==0||i==X-1||j==0||j==Y-1)
                matriz[i][j] = PAREDE;
            else if(getrand(0,50)%5==0)
                matriz[i][j] = PAREDE;
            else if(i==1&&getrand(0,2)==0&&c==0||i==X-2&&getrand(0,2)==0&&c==0)
            {
                matriz[i][j] = RATO;
                push(converte_posicao(i,j));
                 c=1;
            }
            else if(j==1&&getrand(0,2)==0&&c==0||j==X-2&&getrand(0,2)==0&&c==0)
            {
                matriz[i][j] = RATO;
                push(converte_posicao(i,j));
                c=1;
            }
            else
                matriz[i][j] = LIVRE;
}

int inicia_saida()
{
    int i,j;
    for(i=X-1; i>=0; i--)
        for(j=Y-1; j>=0; j--)
            if(i==0&&j>1&&j<Y-2&&getrand(0,20)==0||i==29&&j>1&&j<Y-2&&getrand(0,20)==0)
            {
                matriz[i][j] = SAIDA;
                if(matriz[i][j-1]!=LIVRE&&matriz[i][j+1]!=LIVRE&&matriz[i-1][j]!=LIVRE&&matriz[i+1][j]!=LIVRE)
                    return 1;
                return 0;
            }
            else if(j==0&&i>1&&i<Y-2&&getrand(0,20)==0||j==29&&i>1&&i<Y-2&&getrand(0,20)==0)
            {
                matriz[i][j] = SAIDA;
                if(matriz[i][j-1]!=LIVRE&&matriz[i][j+1]!=LIVRE&&matriz[i-1][j]!=LIVRE&&matriz[i+1][j]!=LIVRE)
                    return 1;
                return 0;
            }
    matriz[X-1][Y-2] = SAIDA;
}

void imprime_matriz()
{
    int i,j;
    for(i=0; i<X; i++)
    {
        for(j=0; j<Y; j++)
            printf("%c",matriz[i][j]);
        printf("\n");
    }
}

int converte_posicao(int i, int j)
{
    return (i * 100 + j);
}

void retorna_posicao(int *i, int *j)
{
    *i = pilha->elemento/100;
    *j = pilha->elemento%100;
}

int determina_caminho()
{
    int i,j;
    retorna_posicao(&i,&j);
    if(matriz[i][j] != SAIDA)
    {
        if(matriz[i][j-1]==LIVRE)
        {
            matriz[i][j] = VISITADA;
            matriz[i][j-1] = RATO;
            push(converte_posicao(i,j-1));
            return 0;
        }
        else if(matriz[i][j+1]==LIVRE)
        {
            matriz[i][j] = VISITADA;
            matriz[i][j+1] = RATO;
            push(converte_posicao(i,j+1));
            return 0;
        }
        else if(matriz[i+1][j]==LIVRE)
        {
            matriz[i][j] = VISITADA;
            matriz[i+1][j] = RATO;
            push(converte_posicao(i+1,j));
            return 0;
        }
        else if(matriz[i-1][j]==LIVRE)
        {
            matriz[i][j] = VISITADA;
            matriz[i-1][j] = RATO;
            push(converte_posicao(i-1,j));
            return 0;
        }
        else
        {
            matriz[i][j] = BECO;
            pop();
            if(!pilha)
                return 1;
            retorna_posicao(&i,&j);
            matriz[i][j] = RATO;
            return 0;
        }
    }
    else
        return -1;
}

void main( )
{
    hidecursor();
    srand(time(NULL));
    char m,controle,caminho,saida;
    do
    {
        controle=0;
        inicia_matriz(&controle);
        while(controle==0)
        {
            _sleep(40);
            system("@cls||c");
            imprime_matriz();
            saida=saida_proxima();
            caminho=determina_caminho();
            if(saida==-1||caminho==-1)
            {
                system("@cls||c");
                printf("\nSaida encontrada\n");
                controle=1;
            }
            else if(caminho==1)
            {
                system("@cls||c");
                printf("\nLabirinto sem solucao\n");
                controle=1;
            }
        }
        printf("\nJogar novamente?(y/n)\n");
        scanf("%c%*c", &m);
    }
    while(m!='n');
    return 0;
}
