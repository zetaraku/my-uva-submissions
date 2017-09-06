#include <stdio.h>
#include <string.h>

typedef struct {
	size_t x, y;
} pair;

int main(int argc, char **argv){
	int completedCaseCount=0;

	while(1){
		int row, column;
		scanf("%d %d\n",&row,&column);

		if(!row&&!column)break;
		if(completedCaseCount)putchar('\n');

		char field[row+2][column+2];
		memset(*field, '0', (row+2)*(column+2));

		pair mines[row*column]; size_t mines_cnt=0;

		char rowline[column+1];
		size_t i, j;for(i=0;i<row;i++){
			gets(rowline);
			for(j=0;j<column;j++)
				if(rowline[j]=='*'){
					mines[mines_cnt].x=i+1,
					mines[mines_cnt].y=j+1;
					mines_cnt++;
				}
		}

		for(i=0;i<mines_cnt;i++){
			size_t r=mines[i].x, c=mines[i].y;
			++field[r-1][c-1];
			++field[r-1][c];
			++field[r-1][c+1];
			++field[r][c-1];
			++field[r][c+1];
			++field[r+1][c-1];
			++field[r+1][c];
			++field[r+1][c+1];
		}

		for(i=0;i<mines_cnt;i++){
			field[mines[i].x][mines[i].y]='*';
		}

		printf("Field #%d:\n",++completedCaseCount);
		for(i=1;i<row+1;i++){
			for(j=1;j<column+1;j++){
				putchar(field[i][j]);
			}
			putchar('\n');
		}
	}

	return 0;
}
