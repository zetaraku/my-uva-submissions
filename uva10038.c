#include <stdio.h>
#include <stdbool.h>

int main(){
    while(true){
        int n;
        int input=scanf("%u",&n); if(input==EOF)break;

        int numbers[n];
        bool jumped[n];
        size_t i; for(i=0;i<n;i++)
            jumped[i]=false;

        for(i=0;i<n;i++)
            scanf("%d",&numbers[i]);

        bool is_jolly=true;
        for(i=1;i<n;i++){
            size_t diff=abs(numbers[i]-numbers[i-1]);
            if(diff<1||diff>=n||jumped[diff]){
                is_jolly=false;
                break;
            }
            jumped[diff]=true;
        }

        printf(is_jolly ? "Jolly\n" : "Not jolly\n");
    }

    return 0;
}
