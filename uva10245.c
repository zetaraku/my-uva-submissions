#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <float.h>

/* define NAN and INFINITY for c89 */
const double NAN = (0./0.);
const double INFINITY = (1./0.);

/* handle NAN value in c89 */
double fmin(double v1, double v2) {
	return
		isnan(v1) ? v2 :
		isnan(v2) ? v1 :
		v1 < v2   ? v1 : v2;
}

typedef struct {
	double x;
	double y;
} Point;

double distance_of(Point *a, Point *b) {
	return sqrt(pow(a->x-b->x,2)+pow(a->y-b->y,2));
}

int point_comp_xy(const void *ap, const void *bp) {
	const Point *a=*(Point **)ap, *b=*(Point **)bp;
	if(a->x != b->x)
		return (a->x - b->x < 0) ? -1 : +1;
	if(a->y != b->y)
		return (a->y - b->y < 0) ? -1 : +1;
	return 0;
}

double find_closest_dist_on_vertline(Point **from, Point **to) {
	int count = (to+1)-from;
	double min_distance = INFINITY;
	if(count==1){
		return min_distance;
	} else {
		Point **p; for(p=from;p<=to-1;p++)
			if( p[1]->y - p[0]->y < min_distance )
				min_distance = p[1]->y - p[0]->y;
		return min_distance;
	}
}

double find_closest_dist(Point **from, Point **to) {
	int count = (to+1)-from;
	if(count==0){
		return NAN;
	}else if(count==1){
		return INFINITY;
	}else if(count==2){
		return distance_of(*from,*to);
	}else{
		Point **wall=&from[count/2];
		double x_median=(*wall)->x;
		while( wall>from && (*wall-1)->x == x_median )wall--;

		double ldist = find_closest_dist(from, wall-1);
		double rdist;
		double min_dist;

		if(isnan(ldist)){	/* when unable to depart anything from left side, slice off the group */
			while( wall<=to && (*wall)->x == x_median )wall++;

			ldist=find_closest_dist_on_vertline(from, wall-1);
			rdist=find_closest_dist(wall, to);
			min_dist = fmin(ldist,rdist);

			if(isnan(rdist))
				return ldist;
			else
				x_median = (*wall)->x;
		} else {
			rdist=find_closest_dist(wall, to);
			min_dist = fmin(ldist,rdist);
		}

		/* merge */
		double new_distance = NAN;
		Point **lwall; for(lwall=wall-1;lwall>=from;lwall--){
			if( x_median - (*lwall)->x > min_dist )break;
			
			Point **rwall; for(rwall=wall;rwall<=to;rwall++){
				if( (*rwall)->x - x_median > min_dist )break;
				
				if( fabs( (*rwall)->y - (*lwall)->y ) > min_dist )continue;
				
				double distance = distance_of(*lwall,*rwall);
				if(distance < min_dist)
					new_distance = min_dist = distance;
			}
		}
		return !isnan(new_distance) ? new_distance :
			ldist < rdist ? ldist : rdist;
	}
}

int main(int argc, char const *argv[])
{
	Point *points[10000];
	int i; for(i=0;i<10000;i++)
		points[i]=(Point *)malloc(sizeof(Point));
	
	int count;
	while(1){
		scanf("%d",&count);
		if(!count)break;
		/*int i;*/ for(i=0;i<count;i++){
			double x, y;
			scanf("%lf %lf", &x, &y);
			points[i]->x=x;
			points[i]->y=y;
		}

		qsort(points, count, sizeof(Point *), point_comp_xy);
		double closest_dist = find_closest_dist(points,points+count-1);
		
		if (closest_dist < 10000 || fabs(closest_dist - 10000) < 1e-7){
			printf("%.4lf\n", closest_dist);
		}else{
			printf("INFINITY\n");
		}
	}
	return 0;
}
