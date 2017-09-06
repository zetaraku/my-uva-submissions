#include <iostream>

using namespace std;

int main(){
	int numberOfCase;
	cin >> numberOfCase;

	int G_len;
	string str;
	for(int i=0;i<numberOfCase;i++){
		cin >> G_len >> str;

		int found=0;
		for(int gpos=1;gpos+G_len<str.size();gpos++){
			for(int U_len=1;U_len<=gpos&&gpos+G_len+U_len-1<str.size();U_len++){
				bool matched=true;
				for(int upos=0;upos<U_len;upos++){
					if(str.at(gpos-U_len+upos)!=str.at(gpos+G_len+upos)){
						matched=false; break;
					}
				}
				if(matched)found++;
			}
		}
		cout << "Case " << (i+1) << ": " << found << endl;
	}

	return 0;
}
