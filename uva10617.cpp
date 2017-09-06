#include <iostream>
#define undefined (-1)
using namespace std;

long long scoreout_count(int,int);
long long table[60][60];

int main(){
	int numberOfCase;
	cin >> numberOfCase;

	string str;
	while(numberOfCase-->0){
		cin >> str;
		fill(table[0],table[0]+60*60,undefined);
		cout << scoreout_count(0,str.size()-1) << endl;
	}

	return 0;
}

long long scoreout_count(int L, int R){
	if(L>R)return 0;
	if(L==R)return 1;
	if(table[L][R]!=undefined)return table[L][R];
	return table[L][R]
		= scoreout_count(L+1,R)
		+ scoreout_count(L,R-1)
		+ (str.at(L)==str.at(R) ? 1 : -scoreout_count(L+1,R-1) );
}

/*
long long scoreout_count(int L, int R){
	if(L>R)return 0;
	if(L==R)return 1;
	if(table[L][R]!=-1)return table[L][R];
	table[L][R] = scoreout_count(L+1,R) + scoreout_count(L,R-1) - scoreout_count(L+1,R-1);
	if(str.at(L)==str.at(R))table[L][R] += 1 + scoreout_count(L+1,R-1);
}
*/
