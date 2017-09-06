#include <iostream>
#include <vector>
#include <utility>
using namespace std;

int main(){

	int completedCaseCount=0;

	while(true){
		int row, column;
		cin >> row >> column;

		if(!row&&!column)break;
		if(completedCaseCount)cout << endl;

		char field[row+2][column+2];
		fill(*field, *field+(row+2)*(column+2), '0');
		vector< pair<int,int> > mines;

		string rowline;
		for(int i=0;i<row;++i){
			cin >> rowline;
			for(int j=0;j<column;j++)
				if(rowline.at(j)=='*')
					mines.push_back(make_pair(i,j));
		}

		for(pair<int,int> mine: mines){
			int r=mine.first+1, c=mine.second+1;
			++field[r-1][c-1];
			++field[r-1][c];
			++field[r-1][c+1];
			++field[r][c-1];
			++field[r][c+1];
			++field[r+1][c-1];
			++field[r+1][c];
			++field[r+1][c+1];
		}

		for(pair<int,int> mine: mines){
			field[mine.first+1][mine.second+1]='*';
		}

		cout << "Field #" << ++completedCaseCount << ":" << endl;
		for(int i=1;i<row+1;i++){
			for(int j=1;j<column+1;++j){
				cout << (field[i][j]);
			}
			cout << endl;
		}
	}

	return 0;
}
