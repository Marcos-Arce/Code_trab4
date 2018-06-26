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
    int check = 1;
    char x;
    x = getchar();
    while(x!='\n'){
        x = getchar();
        check = 0;
    }
    if(!check){
        printf("Digite uma opcao valida\n\n");
    }
    return check;
}

char choose_baralho()
{
    char x;
    int check = 0;

    while(!check){
        printf("Como deseja iniciar o baralho?\n");
        printf("Aleatoriamente -> A\n");
        printf("Por arquivo    -> B\n");
        x = getchar();
        check = clear();
    }
    return x;
}

int check_int(int down_limit, int up_limit, int val)
{
    int check = 0;

    check = clear();
    if(!check);
    else if(val < down_limit || val > up_limit){
        printf("Digite um numero valido\n\n");
        check = 0;
    }else check = 1;

    return check;
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
    //     printf("%c%c\n", sort[i].val, sort[i].cor);
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
    free(sort);
}

void init_baralho_txt(struct carta *p)
{
    int i;
    char nome[60];
    FILE *fp = NULL;

    while(!fp){
        printf("Digite o nome do arquivo que deseja abrir:\n");
        fgets(nome, 59, stdin);
        for(i=0; nome[i] != '\0'; i++) if(nome[i] == '\n') nome[i] = '\0';
        fp = fopen(nome, "rt");
        if(!fp){
            printf("Crie o arquivo primeiro\n\n");
            printf("Digite qualquer tecla para continuar...\n");
            getc(stdin);
        }
    }
    i=0;
    while(!( i > 105|| feof(fp))){
        p[i].val = getc(fp);
        if(p[i].val == 'E'){
            p[i].cor = getc(fp);
        }else p[i].cor = getc(fp);
        getc(fp);
        printf("VALor %c Naipe: %c\n", p[i].val, p[i].cor);
        printf("Valor de i: %d\n", i);
        i++;
    }
    i-=1;
    if(i != 105){
        printf("Valor de i: %d\n", i);
        printf("Adicione o numero corrreto de cartas\n\n");
        exit(1);
    }
    fclose(fp);
    for(i=0; i<106; i++){
        printf("Valor: %c naipe: %c\n", p[i].val, p[i].cor);
    }
}

int jog()
{
    int check = 0;
    int n_jog;

    while(!check){
        printf("Digite a quantidade de jogadores que irão jogar Rummikub:\n");
        scanf("%d", &n_jog);
        check = check_int(1, 5, n_jog);
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

int choose_player(struct carta *p, int n_jog, int repetidos[])
{
    int i;
    int k;
    int check;
    int posi[n_jog];
    int max = 0;
    int aux;
    int val;

    for(i = 0; i<n_jog; i++){
        check = 0;
        while(!check){    
            printf("Jogador %d, escolha uma carta do baralho: (de 0 ate 105)\n", repetidos[i]+1);
            scanf("%d", &posi[i]);
            check = check_int(0, 105, posi[i]);
            for(k=0; k<i;k++){
                if(posi[k] == posi[i]){
                    printf("Digite uma carta do baralho que nao tenha sido utilizada\n");
                    check = 0;
                    break;
                }
            }
        }
        if(p[posi[i]].val >= '0' && p[posi[i]].val <= '9')  val = p[posi[i]].val - '0';
        else if(p[posi[i]].val == 'E') val = 30;
        else val = p[posi[i]].val - 'A' + 10; 
        printf("Valor da carta: %d\n", val);
        if(p[posi[i]].val > max) max = p[posi[i]].val;
    }
    aux = n_jog;
    n_jog = 0;
    for(i = 0; i < aux; i++){
        if(p[posi[i]].val == max){
            repetidos[n_jog] = i;
            n_jog++;
        }
    }
    if(n_jog == 1){
        return repetidos[0];
    }
    printf("Valores repetidos dos jogadores:");
    for(i = 0; i<n_jog; i++) printf(" %d ", repetidos[i]+1);
    printf("\nEscolham as suas cartas novamente\n\n");
    return choose_player(p, n_jog, repetidos);
}

int main(int argc, char const *argv[])
{
    int n_jog;
    int i;
    int n = 106;
    int first;
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
        }else if(x == 'B' || x == 'b'){
            init_baralho_txt(p);
            break;
        }else printf("Digite uma opcao valida\n\n");
        clear_screen();
    }while(1);
    clear_screen();
    n_jog = jog();
    int repetidos[n_jog];
    if(n_jog > 1){
    for(i=0; i<n_jog; i++) repetidos[i] = i;
    first = choose_player(p,n_jog, repetidos);
    }
    first = 0;
    printf("Primeiro jogador: %d\n", first + 1);
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
