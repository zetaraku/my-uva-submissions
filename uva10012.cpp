#include <iostream>
#include <cstdio>
#include <bitset>
#include <limits>
#include <cmath>
#define MAXSIZE (8)
using namespace std;

double minIntersumOfcircles(int L, int R, int S, bitset<MAXSIZE> bs);

double circleRadius[MAXSIZE];
int numberOfCircles;

int main(){
	int numberOfCases;
	cin >> numberOfCases;

	while(numberOfCases-->0){
		cin >> numberOfCircles;

		for(int i=0;i<numberOfCircles;i++)
			cin >> circleRadius[i];

		bitset<MAXSIZE> bs;
		for(int i=numberOfCircles;i<MAXSIZE;i++)
			bs.set(i);

		double totalmin=numeric_limits<double>::infinity();
		if(numberOfCircles==1){
			totalmin = 2*circleRadius[0];
		}else if(numberOfCircles==2){
			totalmin = circleRadius[0] + 2*sqrt(circleRadius[0]*circleRadius[1]) + circleRadius[1];
		}else{
			for(int left=0;left<numberOfCircles-1;left++){
				for(int right=left+1;right<numberOfCircles;right++){
					double mininterval=numeric_limits<double>::infinity();
					bs.set(left).set(right);
					for(int i=0;i<numberOfCircles;i++){
						if(bs.test(i))continue;
						bs.set(i);
						mininterval=min(mininterval,minIntersumOfcircles(left,right,i,bs));
						bs.reset(i);
					}
					bs.reset(left).reset(right);
					totalmin = min(totalmin,circleRadius[left] + 2*mininterval + circleRadius[right]);
				}
			}
		}
		printf("%.3f\n",totalmin);
	}

	return 0;
}

double minIntersumOfcircles(int L, int R, int S, bitset<MAXSIZE> bs){
	double minval=numeric_limits<double>::infinity();
	if(bs.count()==bs.size()){
		minval=sqrt(circleRadius[S]*circleRadius[R]);
	}else{
		for(int i=0;i<numberOfCircles;i++){
			if(bs.test(i))continue;
			bs.set(i);
			minval=min(minval,minIntersumOfcircles(S,R,i,bs));
			bs.reset(i);
		}
	}

	return sqrt(circleRadius[L]*circleRadius[S])+minval;
}
