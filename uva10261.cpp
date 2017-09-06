#include <cstdlib>
#include <iostream>
#include <vector>
#include <map>
using namespace std;

vector<int> cars_lengths;
bool **table;

int main(){	//uncompleted!
	int numberOfCase;
	cin >> numberOfCase;

	int ferry_length;
	while(numberOfCase-->0){
		cin >> ferry_length;
		ferry_length*=100;

		int len;
		while(true){
			cin >> len;
			if(len==0)break;
			cars_lengths.push_back(len);
		}

		ferry_load(ferry_length,ferry_length,cars_lengths.size()-1);
	}

	return 0;
}


bool ferry_load(int L_cap, int R_cap, int N){
	if(N==0)return true;
	return cars_lengths.at(N)<=L_cap && ferry_load(L_cap-cars_lengths.at(N),R_cap,N-1)
		|| cars_lengths.at(N)<=R_cap && ferry_load(L_cap,R_cap-cars_lengths.at(N),N-1);
}

