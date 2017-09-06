#include <iostream>
#include <vector>

using namespace std;

int main(){
	int numberOfCase;
	cin >> numberOfCase;

	int G_len;
	string mainstr;

	for(int i=0;i<numberOfCase;i++){
		cin >> G_len >> mainstr;

		vector<int> posx['a'+26];
		for(int j=0;j<mainstr.size();j++)
			posx[mainstr.at(j)].push_back(j);

		int found=0;
		for(char j='a';j<='z';j++){
			//char c='a'+j;
			vector<int>::const_iterator endj=posx[j].end();
			for(vector<int>::const_iterator k1=posx[j].begin();k1!=endj;k1++){
				for(vector<int>::const_iterator k2=k1+1;k2!=endj;k2++){
					int dK=*k2-*k1;
					if(dK<=G_len)continue;
					int U_len=dK-G_len;
					if(*k2+U_len>mainstr.size())continue;

					bool matched=true;
					for(int t=1,t1=*k1+1,t2=*k2+1;t<U_len;t++,t1++,t2++){
						if(mainstr.at(t1)!=mainstr.at(t2)){
							matched=false; break;
						}
					}
					if(matched){
						found++;
						//cout << mainstr << endl;
						//cout << string(*k1,' ') << string(U_len,'-') << string(G_len,' ') << string(U_len,'-') << endl;
					}
				}
			}
		}
		cout << "Case " << (i+1) << ": " << found << endl;
	}

	return 0;
}
