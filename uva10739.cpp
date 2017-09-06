#include <iostream>

using namespace std;

int min3(int,int,int);
int req_operate(int,int);
int table[1000][1000];
string str;

int main(){

	int numberOfCase;
	cin >> numberOfCase;

	for(int i=1;i<=numberOfCase;i++){
		fill(table[0],table[0]+1000*1000,-1);
		cin >> str;
		cout << "Case " << i << ": " << req_operate(0,str.size()-1) << endl;
	}

	return 0;
}

int req_operate(int i, int j){

	if(i>=j)return 0;
	if(table[i][j]!=-1)return table[i][j];

	int ret;
	if(str.at(i)==str.at(j))
		ret=req_operate(i+1,j-1);
	else
		ret=1+min3(
			req_operate(i+1,j),
			req_operate(i,j-1),
			req_operate(i+1,j-1)
		);
	return table[i][j]=ret;
}

int min3(int a, int b, int c){
	return a<b?(a<c?a:c):(b<c?b:c);
}
