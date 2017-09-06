#include <stdbool.h>
#include <stdio.h>

int main(){

    /*
    freopen("input.txt","r",stdin);
    FILE *stdans=fopen("output.txt","r");
    */

    size_t k=0;
    while(true){
        size_t nPoint;
        scanf("%u",&nPoint);

        if(nPoint==0)
            break;

        bool graph[nPoint+1][nPoint+1];
        size_t distanceFromStart[nPoint+1];
        size_t i,j; for(i=0;i<=nPoint;i++){
            distanceFromStart[i]=0;
            for(j=0;j<=nPoint;j++){
                graph[i][j]=false;
            }
        }

        size_t startPoint;
        scanf("%u",&startPoint);

        while(true){
            size_t p, q;
            scanf("%u %u",&p,&q);

            if(p==0&&q==0)break;

            graph[p][q]=true;
        }

        size_t processingStack[nPoint]; size_t processingStack_size=0;
        bool currentInStack[nPoint+1]; for(i=0;i<=nPoint;i++)currentInStack[i]=false;

        processingStack[processingStack_size++]=startPoint;
        currentInStack[startPoint]=true;

        size_t farestPoint=startPoint;
        size_t maxDistance=0;

        while(processingStack_size>0){
            size_t currPoint=processingStack[--processingStack_size];
            currentInStack[currPoint]=false;

            for(j=0;j<=nPoint;j++){
                if(!graph[currPoint][j])
                    continue;
                if(distanceFromStart[currPoint]+1>distanceFromStart[j]){
                    distanceFromStart[j]=distanceFromStart[currPoint]+1;
                    if(!currentInStack[j])
                        processingStack[processingStack_size++]=j;
                    if(distanceFromStart[j]>maxDistance
                    || distanceFromStart[j]==maxDistance && j<farestPoint){
                        farestPoint=j;
                        maxDistance=distanceFromStart[j];
                    }
                }
            }
        }

        printf("Case %lu: The longest path from %lu has length %lu, finishing at %lu.\n\n",++k,startPoint,maxDistance,farestPoint);

        /*
        char myAns[1024], expectedAns[1024];
        sprintf(myAns,"Case %u: The longest path from %u has length %u, finishing at %u.\n",k,startPoint,maxDistance,farestPoint);
        fgets(expectedAns,1024-1,stdans);
        assert(strcmp(myAns,expectedAns)==0);
        */
    }

    return 0;
}
