#include <stdio.h>
#include <math.h>

#define ROOT 5
#define INIT_VALUE 3
#define ITERS 3

#define f(x) ((x*x) - ROOT)
#define df(x) (2 * x)
#define err(x) (fabs(x - sqrt(ROOT)))

double Newton(int iters, double initValue){
	double x[2];
	x[0] = initValue;
	for (int i = 0; i < iters; i++)
		x[!(i % 2)] = x[i % 2] - f(x[i % 2]) / df(x[i % 2]);
	return x[iters % 2];
}

double oneTangent(int iters, double initValue){
	double x[2];
	x[0] = initValue;
	double c = df(initValue);
	for (int i = 0; i < iters; i++)
		x[!(i % 2)] = x[i % 2] - f(x[i % 2]) / c;
	return x[iters % 2];
}

double secant(int iters, double initValue1, double initValue2){
	double x[3];
	x[0] = initValue1;
	x[1] = initValue2;
	for (int i = 1; i < iters; i++){
		double y1 = x[i % 3], y0 = x[(i - 1) % 3];
		x[(i + 1) % 3] = y1 - f(y1) * (y1 - y0) / (f(y1) - f(y0));
	}
	return x[iters % 3];
}

int main(){
	printf("Newton's method error: %lf\n", err(Newton(ITERS, INIT_VALUE)));
	printf("One tangent method error: %lf\n", err(oneTangent(ITERS, INIT_VALUE)));
	printf("Secant method error: %lf\n", err(secant(ITERS, INIT_VALUE, Newton(1, INIT_VALUE))));
}
