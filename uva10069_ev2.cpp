#include <iostream>
#include "Bignum.cpp"
using namespace std;

/* memory saving ver. with BigNum */
int main(){
	int numberOfCase;
	cin >> numberOfCase;

	string mainstr, pattern;
	while(numberOfCase-->0){
		cin >> mainstr >> pattern;
		int size_mstr=mainstr.size();
		int size_patt=pattern.size();

		bool sw=true;
		BigNum table[2][size_mstr+1];	//alternately using two row to save space
		for(int j=0;j<size_mstr;j++)
			table[0][j]=BigNum::ONE;

		for(int i=0;i<size_patt;i++,sw=!sw){
			table[sw][0]=BigNum::ZERO;
			for(int j=0;j<size_mstr;j++){
				table[sw][j+1]=table[sw][j];
				if(pattern.at(i)==mainstr.at(j))
					table[sw][j+1]=table[sw][j+1].add(table[!sw][j]);
			}
		}

		cout << table[!sw][size_mstr] << endl;
	}

	return 0;
}
