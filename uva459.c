#include <stdio.h>
#include <stdbool.h>

int main(){
    int number_of_cases;
    scanf("%d\n", &number_of_cases);

    while(number_of_cases-->0){
        char line[2+1];
        gets(line);
        char last_node_name=line[0];
        size_t max_node=last_node_name-'A'+1;

        bool graph[max_node][max_node];
        size_t i,j; for(i=0;i<max_node;i++)
            for(j=0;j<max_node;j++)
                graph[i][j]=false;

        while(true){
            char edge_node_name[2];
            char *input=gets(line); if(line[0]=='\0'||input==NULL)break;
            edge_node_name[0]=line[0];
            edge_node_name[1]=line[1];
            size_t node_a=edge_node_name[0]-'A', node_b=edge_node_name[1]-'A';
            graph[node_a][node_b]=graph[node_b][node_a]=true;
        }

        bool is_traversed[max_node];
        for(i=0;i<max_node;i++)
            is_traversed[i]=false;

        size_t mcs_count=0;
        size_t process_stack[max_node]; size_t process_stack_size=0;
        size_t start_node; for(start_node=0;start_node<max_node;start_node++){
            if(is_traversed[start_node])continue;
            mcs_count++;
            is_traversed[start_node]=true;
            process_stack[process_stack_size++]=start_node;
            while(process_stack_size>0){
                size_t node=process_stack[--process_stack_size];
                size_t neighbor; for(neighbor=0;neighbor<max_node;neighbor++){
                    if(!graph[node][neighbor])continue;
                    if(is_traversed[neighbor])continue;
                    is_traversed[neighbor]=true;
                    process_stack[process_stack_size++]=neighbor;
                }
            }
        }

        printf("%u\n",mcs_count);
        if(number_of_cases!=0)printf("\n");
    }

    return 0;
}
