#include <cstdio>

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

		int lowavg=total/n;
		int paymore_cnt=total%n;
		int high_total=0, high_cnt=0;

		for(int money_paid: students)
			if(money_paid>lowavg){
				high_total+=money_paid;
				high_cnt++;
			}
		if(paymore_cnt>high_cnt)paymore_cnt=high_cnt;

		int money_trans=high_total-lowavg*high_cnt-1*paymore_cnt;
		printf("$%d.%02d\n",money_trans/100,money_trans%100);
	}

	return 0;
}
