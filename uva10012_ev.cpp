#include <iostream>
#include <cstdio>
#include <vector>
#include <bitset>
#include <limits>
#include <cmath>
#define MAXSIZE (8)
using namespace std;

void minIntersumOfcircles(int S);

class Circle {
public:
	double r;
	double x, y;
	Circle(double r, double x, double y) :r(r), x(x), y(y){}
	double distancesq_from(Circle& c2){
		return pow(x-c2.x,2)+pow(y-c2.y,2);
	}
};

double circleRadius[MAXSIZE];
int numberOfCircles;
vector<Circle> circles;
bitset<MAXSIZE> bs;
double minWidth;
vector<double> rbounds={0};

int main(){
	int numberOfCases;
	cin >> numberOfCases;

	while(numberOfCases-->0){
		cin >> numberOfCircles;
		for(int i=0;i<numberOfCircles;i++)cin >> circleRadius[i];
		bs.reset();
		for(int i=numberOfCircles;i<MAXSIZE;i++)bs.set(i);
		minWidth=numeric_limits<double>::infinity();
		for(int i=0;i<numberOfCircles;i++)
			if(!bs.test(i))
				minIntersumOfcircles(i);
		printf("%.3f\n",minWidth);
	}

	return 0;
}

void minIntersumOfcircles(int S){
	bs.set(S);

	Circle c(circleRadius[S],circleRadius[S],circleRadius[S]);

	if(!circles.empty()){
		Circle& c_left=circles.back();
		c.x=c_left.x+2*sqrt(c_left.r*c.r);	//push right from left circle
		if(c.x<c.r)c.x=c.r;					//push right from left border
	}

	for(auto it=circles.rbegin();++it!=circles.rend();){
		Circle& c_left=*it;
		if(c_left.distancesq_from(c)<pow(c_left.r+c.r,2)){
			c.x=c_left.x+2*sqrt(c_left.r*c.r);	//push right
			//c.y=c_left.y+(c.r-c_left.r);
		}
		if(c_left.r>=c.r)break;
	}

	circles.push_back(c);
	rbounds.push_back(max(rbounds.back(),c.x+c.r));

	if(bs.count()==bs.size())
		minWidth=min(minWidth,rbounds.back());
	else
		for(int i=0;i<numberOfCircles;i++)
			if(!bs.test(i))
				minIntersumOfcircles(i);

	circles.pop_back();
	rbounds.pop_back();

	bs.reset(S);

	return;
}
