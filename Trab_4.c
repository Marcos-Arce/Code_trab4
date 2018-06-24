#include <stdio.h>
#include <stdlib.h>

struct carta{
    char val;
    char cor; //!->OUROS=     @->COPAS     #->ESPADA     $->PAUS
};

void clear_screen()
{
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

int clear()
{
    int y = 1;
    char x;
    x = getchar();
    while(x!='\n'){
        x = getchar();
        y = 0;
    }
    if(!y){
        printf("Digite uma opcao valida\n\n");
    }
    return y;
}

char choose_baralho()
{
    char x;
    int y = 0;

    clear_screen();
    while(!y){
        printf("Como deseja iniciar o baralho?\n");
        printf("Aleatoriamente -> A\n");
        printf("Por arquivo    -> B\n");
        x = getchar();
        y = clear();
    }
    return x;
}

int check_int(int down_limit, int up_limit, int val)
{
    int y = 0;

    y = clear();
    if(!y);
    else if(val < down_limit || val > up_limit){
        printf("Digite um numero valido\n\n");
        y = 0;
    }else y = 1;

    return y;
}

void init_baralho_randon(struct carta *p)
{
    int i;
    int k;
    int j;
    int posi;
    struct carta *sort;
    sort = (struct carta *)malloc(106*sizeof(struct carta));
    
    for(i=0; i<2; i++){
        for(k=0; k<4; k++){
            for(j=1; j<14; j++){
                //printf("Posicao: %d", j-1+13*k + i*52);
                if(j<10) sort[j-1+13*k + i*52].val = j + '0';
                else sort[j-1+13*k + i*52].val = j - 10 + 'A';
                //printf("Valor de k: %d\n",k);
                if(k == 0) sort[j-1+13*k + i*52].cor = '!';
                else if(k == 1) sort[j-1+13*k + i*52].cor = '@';
                else if(k == 2) sort[j-1+13*k + i*52].cor = '#';
                else if(k == 3) sort[j-1+13*k + i*52].cor = '$';
            }
        }
    }
    // for(i = 0; i<104; i++){
    //     printf("valor: %c   naipe: %c\n", sort[i].val, sort[i].cor);
    // }
    sort[104].val = 'E';    sort[104].cor = '*';
    sort[105].val = 'E';    sort[104].cor = '*';
    i = 0;
    while(i<106){
        posi = rand()%106;
        //printf("posicao: %d\n", posi);
        if(!p[posi].val){
            p[posi] = sort[i];
            i++;
        }
    }
}

int jog()
{
    int y = 0;
    int n_jog;

    while(!y){
        printf("Digite a n_jogidade de jogadores que irão jogar Rummikub:\n");
        scanf("%d", &n_jog);
        y = check_int(1, 5, n_jog);
    }
    return n_jog;
}

void val_hand(struct carta **jogadores, struct carta *p, int n_jog)
{
    int i;
    int k;
    int j = 0;
    for(i=0; i<n_jog; i++)
        for(k=0; k<14; k++,j++)
            jogadores[i][k] = p[j];
}

struct carta* update_baralho(struct carta *p, int quant, int n_antigo)
{
    int i;
    int k;
    struct carta *tp;
    tp = (struct carta*) malloc((n_antigo - quant)*sizeof(struct carta));
    if(!tp){
        printf("Nao foi possivel alocar memoria suficiente\n\n");
        exit(1);
    }

    for(i=quant, k=0; i<n_antigo; i++,k++){
        tp[k] = p[i];
    }
    free(p);
    return tp;
}

int main(int argc, char const *argv[])
{
    int n_jog;
    int i;
    int k;
    int n = 106;
    char x;
    struct carta *p;
    struct carta **jogadores = NULL;
    
    p = (struct carta *)calloc(106,sizeof(struct carta));
    if(!p){
        printf("Nao foi possivel alocar memoria suficiente\n");
        printf("Encerrando o programa...\n");
        return 1;
    }
    do{
        x = choose_baralho();
        if(x == 'A' || x == 'a'){
            init_baralho_randon(p);
            break;
        }else printf("Digite uma opcao valida\n\n");
    }while(1);

    n_jog = jog();

    jogadores = (struct carta **)malloc(sizeof(struct carta *)*n_jog);
    if(!jogadores){
        printf("Nao foi possivel alocar memoria suficiente\n\n");
        return 1;
    }
    for(i = 0; i<n_jog; i++){
        jogadores[i] = (struct carta *)calloc(14, sizeof(struct carta));
        if(!jogadores[i]){
            printf("Nao foi possivel alocar memoria suficiente\n\n");
            return 1;
       }
    }
    
    val_hand(jogadores, p, n_jog);
    p = update_baralho(p,n_jog*14,106);
    n -= 14*n_jog;
}
