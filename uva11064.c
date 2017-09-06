#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#define PRIME_SIZE (46341)

long long primes_list[PRIME_SIZE]; size_t primes_count = 0;
bool is_prime[PRIME_SIZE];

int main() {

	/* build prime table & prime list */
	size_t i,j;
	for(i=2;i<PRIME_SIZE;i++)
		is_prime[i] = true;
	for(i=2;i<PRIME_SIZE;i++){
		if(is_prime[i]){
			primes_list[primes_count++] = i;
			for(j=i*2;j<PRIME_SIZE;j+=i)
				is_prime[j] = false;
		}
	}

	/* foreach input: */
	long long n;
	while(true) {
		int input_read = scanf("%lld", &n);
		if(input_read==EOF)break;
		
		/* special case */
		if(n==0){
			printf("0\n");
			continue;
		}

		/* Prime factor table */
		long long pfactors[PRIME_SIZE];
		long long pfactors_exp[PRIME_SIZE];
		size_t pfactors_count = 0;

		long long num = n;
		
		/* Prime-Factorization */
		for(i=0;i<primes_count&&num!=1;i++) {
			long long prime=primes_list[i];
			if(num%prime==0) {
				pfactors[pfactors_count] = prime;
				pfactors_exp[pfactors_count] = 0;
				do {
					num/=prime;
					pfactors_exp[pfactors_count]++;
				} while(num%prime==0);
				pfactors_count++;
			}
		}
		if(num!=1) {
			pfactors[pfactors_count] = num;
			pfactors_exp[pfactors_count] = 1;
			pfactors_count++;
			/* num/=num; */
		}
		
		/* Euler's totient function */
		long long phi = n;
		for(i=0;i<pfactors_count;i++)
			phi = phi/pfactors[i]*(pfactors[i]-1);

		long long factor_counts = 1;
		for(i=0;i<pfactors_count;i++)
			factor_counts *= (pfactors_exp[i]+1);
		
		printf("%lld\n", n - phi - factor_counts + 1);
	}
	
	return 0;
}
