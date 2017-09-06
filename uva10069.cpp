#include <iostream>

using namespace std;

/* original ver. (without BigNum, won't work with big number) */
int main(){
	int numberOfCase;
	cin >> numberOfCase;

	string mainstr, pattern;
	while(numberOfCase-->0){
		cin >> mainstr >> pattern;
		int size_mstr=mainstr.size();
		int size_patt=pattern.size();

		long long int table[size_patt+1][size_mstr+1];

		fill(table[0],table[0]+size_mstr+1,1);
		for(int t=1;t<=size_patt;t++)table[t][0]=0;

		for(int i=0;i<size_patt;i++){
			for(int j=0;j<size_mstr;j++){
				table[i+1][j+1]=table[i+1][j];
				if(pattern.at(i)==mainstr.at(j))
					table[i+1][j+1]+=table[i][j];
			}
		}

		cout << table[size_patt][size_mstr] << endl;
	}

	return 0;
}
