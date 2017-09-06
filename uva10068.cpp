#include <iostream>
#include <utility>
#include <queue>
#include <vector>
#define BLANK (-1)
#define BLOCK (-2)
#define START (-3)
#define END (-4)
using namespace std;

int main(){
	int row, column;
	cin >> row >> column;
	int maze[row][column];
	
	int treasure_count=0;
	int blockcounts = row*column;
	char tmpc;
	vector< int,pair<int,int> > treasure_pos;
	for(int i=0;i<row;i++){
		for(int j=0;j<column;j++){
			cin >> tmpc;
			if(tmpc=='.')mazez=BLANK;
			else if(tmpc=='#')*p=BLOCK;
			else if(tmpc=='S')*p=START;
			else if(tmpc=='T')*p=END;
			else if(tmpc=='*'){
				*p=treasure_count++;
				treasure_pos.push_back(make_pair())
			}
		}
	}
	
	int walk_energy; cin >> walk_energy;
	int pickup_energy[treasure_count], carry_energy[treasure_count];
	int distance_between[treasure_count+2][treasure_count+2];
	
	for(int i=0;i<)
	int rootr, rootc;
	queue<>
}
