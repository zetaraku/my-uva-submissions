#include <iostream>
#include <vector>
using namespace std;

class BigNum {
private:
	bool negsign=false;
	vector<char> data;

	BigNum(bool sign, vector<char> numdata) :negsign(sign), data(numdata){

	}

	static int part_cmp(char* a, char* b, int length){
		for(int i=length-1;i>=0;i--)
			if(*(a+i)!=*(b+i))
				return *(a+i)-*(b+i);
		return 0;
	}

	static vector<char> _add(const vector<char>& nbig, const vector<char>& nsmall){
		int longsize, shortsize;
		longsize=nbig.size(), shortsize=nsmall.size();
		vector<char> result;
		bool carry=0;
		for(int i=0;i<shortsize;i++){
			int r=nbig.at(i)+nsmall.at(i)+carry;
			result.push_back(r%10);
			carry=r/10;
		}
		for(int i=shortsize;i<longsize;i++){
			int r=nbig.at(i)+carry;
			result.push_back(r%10);
			carry=r/10;
		}
		if(carry)result.push_back(carry);

		return result;
	}
	static vector<char> _sub(const vector<char>& nbig, const vector<char>& nsmall){
		int longsize, shortsize;
		longsize=nbig.size(), shortsize=nsmall.size();

		vector<char> result;
		bool carry=0;
		for(int i=0;i<shortsize;i++){
			int r=nbig.at(i)-nsmall.at(i)-carry;
			if(carry=(r<0))r+=10;
			result.push_back(r);
		}
		for(int i=shortsize;i<longsize;i++){
			int r=nbig.at(i)-carry;
			if(carry=(r<0))r+=10;
			result.push_back(r);
		}

		return result;
	}
	static vector<char> _mul(const vector<char>& a, const vector<char>& b){
		vector<char> result(a.size()+b.size());
		char cache[a.size()+1];		//TODO: use 1~9 table to speed up

		for(int j=0;j<b.size();j++){
			char carry=0;
			cache[0]=0;
			for(int i=0;i<a.size();i++){
				cache[i]+=a.at(i)*b.at(j)+carry;	//0~99
				cache[i+1]=cache[i]/10;
				cache[i]%=10;
			}

			for(int k=j;k<=j+a.size();k++){
				result.at(k)+=cache[k-j];
				if(result.at(k)>9){					//0~18
					result.at(k+1)++;
					result.at(k)-=10;
				}
			}
		}

		if(result.back()==0)result.pop_back();
		return result;
	}
	static vector<char> _div(const vector<char>& a, const vector<char>& b){
		vector<char> result(a.size()-b.size()+1);
		char cache[10][b.size()+1];		//TODO: use 1~9 table to speed up

		for(int i=0;i<=9;i++){
			char carry=0;
			cache[i][0]=0;
			for(int j=0;j<b.size();j++){
				cache[i][j]+=a.at(i)*b.at(j)+carry;	//0~99
				cache[i][j+1]=cache[i][j]/10;
				cache[i][j]%=10;
			}
		}

		vector<char> n(a);
		for(int i=a.size()-1;i-b.size()>=-1;i--){
			//while(part_cmp())
		}
	}
public:
	friend ostream& operator<<(ostream&, const BigNum&);
	static const BigNum ZERO, ONE, NEGONE;

	BigNum() {
		data.push_back(0);
	}
	BigNum(string num) {
		if(num.at(0)=='-')num.erase(num.begin()),negsign=true;
		else if(num.at(0)=='+')num.erase(num.begin()),negsign=false;
		for(auto it=num.rbegin();it!=num.rend();it++)data.push_back(*it-'0');
	}
	BigNum(long long num) {
		if(num<0)num*=-1,negsign=true;
		while(num>0)data.push_back(num%10),num/=10;
		if(!data.size())data.push_back(0);
	}

	string tostr() const {
		string str;
		if(negsign)str+='-';
		for(auto rit=data.rbegin();rit!=data.rend();rit++)
			str+=*rit+'0';
		return str;
	}

	BigNum add(BigNum n){
		BigNum *a=this, *b=&n;
		if(abscmp(*a,*b)>0)swap(a,b);
		if(a->negsign xor b->negsign)return BigNum(b->negsign,_sub(b->data,a->data));
		else return BigNum(b->negsign,_add(b->data,a->data));
	}
	BigNum sub(BigNum n){
		BigNum *a=this, *b=&n;
		if(abscmp(*a,*b)>0)swap(a,b);
		if(a->negsign xor !b->negsign)return BigNum(!b->negsign xor a!=this,_sub(b->data,a->data));
		else return BigNum(!b->negsign xor a!=this,_add(b->data,a->data));
	}
	BigNum mul(BigNum n){
		return BigNum(negsign xor n.negsign,_mul(data,n.data));
	}
	BigNum div(BigNum n){
		return BigNum(negsign xor n.negsign,_div(data,n.data));
	}

	BigNum neg(){
		return BigNum(!negsign,data);
	}

	static int abscmp(BigNum a, BigNum n){
		if(a.data.size()!=n.data.size())return a.data.size()-n.data.size();
		for(int i=a.data.size()-1;i>=0;i--)
			if(a.data.at(i)!=n.data.at(i))
				return a.data.at(i)-n.data.at(i);
		return 0;
	}
	static int cmp(BigNum a, BigNum n){
		if(a.negsign xor n.negsign)return n.negsign-a.negsign;
		if(a.data.size()!=n.data.size())return (a.data.size()-n.data.size()) * (1-2*n.negsign);
		for(int i=a.data.size()-1;i>=0;i--)
			if(a.data.at(i)!=n.data.at(i))
				return (a.data.at(i)-n.data.at(i)) * (1-2*n.negsign);
		return 0;
	}
};
ostream& operator<<(ostream& os, const BigNum& object){
	if(object.negsign)os << '-';
	for(auto rit=object.data.rbegin();rit!=object.data.rend();rit++)
		os << (int)*rit;
	return os;
}
const BigNum BigNum::ZERO(0);
const BigNum BigNum::ONE(1);
const BigNum BigNum::NEGONE(-1);
