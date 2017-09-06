#include <iostream>
#include <vector>
#define ull_scale 1000000000u
using namespace std;

typedef unsigned long long ull;

static vector<ull> _mul(const vector<ull>& a, const vector<ull>& b){
	int a_siz=a.size(), b_siz=b.size();
	vector<ull> result(a_siz+b_siz+1);
	ull cache[a_siz+1];

	for(int j=0;j<b_siz;j++){
		ull carry=0;
		cache[0]=0;
		for(int i=0;i<a_siz;i++){
			cache[i]+=a.at(i)*b.at(j)+carry;
			cache[i+1]=cache[i]/ull_scale;
			cache[i]%=ull_scale;
		}

		for(int k=j;k<=j+a_siz;k++){
			result.at(k)+=cache[k-j];
			if(result.at(k)>=ull_scale){
				result.at(k+1)+=result.at(k)/ull_scale;
				result.at(k)%=ull_scale;
			}
		}
	}

	while(result.size() && result.back()==0)
		result.pop_back();

	return result;
}

int main(){
	vector<ull> T[1001]={{1}};
	vector<ull> x={1};
	for(unsigned int i=1;i<=1000;i++)
		T[i]=x=_mul(x,vector<ull>{i});

	int num;
	while(cin >> num){
		int sum=0;
		for(ull i: T[num])
			while(i>0)
				sum+=i%10,i/=10;
		cout << sum << endl;
	}

	return 0;
}
