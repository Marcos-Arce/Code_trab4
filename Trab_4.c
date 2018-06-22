#include <stdio.h>
#include <stdlib.h>

struct carta{
    int val;
    char tipo;
    
};

void clear_screen(){
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

int clear(){
    int y = 1;
    char x;
    x = getchar();
    while(x!='\n'){
        x = getchar();
        y = 0;
    }
    return y;
}

char choose_baralho(){
    char x;
    int y = 0;

    while(!y){
        printf("Como deseja iniciar o baralho?\n");
        printf("Aleatoriamente -> A\n");
        printf("Por arquivo    -> B\n");
        x = getchar();
        y = clear();
    }

}



int check_int(int down_limit, int up_limit, int val){
    int y;

    y = clear();
    if(!y){
    }else if(val < down_limit || val > up_limit) y = 1;
}

int main(int argc, char const *argv[])
{
    struct carta *p;
    
    return 0;
}
