#include <iostream>
#include <vector>

using namespace std;

int main(){
	int numberOfCase;
	cin >> numberOfCase;

	string mainstr, substring;
	int numberOfSubstr;

	for(int i=0;i<numberOfCase;i++){
		cin >> mainstr;

		cin >> numberOfSubstr;
		for(int j=0;j<numberOfSubstr;j++){
			cin >> substring;

			bool matched=false;

			cout << (matched ? 'y' : 'n') << endl;
		}
	}

	return 0;
}
