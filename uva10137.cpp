#include <cstdio>
#include <algorithm>
#include <functional>

using namespace std;

int main(){
	int n;
	while(true){
		scanf("%d",&n);
		if(n==0)break;

		int students[n];
		int total=0;
		int num_a, num_b;
		for(int i=0;i<n;i++){
			scanf("%d.%2d", &num_a, &num_b);
			students[i]=num_a*100+num_b;
			total+=students[i];
		}
		
		int lowavg=total/n, highavg=lowavg+1;
		int paymore_cnt=total%n;
		sort(students,students+n,std::greater<int>());

		int money_trans=0;
		for(int i=0;i<paymore_cnt&&students[i]>highavg;i++)
			money_trans+=students[i]-highavg;
		for(int i=paymore_cnt;i<n&&students[i]>lowavg;i++)
			money_trans+=students[i]-lowavg;
		
		printf("$%d.%02d\n",money_trans/100,money_trans%100);
	}

	return 0;
}
