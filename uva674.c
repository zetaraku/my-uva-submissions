#include <stdio.h>
#define MAX_CENTS (7489)
#define CENT_1 (0)
#define CENT_5 (1)
#define CENT_10 (2)
#define CENT_25 (3)
#define CENT_50 (4)
#define CENTS_TYPES (5)

int coin_value[CENTS_TYPES]={1,5,10,25,50};

int main(){
    unsigned long combination_dp[CENTS_TYPES][MAX_CENTS+1];

    size_t i,j; for(j=0;j<=MAX_CENTS;j++)
        combination_dp[CENT_1][j]=1;
    for(i=1;i<CENTS_TYPES;i++){
        for(j=0;j<=MAX_CENTS;j++){
            size_t amount=j;
            unsigned long combination=0;
            size_t now_coin_type=i;
            combination+=combination_dp[now_coin_type-1][amount];
            while(amount>=coin_value[now_coin_type]){
                amount-=coin_value[now_coin_type];
                combination+=combination_dp[now_coin_type-1][amount];
            }
            combination_dp[i][j]=combination;
        }
    }

    while(1){
        size_t amount;
        int input=scanf("%u", &amount);
        if(input==EOF)break;
        printf("%lu\n",combination_dp[CENTS_TYPES-1][amount]);
    }

    return 0;
}
