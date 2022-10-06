#include <stdio.h>
#include <math.h>

#define f(x) sin(x)

double trapezoidal(double a, double b, int n){
	double len = (b - a) / n, res = 0;
	for (int i = 0; i < n; i++){
		double ai = a + len * i;
		double bi = a + len * (i + 1);
		res += (f(ai) + f(bi)) / 2 * len;
	}
	return res;
}

double simpson(double a, double b, int n){
	double len = (b - a) / n, res = 0;
	for (int i = 0; i < n; i += 2){
		double ai = a + len * i;
		double bi = a + len * (i + 2);
		res += (f(ai) + f(bi) + 4 * f((ai + bi) / 2)) / 6 * 2 * len;
	}
	return res;
}

int main(){
	double a, b;
	int n;
	printf("segment of integration:\n");
	scanf("%lf %lf", &a, &b);
	printf("number of points:\n");
	scanf("%d", &n);
	printf("trapezoidal method get %lf\n", trapezoidal(a, b, n));
	printf("Simpson method get %lf\n", simpson(a, b, n));
}
