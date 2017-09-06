#include <iostream>

using namespace std;

/* memory saving ver. (without BigNum) */
int main(){
	int numberOfCase;
	cin >> numberOfCase;
	string mainstr, pattern;

	while(numberOfCase-->0){
		cin >> mainstr >> pattern;
		int size_mstr=mainstr.size();
		int size_patt=pattern.size();

		bool sw=true;
		long long int table[2][size_mstr+1];

		fill(table[0],table[0]+size_mstr+1,1);

		for(int i=0;i<size_patt;i++,sw=!sw){
			table[sw][0]=0;
			for(int j=0;j<size_mstr;j++){
				table[sw][j+1]=table[sw][j];
				if(pattern.at(i)==mainstr.at(j))
					table[sw][j+1]+=table[!sw][j];
			}
		}

		cout << table[!sw][size_mstr] << endl;
	}

	return 0;
}
