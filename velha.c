#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

COORD coord = {0,0};
int l=0,vez,matriz[3][3];
char nomeJog1[50];
char nomeJog2[50];
FILE *txt;

///Struct
typedef struct Velha
{
    int partida;
    char JogVelha[3][3];
    char resultado;
} Partida;

///Funções esteticas
int random(int high)
{
    srand( (unsigned)time(NULL));
    return rand()%high;
}

void gotoxy(int x,int y)
{
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
void hidecursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

///Funções do jogo
int grava_dado(char nome_arq[50], Partida partida)
{
    FILE *bin;
    if((bin = fopen(nome_arq, "a + b")) == NULL)
    {
        perror("Erro ao abrir bin");
        return 0;
    }
    fwrite(&partida, 1, sizeof(Partida), bin);
    fclose(bin);
    return 1;
}

Partida exibe_dados(char nome_arq[50], int partida)
{
    FILE *bin;
    Partida exibe;
    if((bin = fopen(nome_arq, "a + b")) == NULL)
    {
        perror("Erro ao abrir bin");
        exit(0);
    }

    while (1)
    {
        fread(&exibe,sizeof(Partida),1, bin);
        if(exibe.partida==partida)
            break;
        if(feof(bin))
        {
            exibe.partida = NULL;
            break;
        }

    }
    if(exibe.partida==NULL)
        printf("Partida nao encontrada\n");
    fclose(bin);
    return exibe;
}

void exibe_tudo(int partida)
{
    FILE *bin;
    FILE *txt;
    Partida exibe;
    char buff[50],ganhadorInverse[30],ganhador[30],ganhadorFinal[30];
    char jogadores[50][50];
    int i,j,x=0;

    if((bin = fopen("Velha.bin", "a + b")) == NULL)
    {
        perror("Erro ao abrir bin");
        return 0;
    }
    if((txt = fopen("Velha.txt", "a+")) == NULL)
    {
        perror("Erro ao abrir txt");
        return 0;
    }

    exibe.partida = NULL;
    while (1)
    {

        fread(&exibe,sizeof(Partida),1, bin);
        fgets(buff, sizeof(buff), txt);
        strcpy(ganhador,buff);
        removeChar(buff,';');

        ///Seleciona ganhador para array de string
        removeChar(ganhador,' ');
        strcpy(ganhadorInverse,"                             ");
        strcpy(ganhadorFinal,"                             ");
        for(i=0; ganhador[i+1]!=exibe.resultado; ++i)
            ganhadorInverse[i] = ganhador [i];
        for(i=strlen(ganhadorInverse); (ganhadorInverse[i]!=';'&&i>=0); --i)
            if(ganhadorInverse[i]>='A'&&ganhadorInverse[i]<='Z'||ganhadorInverse[i]>='a'&&ganhadorInverse[i]<='z')
            ganhadorFinal[i] = ganhadorInverse[i];
        removeChar(ganhadorFinal,' ');
        strcpy(jogadores[x],ganhadorFinal);
        x++;

        ///Exibe dados de cada partida
        printf(buff);
        printf("Partida de numero: %d\n",exibe.partida);
        printf("Jogador ganhador: %c\n",exibe.resultado);
        printf("Velha: \n");
        printf("\n");
        for(i = 0 ; i < 3 ; i++)
        {
            for(j = 0 ; j < 3 ; j++)
            {
                printf("%c",exibe.JogVelha[i][j]);
                if(j != 2)
                    printf("|");
            }
            printf("\n");
        }
        printf("\n");
        if(exibe.partida==partida || partida==1)
            break;
        if(feof(bin))
            break;

    }
    if(exibe.partida==NULL)
        printf("Nenhuma partida encontrada\n");

    verificaGanhador(jogadores);
    fclose(bin);
}

void recebePartida(Partida *Jogo,int part, char result)
{
    (*Jogo).partida = part;
    int i, j;
    for(i=0; i<3; i++)
    {
        for(j=0; j<3; j++)
        {
            if(matriz[i][j]==1)
            {
                (*Jogo).JogVelha[i][j]='X';
            }
            else if(matriz[i][j]==2)
            {
                (*Jogo).JogVelha[i][j]='O';
            }
            else
            {
                (*Jogo).JogVelha[i][j]=' ';
            }

        }
    }
    (*Jogo).resultado = result;
}

void escreveTxt(char *jog1, char *jog2)
{
    if((txt = fopen("Velha.txt", "a+")) == NULL)
    {
        perror("Erro ao abrir txt");
        exit(1);
    }
    fprintf(txt, "%s; ", nomeJog1);
    fprintf(txt, "%c; ", *jog1);
    fprintf(txt, "%s; ", nomeJog2);
    fprintf(txt, "%c;\n", *jog2);
    fclose(txt);
}

void removeChar(char *str, char garbage)
{

    char *src, *dst;
    for (src = dst = str; *src != '\0'; src++)
    {
        *dst = *src;
        if (*dst != garbage) dst++;
    }
    *dst = '\0';
}

void verificaGanhador(char jogadores[50][50]){
    int i,j,occurrence=0, maximum = 0,x=1;
    char *index_max = NULL;
    for (i=0; i<50; i++){
        if(strlen(jogadores[i])==0)
            break;
        occurrence = 0;
        for (j=i; j<50; j++){
            if (!strcmp(*(jogadores+i), *(jogadores+j))){
                occurrence++;
            }
        }
        if (occurrence>maximum){
            maximum = occurrence;
            index_max = *(jogadores+i);
        }
        if(occurrence==maximum&&index_max != *(jogadores+i))
            x++;

    }
    if(x>1)
        printf("Ocorreu um empate entre %d jogadores, realizem novas partidas!\n", x);
    else if (index_max != NULL)
        printf("O jogador com mais vitorias foi %s com %d vitorias \n", index_max,maximum);

}

int verifica_ganhador(char jog)
{
    int lin, col,soma,soma2;
    ///Verifica linhas
    for(lin = 0 ; lin < 3 ; lin++)
    {
        soma=0;
        for(col = 0 ; col < 3 ; col++)
        {
            if(jog=='X')
            {
                if( matriz[lin][col]==1)
                    soma++;
            }
            else
            {
                if( matriz[lin][col]==2)
                    soma++;
            }
            if(soma==3)
                return 1;
        }
    }
    ///Verifica cols
    for(col = 0 ; col < 3 ; col++)
    {
        soma=0;

        for(lin = 0 ; lin < 3 ; lin++)
            if(jog=='X')
            {
                if( matriz[lin][col]==1)
                    soma++;
            }
            else
            {
                if( matriz[lin][col]==2)
                    soma++;
            }
        if(soma==3)
            return 1;
    }
    ///Verifica Diagonais
    soma=soma2=0;
    for(lin = 0 ; lin < 3 ; lin++)
    {
        for(col = 0 ; col < 3 ; col++)
        {
            if(lin==col)
            {
                if(jog=='X')
                {
                    if( matriz[lin][col]==1)
                        soma++;
                }
                else
                {
                    if( matriz[lin][col]==2)
                        soma++;
                }
            }
            if(lin==0&&col==2||lin==2&&col==0||lin==1&&col==1)
            {
                if(jog=='X')
                {
                    if( matriz[lin][col]==1)
                        soma2++;
                }
                else
                {
                    if( matriz[lin][col]==2)
                        soma2++;
                }
            }
        }
    }
    if(soma==3||soma2==3)
        return 1;
    else
        return 0;
}
void int_easy(int *lin,int *col)
{
    int i = random(10);
    switch(i)
    {
    case 1:
        *lin = 0;
        *col = 0;
        break;
    case 2:
        *lin = 0;
        *col = 1;
        break;
    case 3:
        *lin = 0;
        *col = 2;
        break;
    case 4:
        *lin = 1;
        *col = 0;
        break;
    case 5:
        *lin = 1;
        *col = 1;
        break;
    case 6:
        *lin = 1;
        *col = 2;
        break;
    case 7:
        *lin = 2;
        *col = 0;
        break;
    case 8:
        *lin = 2;
        *col = 1;
        break;
    case 9:
    default:
        *lin = 2;
        *col = 2;
        break;
    }
    random(10);
}

void jogada_computador(char jog, int nivel)
{
    int lin,col;
    int_easy(&lin,&col);

    while(lin < 0 || lin > 3 || col < 0 || col > 3||matriz[lin][col]!=0 )
        int_easy(&lin,&col);

    if(jog=='X')
        matriz[lin][col] = 1;
    else
        matriz[lin][col] = 2;
    return;
}



int jogada_usuario(int lin, int col, char jog)
{
    if(lin < 0 || lin > 3 || col < 0 || col > 3 )
        return 1;
    else if(matriz[lin][col]!=0)
        return 2;

    if(jog=='X')
        matriz[lin][col] = 1;
    else
        matriz[lin][col] = 2;
    return 0;
}

int menu()
{
    int opc;
    gotoxy(30,12);
    printf("Jogo feito por Gabriel e Daniel TADS Tarde");
    gotoxy(10,2);
    printf("   |  __   __   __       __|  __            ___  |   |__   __  ");
    gotoxy(10,3);
    printf("(__, (__) (__| (__)     (__| (__(     (__| (__/_ |_, |  ) (__( ");
    gotoxy(10,4);
    printf("           __/                                                 ");
    gotoxy(20,5);
    printf("1 - Jogador vs computador");
    gotoxy(20,6);
    printf("2 - Jogador vs jogador");
    gotoxy(20,7);
    printf("3 - Exibe partida");
    gotoxy(20,8);
    printf("4 - Exibe todas as partidas");
    gotoxy(30,10);
    printf("Informe opcao: ");
    scanf("%d%*c", &opc);
    switch(opc)
    {
    case 1:
        return 1;
        break;
    case 2:
        return 2;
    case 3:
        return 3;
        break;
    }
}

void inicializa_velha()
{
    int i, j;
    for(i=0; i<3; i++)
        for(j=0; j<3; j++)
            matriz[i][j]=0;
}

void escolha_simbolo(char *jog1, char *jog2, int opc)
{
    system("cls");
    do
    {
        gotoxy(20,6);
        printf("Digite X ou O");
        gotoxy(20,7);
        printf("Escolha: ");
        scanf("%c%*c",jog1);
        *jog1=toupper(*jog1);
    }
    while(*jog1!='X'&&*jog1!='O');
    if (*jog1 == 'X')
        *jog2 = 'O';
    else
        *jog2 = 'X';
    system("cls");
    gotoxy(20,6);
    printf("Digite o nome do jogador 1");
    gotoxy(20,7);
    gets(nomeJog1);
    system("cls");
    gotoxy(20,6);
    if(opc!=1)
    {
        printf("Digite o nome do jogador 2");
        gotoxy(20,7);
        gets(nomeJog2);
        system("cls");
    }

}

void verificaJogada(int i)
{
    if(i==0)
        printf("\nJogada valida");
    else if(i==1)
    {
        printf("\nPosicao invalida");
        if(vez==1)
            vez=2;
        else
            vez=1;
    }
    else
    {
        printf("\nPosicao ja ocupada");
        if(vez==1)
            vez=2;
        else
            vez=1;
    }
}
void desenhamatriz()
{
    int i, j;
    printf("\n");
    for(i = 0 ; i < 3 ; i++)
    {
        char nomeJog1[50];
        char nomeJog2[50];
        for(j = 0 ; j < 3 ; j++)
        {
            if(matriz[i][j] == 0)
                printf("    ");
            else if(matriz[i][j] == 1)
                printf("  X ");
            else
                printf("  O ");

            if(j != 2)
                printf("|");
        }
        printf("\n");
    }
    printf("\n");
}

int main()
{
    Partida Jogo;
    char jognov = 'S';
    char jog1;
    char jog2;
    char nomeArq[50];
    int aux,gan,lin,col,opc,dificuldade,pergunta,gravar,part;
    hidecursor();
    ///Pega partida atual
    FILE *bin;
    bin=fopen("Velha.bin", "rb");
    if(bin)
        while (1)
        {
            fread(&Jogo,sizeof(Partida),1, bin);
            if(feof(bin))
            {
                part = Jogo.partida;
                break;
            }
        }
    else
        part = 0;
    printf("%d",part);
    fclose(bin);
    ///Loop do game
    do
    {

        strcpy(nomeArq,"Velha.bin");
        system("cls");
        dificuldade=0;
        vez = 1;
        inicializa_velha();
        opc=menu();
        aux=l=lin=gravar=pergunta=col=0;
        if(opc==1)
        {
            part++;
            strcpy(nomeJog2,"Computador");
            escolha_simbolo(&jog1,&jog2,opc);
            escreveTxt(&jog1,&jog2);
            while(l<9)
            {
                printf("\n");
                if(aux!=1)
                    desenhamatriz();
                aux = 0;
                if(vez==1)
                {
                    printf("\n %s, faca sua jogada: \n",nomeJog1);
                    printf("lin: ");
                    scanf("%d%*c", &lin);
                    lin--;
                    printf("col: ");
                    scanf("%d%*c", &col);
                    col--;
                    vez = 2;
                    verificaJogada(jogada_usuario(lin,col,jog1));
                    gan=verifica_ganhador(jog1);
                    if(gan==1)
                    {
                        printf("\nJogador %s ganhou",nomeJog1);
                        recebePartida(&Jogo,part,jog1);
                        break;
                    }
                    if(vez==2)
                        l++;
                }
                else if(vez==2)
                {
                    ///Hora do pc
                    printf("\n %s, faca sua jogada: \n",nomeJog2);
                    vez = 1;
                    lin=col=0;
                    jogada_computador(jog2,dificuldade);
                    gan=verifica_ganhador(jog2);
                    if(gan==1)
                    {
                        printf("\nComputador ganhou");
                        recebePartida(&Jogo,part,jog2);
                        break;
                    }
                    if(vez==1)
                        l++;
                }
            }
            printf("\n");
            desenhamatriz();
            printf("\n");
            if(l==9)
            {
                printf("\nPartida empatou!");
                recebePartida(&Jogo,part,'V');
            }
            gravar = grava_dado(nomeArq,Jogo);
            if(gravar==1)
                printf("Partida gravada com sucesso");
            else
                printf("Ocorreu erro ao gravar partida");
        }
        else if(opc==2)
        {
            part++;
            escolha_simbolo(&jog1,&jog2,opc);
            escreveTxt(&jog1,&jog2);
            while(l<9)
            {
                printf("\n");
                desenhamatriz();
                if(vez==1)
                {
                    printf("\n %s, faca sua jogada: \n",nomeJog1);
                    printf("lin: ");
                    scanf("%d%*c", &lin);
                    lin--;
                    printf("col: ");
                    scanf("%d%*c", &col);
                    col--;
                    vez = 2;
                    verificaJogada(jogada_usuario(lin,col,jog1));
                    gan=verifica_ganhador(jog1);
                    if(gan==1)
                    {
                        printf("\nJogador %s ganhou",nomeJog1);
                        recebePartida(&Jogo,part,jog1);
                        break;
                    }
                    if(vez==2)
                        l++;
                }
                else if(vez==2)
                {
                    printf("\n %s, faca sua jogada: \n",nomeJog2);
                    printf("lin: ");
                    scanf("%d%*c", &lin);
                    lin--;
                    printf("col: ");
                    scanf("%d%*c", &col);
                    col--;
                    vez = 1;
                    verificaJogada(jogada_usuario(lin,col,jog2));
                    gan=verifica_ganhador(jog2);
                    if(gan==1)
                    {
                        printf("\nJogador %s ganhou",nomeJog2);
                        recebePartida(&Jogo,part,jog2);
                        break;
                    }
                    if(vez==1)
                        l++;
                }

            }
            printf("\n");
            desenhamatriz();
            printf("\n");
            if(l==9)
            {
                printf("\nPartida empatou!");
                recebePartida(&Jogo,part,'V');
            }
            int i,j;
            gravar = grava_dado(nomeArq,Jogo);
            if(gravar==1)
                printf("Partida gravada com sucesso");
            else
                printf("Ocorreu erro ao gravar partida");
        }
        else if(opc==3)
        {
            system("cls");
            printf("\nQual partida deseja procurar?\n");
            scanf("%d%*c",&pergunta);
            Jogo = exibe_dados(nomeArq,pergunta);
            if(Jogo.partida!=NULL)
            {
                printf("Partida de numero: %d\n",Jogo.partida);
                printf("Jogador ganhador: %c\n",Jogo.resultado);
                int i, j;
                printf("\n");
                for(i = 0 ; i < 3 ; i++)
                {
                    for(j = 0 ; j < 3 ; j++)
                    {
                        printf("%c",Jogo.JogVelha[i][j]);
                        if(j != 2)
                            printf("|");
                    }
                    printf("\n");
                }
                printf("\n");
            }
        }
        else if(opc==4)
        {
            system("cls");
            exibe_tudo(part);
        }
        else
            return 0;
        printf("\nDeseja voltar ao menu?(S/N)");
        scanf("%c%*c",&jognov);
    }
    while(toupper(jognov)=='S');
}
