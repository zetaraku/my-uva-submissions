#include <stdio.h>
#include <math.h>

/* #include "clamart_formula.c" */
	#ifndef INFINITY
	#define INFINITY (1.0/0.0)
	#endif

	typedef double point2d[2];
	typedef double matrix2d[2][2];
	typedef double matrix2d_aug[2][3];

	double determine2d(matrix2d A){
		return A[0][0]*A[1][1]-A[0][1]*A[1][0];
	}

	int clamart_2d(matrix2d_aug abc, point2d ret){
		matrix2d m_delta0={{abc[0][0],abc[0][1]},{abc[1][0],abc[1][1]}};
		double delta0=determine2d(m_delta0);
		matrix2d m_deltax={{abc[0][2],abc[0][1]},{abc[1][2],abc[1][1]}};
		double deltax=determine2d(m_deltax);
		matrix2d m_deltay={{abc[0][0],abc[0][2]},{abc[1][0],abc[1][2]}};
		double deltay=determine2d(m_deltay);

		if(delta0==0){
			if(deltax==0&&deltay==0)
				return INFINITY;
			else
				return 0;
		}else{
			ret[0]=deltax/delta0;
			ret[1]=deltay/delta0;
			return 1;
		}
	}
/* end of include */

typedef struct {
	double x, y;
} Vector;
typedef Vector Point;

double dot_product(Vector *a, Vector *b) {
	return a->x*b->x + a->y*b->y;
}

double distance2_of(Point *a, Point *b) {
	double xdet=a->x-b->x, ydet=a->y-b->y;
	return xdet*xdet + ydet*ydet;
}

int main(int argc, char const *argv[]) {
	size_t i, j;
	int k=0;
	while(1){
		Point A, B;
		size_t N, Q;
		scanf("%lf %lf %lf %lf %lu %lu", &A.x, &A.y, &B.x, &B.y, &N, &Q);

		if(N==0&&Q==0)
			break;

		printf("Case %d:\n", ++k);

		Point A_B={(A.x+B.x)/2,(A.y+B.y)/2};
		Vector AB={B.x-A.x,B.y-A.y};

		Point points[N];
		for(i=0;i<N;i++)
			scanf("%lf %lf", &points[i].x, &points[i].y);

		size_t querycid;
		for(i=0;i<Q;i++){
			scanf("%lu", &querycid); querycid--;
			Point C=points[querycid];

			Point A_C={(A.x+C.x)/2,(A.y+C.y)/2};
			Vector AC={C.x-A.x,C.y-A.y};
			matrix2d_aug abc={
				{AB.x,AB.y,dot_product(&AB,&A_B)},
				{AC.x,AC.y,dot_product(&AC,&A_C)}
			};

			point2d ccr;
			double cr, cr2;
			int ans_count=clamart_2d(abc,ccr);

			if(ans_count!=1){
				puts("Impossible");
			}else{
				Point cc={ccr[0],ccr[1]};
				cr2=distance2_of(&cc,&C), cr=sqrt(cr2);
				/* printf("%d: %lf, %lf (%lf)\n", ans_count, cc.x, cc.y, cr); */
				if(cr>100000){
					puts("Impossible");
				}else{
					int count=3;
					for(j=0;j<N;j++){
						Point p=points[j];
						if(fabs(p.x-cc.x)>cr||fabs(p.y-cc.y)>cr||querycid==j)
							continue;
						if(distance2_of(&p,&cc)<=cr2)
							count++;
					}
					printf("%d\n", count);
				}
			}
		}
	}

	return 0;
}