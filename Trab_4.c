#include <stdio.h>
#include <stdlib.h>

struct carta{
    char val_c;
    unsigned int val_n : 5;
    char cor;
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

char choose_action()
{
    char x;
    int check = 0;

    while(!check){
        printf("Qual acao deseja realizar?\n");
        printf("Criar grupo de cartas                   -> A\n");
        printf("Adicionar cartas a grupos existentes    -> B\n");
        printf("Transferir carta de um grupo para outro -> C\n");
        printf("Dividir grupo                           -> D\n");
        printf("Salvar e sair                           -> E\n");
        printf("Sair e retirar uma carta do baralho     -> F\n");
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
                if(j<10) sort[j-1+13*k + i*52].val_c = j + '0';
                else sort[j-1+13*k + i*52].val_c = j - 10 + 'A';
                //printf("Valor de k: %d\n",k);
                sort[j-1+13*k + i*52].val_n = j;
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
    
    sort[104].val_c = '*';    sort[104].cor = '*';    sort[104].val_n = 20;
    sort[105].val_c = '*';    sort[105].cor = '*';    sort[105].val_n = 20;
    i = 0;
    while(i<106){
        posi = rand()%106;
        //printf("posicao: %d\n", posi);
        if(!p[posi].val_n){
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
    while(!(feof(fp) || i > 105)){
        p[i].val_c = getc(fp);
        p[i].cor = getc(fp);
        if(p[i].val_c >= '0' && p[i].val_c <= '9') p[i].val_n = p[i].val_c - '0';
        else if(p[i].val_c >= 'A' && p[i].val_c <= 'D') p[i].val_n = p[i].val_c - 'A' + 10;
        else if(p[i].val_c == '*') p[i].val_n = 20;
        getc(fp);
        printf("Valor %c Naipe: %c Valor real: %d   ", p[i].val_c, p[i].cor, p[i].val_n);
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
        printf("Valor: %c naipe: %c\n", p[i].val_c, p[i].cor);
    }
}

int jog()
{
    int check = 0;
    int n_jog;

    while(!check){
        printf("Digite a quantidade de jogadores que irão jogar Rummikub (1 ate 5):\n");
        scanf("%d", &n_jog);
        check = check_int(1, 5, n_jog);
    }
    return n_jog;
}
//int  *mao
void val_hand(struct carta **player, struct carta *p, int n_jog, int *quant_mao)
{
    int i;
    int k;
    int j = 0;
    for(i=0; i<n_jog; i++){
    quant_mao[i] = 14;
        for(k=0; k<14; k++,j++){
            player[i][k] = p[j];
        }
    }
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
        printf("Valor da carta: %d\n", p[posi[i]].val_n);
        if(p[posi[i]].val_n > max) max = p[posi[i]].val_n;
    }
    aux = n_jog;
    n_jog = 0;
    for(i = 0; i < aux; i++){
        if(p[posi[i]].val_n == max){
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
//int *mao;
void show_hand(struct carta **player, int i, int limit)
{
    int k;
    for(k=0; k<limit; k++){
        printf("%c%c ", player[i][k].val_c, player[i][k].cor);
        if(!(k%10) && k>0) printf("\n");
    }
    printf("\n\n");
}
//int *mao_copy;
void show_hand_copy(struct carta *player_copy, int limit)
{
    int k;
    for(k=0; k<limit; k++){
        printf("%c%c ", player_copy[k].val_c, player_copy[k].cor);
        if(!(k%10) && k>0) printf("\n");
    }
    printf("\n\n");
}

void show_baralho(int n_baralho)
{
    printf("\n");
    printf("                                                                            Baralho:\n");
    printf("                                                                               ----\n");
    printf("                                                                               |%d|\n", n_baralho);
    printf("                                                                               |  |\n");
    printf("                                                                               ----\n");
    printf("\n\n");
}
//int *quant_grupo & quant_grupo_copy
void show_mesa(struct carta **grupo, int n_grupo, int *limit)
{
    int i;
    int k;

    for(i=0; i<n_grupo; i++){
        if(i>0) printf("\n\n");
        printf("Grupo %d                                          ", i+1);
        for(k=0; k<limit[i]; k++){
            if(!k%13) printf("\n| ");
            printf("%c%c ", grupo[i][k].val_c, grupo[i][k].cor);
        }
    }
}
//int *quant_grupo & quant_grupo_copy
void show_info(struct carta **grupo, int n_grupo, int n_baralho, struct carta **player, int i, struct carta *player_copy,int *quant_grupo, int quant_mao, int decision)
{
    printf("Turno do jogador: %d\n\n", i+1);
    printf("    MESA:\n\n");
    if(n_grupo>0) show_mesa(grupo, n_grupo, quant_grupo);
        show_baralho(n_baralho);
    if(decision) show_hand(player, i, quant_mao);
    else show_hand_copy(player_copy, quant_mao);
}

void buble_sort_carta(struct carta *vector, int limit, int grupo_hand)
{
    int i;
    int k;
    int j;
    int flag = 0;
    struct carta *aux;

    aux = (struct carta *) malloc(sizeof(struct carta));
    if(!aux){
        printf("Nao foi possivel alocar memoria suficiente\n\n");
        exit(1);
    }
    for(i = 0; i<limit; i++){
        for(k=0; k<limit - 1; k++){
            if(vector[k].val_n > vector[k+1].val_n){
                *aux = vector[k];
                vector[k] = vector[k+1];
                vector[k+1] = *aux;
            }
        }
    }
    if(grupo_hand){
        for(i=0; i<limit; i++){
            if(vector[i].val_n == 20){
                flag++;
            }
        }
        i=0;
        while(flag){
            for(i=i; i<limit-2; i++){
                if(vector[i].val_n + 1 != vector[i+1].val_n && vector[i].val_n != vector[i+1].val_n){
                    *aux = vector[i+1];
                    vector[i+1] = vector[limit -1];
                    vector[limit - 1] = *aux;
                    //printf("%c%c  %c%c  %c%c %c%c\n", vector[0].val_c, vector[0].cor, vector[1].val_c, vector[1].cor, vector[2].val_c, vector[2].cor, vector[3].val_c, vector[3].cor);
                }
            }
            for(k=i+2; k<limit; k++){
                for(j=i+2; j<limit - 1; j++){
                    if(vector[j].val_n > vector[j+1].val_n){
                        *aux  = vector[j];
                        vector[j] = vector[j+1];
                        vector[j+1] = vector[j];
                        //printf("%c%c  %c%c  %c%c %c%c\n", vector[0].val_c, vector[0].cor, vector[1].val_c, vector[1].cor, vector[2].val_c, vector[2].cor, vector[3].val_c, vector[3].cor);
                    }
                }
            }
            flag--;
        }
    }
    free(aux);
}


int *copy_info(int *vector, int limit)
{
    int i;
    int *vector_copy;

    vector_copy = (int *)malloc(limit*sizeof(int));
    if(!vector_copy){
        printf("Nao foi possivel alocar memoria suficiente\n\n");
        exit(1);
    }
    for(i=0; i<limit;i++){
        vector_copy[i] = vector[i];
    }
    return vector_copy;
}

struct carta **copy_info_grupos(struct carta **grupo,int n_grupo, int *quant_grupo)
{
    int i;
    int k;
    struct carta **grupo_copy;

    grupo_copy = (struct carta **)malloc((n_grupo) * sizeof(struct carta *));
    if(!grupo_copy){
        printf("Nao foi possivel alocar memoria suficiente\n\n");
        exit (1);
    }
    for(i = 0; i<n_grupo; i++){
        grupo_copy[i] = (struct carta *)malloc(quant_grupo[i] * sizeof(struct carta));
        if(!grupo_copy){
            printf("Nao foi possivel alocar memoria suficiente\n\n");
            exit (1);
        }
    }
    for(i=0; i<n_grupo; i++){
        for(k=0; k<quant_grupo[i]; k++){
            grupo_copy[i][k] = grupo[i][k];
        }
    }
    return grupo_copy;
}

struct carta *copy_info_player(struct carta **player, int i, int limit)
{
    int k;
    struct carta *player_copy;

    player_copy = (struct carta *)malloc(limit*sizeof(struct carta));
    if(!player_copy){
        printf("Nao foi possivel alocar memoria suficiente\n\n");
    }
    for(k=0; k<limit; k++){
        player_copy[k] = player[i][k];
    }
    return player_copy;
}

int *update_quant_grupo(int *vector, int n_grupo, int quant, int select)
{
    int i;
    int k;
    int *new_vector;

    new_vector = (int *)malloc((n_grupo+quant)*sizeof(int));
    if(!new_vector){
        printf("Nao foi possivel alocar memoria suficiente\n\n");
        exit(1);
    }
    for(i=0, k=0;i<n_grupo+quant;i++,k++){
        if(k==select  && quant == -1) k++;
        if(k==n_grupo && quant == 1) new_vector[n_grupo] = 0;
        else new_vector[i] = vector[k];
    }
    free(vector);
    return new_vector;
}

int ask_thing(int max, char select[50])
{
    int check = 0;
    int x;

    while(!check){
        printf("%s ate %d):\n",select, max);
        scanf("%d", &x);
        check = check_int(1, max, x);
    }
    return x - 1;
}

struct carta* update_grupo_hand(struct carta *grupo, int select, struct carta *player_copy, int select_card, int *quant_copy, int quant)
{
    int i;
    int k;
    struct carta *grupo_copy;

    grupo_copy = (struct carta *)malloc((quant_copy[select]+quant)*sizeof(struct carta));
    if(!grupo_copy){
        printf("Nao foi possivel alocar memoria suficiente\n\n");
        exit(1);
    }
    for(i=0, k=0; i<quant_copy[select]+quant; i++, k++){
        if(k == select_card && quant == -1) k++;
        if(k == quant_copy[select] && quant == 1) grupo_copy[k] = player_copy[select_card];
        else grupo_copy[i] = grupo[k];
    }

    quant_copy[select] += quant;
    free(grupo);

    return grupo_copy;
}


int ask_grupo_rem_mv(int grupo_ant,int n_grupo, char select[20], int *quant_grupo)
{
    int check = 0;
    int select_grupo;

    while(!check){
        printf("Digite um grupo que tera uma carta %s: (1 ate %d)\n", select, n_grupo);
        scanf("%d", &select_grupo);
        check = check_int(1,n_grupo,select_grupo);
        select_grupo--;
        if(select_grupo == grupo_ant){
            printf("Selecione um grupo diferente para adicionar a carta\n\n");
            check = 0;
        }else if(grupo_ant == -1 && quant_grupo[select_grupo] == 0){
            printf("O grupo selecionado nao possui cartas para serem removidas\n\n");
            check = 0;
        }
    }
    return select_grupo;
}

struct carta** remove_create_grupo(struct carta **grupo,int n_grupo,int *grupo_quant, int select, int quant)
{
    int i;
    int k;
    struct carta **grupo_copy;

    grupo_copy = (struct carta **)malloc((n_grupo + quant)*sizeof(struct carta *));
    if(!grupo_copy){
        printf("Nao foi possivel alocar memoria suficiente\n\n");
        exit(1);
    }
    for(i=0, k=0; i<n_grupo+quant; i++,k++){
        if(k==select && quant ==-1) k++;
        if(i== n_grupo) grupo_copy[i] = (struct carta *)malloc(1*sizeof(struct carta));
        else grupo_copy[i] = (struct carta *)malloc(grupo_quant[k] * sizeof(struct carta));
        if(!grupo_copy[i]){
            printf("Nao foi possivel alocar memoria sufuciente\n\n");
            exit(1);
        }
        grupo_copy[i] = grupo[k];
    }
    free(grupo);
    return grupo_copy;
}

int check_win(struct carta *grupo, int quant_grupo)
{
    int i;
    int k;
    int seq_win = 1;
    int grup_win = 1;
    int start;
    char naipe;

    naipe = grupo[0].cor;
    start = grupo[0].val_n;
    for(i=0; i<quant_grupo; i++){
        if(!(start+i == grupo[i].val_n || grupo[i].val_n == 20)){
            seq_win = 0;
            break;
        }else if(naipe != grupo[i].cor && grupo[i].val_n != 20){
            seq_win = 0;
            break;
        }
    }
    if(!seq_win){
        if(quant_grupo <= 4){
            start = grupo[0].val_n;
            for(i=0; i<quant_grupo; i++){
                if(start != grupo[i].val_n && grupo[i].val_n != 20){
                    grup_win = 0;
                    break;
                }
            }
            if(grup_win){
                for(i=0; i<quant_grupo; i++){
                    for(k=i+1; k<quant_grupo; k++){
                        if(grupo[i].cor == grupo[k].cor){
                            grup_win = 0;
                            break;
                        }
                    }
                }
            }
        }else grup_win = 0;
    }
    if(seq_win || grup_win) return 1;
    else return 0;
}

int main(int argc, char const *argv[])
{
    int n_jog;
    int i;
    int k;
    int n_baralho = 106;
    int n_grupo = 0;
    int n_grupo_copy;
    int select_grupo;
    int select_grupo_rem;
    int select_grupo_mv;
    int select_card;
    int first;
    int flag1;
    int check_play;
    char x;
    int *quant_mao;
    int *quant_mao_copy;
    int *quant_grupo = NULL;
    int *quant_grupo_copy;
    struct carta *p;
    struct carta **player;
    struct carta *player_copy;
    struct carta **grupo = NULL;
    struct carta **grupo_copy;
    
    p = (struct carta *)calloc(106,sizeof(struct carta));
    if(!p){
        printf("Nao foi possivel alocar memoria suficiente\n");
        printf("Encerrando o programa...\n");
        return 1;
    }
    clear_screen();
    do{
        x = choose_baralho();
        if(x == 'A' || x == 'a'){
            init_baralho_randon(p);
            break;
        }else if(x == 'B' || x == 'b'){
            init_baralho_txt(p);
            break;
        }else printf("Digite uma opcao valida\n\n");
    }while(1);
    clear_screen();
    n_jog = jog();
    first = 0;
    if(n_jog > 1){
        int repetidos[n_jog];
        for(i=0; i<n_jog; i++) repetidos[i] = i;
        first = choose_player(p,n_jog, repetidos);
    }
    int primeira_jogada[n_jog];
    int flag_primeira_play[n_jog]; 
    for(i=0; i<n_jog; i++){
        primeira_jogada[i] = 0;
        flag_primeira_play[i] = 0;
    }
    quant_mao = (int *) malloc(n_jog * sizeof(int));
    if(!quant_mao){
        printf("Nao foi possivel alocar memoria suficiente\n\n");
        return 1;
    }
    player = (struct carta **)malloc(n_jog * sizeof(struct carta *));
    if(!player){
        printf("Nao foi possivel alocar memoria suficiente\n\n");
        return 1;
    }
    for(i = 0; i<n_jog; i++){
        player[i] = (struct carta *)malloc(14*sizeof(struct carta));
        if(!player[i]){
            printf("Nao foi possivel alocar memoria suficiente\n\n");
            return 1;
       }
    }
    val_hand(player, p, n_jog, quant_mao);
    p = update_baralho(p,n_jog*14,106);
    n_baralho -= 14*n_jog;
    i = first;
    do{
        flag1 = 0;
        check_play = quant_mao[i];
        buble_sort_carta(player[i], quant_mao[i], 0);
        n_grupo_copy = n_grupo;
        quant_mao_copy = copy_info(quant_mao, n_jog);
        quant_grupo_copy = copy_info(quant_grupo, n_grupo);
        grupo_copy = copy_info_grupos(grupo, n_grupo,quant_grupo);
        player_copy = copy_info_player(player, i,quant_mao[i]);
        while(!flag1){
            show_info(grupo_copy, n_grupo_copy, n_baralho, player, i, player_copy,quant_grupo_copy, quant_mao_copy[i],0);
            x = choose_action();
            if(x == 'A' || x == 'a'){
                quant_grupo_copy = update_quant_grupo(quant_grupo_copy, n_grupo_copy, 1, 0);
                grupo_copy = remove_create_grupo(grupo_copy, n_grupo_copy, quant_grupo_copy, 0, 1);
                n_grupo_copy++;
            }else if(x == 'B' || x =='b'){
                if(n_grupo_copy > 0){
                    show_info(grupo_copy, n_grupo_copy, n_baralho, player, i, player_copy,quant_grupo_copy, quant_mao_copy[i],0);
                    select_grupo = ask_thing(n_grupo_copy, "Digite qual grupo deseja selecionar (1\0");
                    select_card = ask_thing(quant_mao_copy[i], "Digite qual carta deseja selecionar (1\0");
                    clear_screen();
                    printf("|-------------------------------------------------|\n");
                    printf("|Grupo selecionado: %d     Carta selecionada: %c%c   |\n", select_grupo+1, player_copy[select_card].val_c, player_copy[select_card].cor);
                    printf("|-------------------------------------------------|\n");
                    if(!flag_primeira_play[i]) primeira_jogada[i] += player_copy[select_card].val_n;
                    grupo_copy[select_grupo] = update_grupo_hand(grupo_copy[select_grupo], select_grupo, player_copy, select_card, quant_grupo_copy, 1);
                    player_copy = update_grupo_hand(player_copy, i,player[i],select_card, quant_mao_copy, -1);
                    buble_sort_carta(grupo_copy[select_grupo], quant_grupo_copy[select_grupo], 1);
                }else{
                    clear_screen();
                    printf("Crie um grupo primeiro\n\n");
                }
            }else if(x =='C' || x == 'c'){
                if(n_grupo_copy>1){
                    select_grupo_rem = ask_grupo_rem_mv(-1,n_grupo_copy, "removida\0", quant_grupo_copy);
                    select_card = ask_thing(quant_grupo_copy[select_grupo_rem], "Digite qual carta deseja transferir (1\0");
                    select_grupo_mv = ask_grupo_rem_mv(select_grupo_rem,n_grupo_copy, "inserida\0", quant_grupo_copy);
                    grupo_copy[select_grupo_mv] = update_grupo_hand(grupo_copy[select_grupo_mv], select_grupo_mv, grupo_copy[select_grupo_rem], select_card, quant_grupo_copy, 1);
                    grupo_copy[select_grupo_rem] = update_grupo_hand(grupo_copy[select_grupo_rem], select_grupo_rem, NULL,select_card, quant_grupo_copy, -1);
                }else printf("Crie pelo menos dois grupos\n\n");
            }else if(x == 'D' || x == 'd'){
                if(n_grupo_copy > 0){
                    select_grupo = ask_thing(n_grupo_copy, "Digite qual grupo sera dividido (1\0");
                    select_card = ask_thing(quant_grupo_copy[select_grupo], "A partir de qual carta deseja dividir? (2\0");
                    quant_grupo_copy = update_quant_grupo(quant_grupo_copy, n_grupo_copy, 1, 0);
                    grupo_copy = remove_create_grupo(grupo_copy, n_grupo_copy, quant_grupo_copy, 0, 1);
                    n_grupo_copy++;
                    for(k=select_card; k<quant_grupo_copy[select_grupo];){
                        grupo_copy[n_grupo_copy-1] = update_grupo_hand(grupo_copy[n_grupo_copy-1], n_grupo_copy-1, grupo_copy[select_grupo], select_card, quant_grupo_copy, 1);
                        grupo_copy[select_grupo] = update_grupo_hand(grupo_copy[select_grupo], select_grupo, NULL, select_card, quant_grupo_copy, -1);
                    }
                }else printf("Crie um grupo primeiro\n");
            }else if(x == 'E' || x == 'e'){
                flag1 = 1;
                for(k=0; k<n_grupo_copy; k++){
                    if(quant_grupo_copy[k] == 0){
                        quant_grupo_copy = update_quant_grupo(quant_grupo_copy, n_grupo_copy, -1, k);
                        grupo_copy = remove_create_grupo(grupo_copy, n_grupo_copy, quant_grupo_copy, k, -1);
                        n_grupo_copy--;
                        k--;
                    }
                }
                if(check_play == quant_mao_copy[i]){
                    flag1 = 0;
                    printf("Faca alguma jogada primeiro\n");
                }
                for(k=0; k<n_grupo_copy; k++){
                    if(quant_grupo_copy[k] < 3){
                        if(flag1) {
                            printf("         ERROS PRESENTES NA MESA:\n\n");
                            printf("O numero minimo de cartas em um grupo eh 3\n");
                            printf("Grupos com menos cartas: ");
                        }
                        flag1 = 0;
                        printf("%d ", k+1);
                    }
                }
                int flag2 = 1;
                if(flag1){
                    for(k=0; k<n_grupo_copy; k++){
                        flag1 =  check_win(grupo_copy[k], quant_grupo_copy[k]);
                        if(!flag1 && flag2){
                            printf("         ERROS PRESENTES NA MESA:\n\n");
                            printf("So eh permitido grupos ou sequencias\n");
                            printf("Grupos errados: ");
                            flag2 = 0;
                        }
                        if(!flag1){
                            printf("%d ", k+1);
                        }
                    }
                }
                if(flag1) flag1 = flag2;
                if(flag1 && !flag_primeira_play[i]){
                    if(primeira_jogada[i] < 30){
                        printf("A primeira jogada deve valer no minimo 30 pontos\n\n");
                        flag1 = 0;
                        primeira_jogada[i] = 0;
                    }else flag_primeira_play[i] = 1;
                }
                if(flag1){
                    if(!quant_mao_copy[i]){
                        printf("O jogador %d venceu!!\n\n", i+1);
                        free(player);
                        free(player_copy);
                        free(grupo);
                        free(grupo_copy);
                        free(quant_grupo);
                        free(quant_grupo_copy);
                        free(quant_mao);
                        free(quant_mao_copy);
                        return 0;
                    }
                    free(player[i]);
                    player[i] = player_copy;
                    free(grupo);
                    grupo = grupo_copy;
                    n_grupo = n_grupo_copy;
                    free(quant_grupo);
                    quant_grupo = quant_grupo_copy;
                    free(quant_mao);
                    quant_mao = quant_mao_copy;
                }
                printf("\n\n");
            }else if(x == 'F' || x == 'f'){
                free(quant_grupo_copy);
                free(grupo_copy);
                n_grupo_copy = 0;
                free(quant_mao_copy);
                show_hand(player, i, quant_mao[i]);
                player_copy = update_grupo_hand(player[i], i,p,0, quant_mao, 1);
                p = update_baralho(p,1,n_baralho);
                player[i] = player_copy;
                if(n_baralho>0){
                    n_baralho--;
                    clear_screen();
                    printf("Turno do jogador: %d\n\n", i+1);
                    printf("    MESA:\n\n");
                    show_mesa(grupo, n_grupo, quant_grupo);
                    show_baralho(n_baralho);
                    printf("\nSua nova mao\n\n");
                    show_hand(player, i, quant_mao[i]);
                    if(n_baralho == 0) first = i;
                }else printf("Nao ha mais cartas no baralho. Essa e a ultima rodada.\nO jogo ira continuar ate o jogador %d\n", first + 1);
                printf("\n\nAperte qualquer tecla para continuar...");
                getc(stdin);
                flag1 = 1;
            }else printf("Digite uma opcao valida\n\n");
        }
        i++;
        if(i==first && n_baralho == 0){
            int min = 0;
            int sum;
            printf("O(s) ganhador(es) eh(sao): ");
            for(i=0; i<n_jog; i++){
                sum = 0;
                for(k=0; k<quant_mao[i]; k++){
                    sum += player[i][k].val_n;
                }
                if(sum < min) min = sum;
            }
            for(i=0; i<n_jog; i++){
                sum = 0;
                for(k=0; k<quant_mao[i]; k++){
                    sum += player[i][k].val_n;
                }
                if(sum == min) printf("%d ", i+1); 
            }
        }
        if(i==n_jog) i=0;
    }while(1);
}