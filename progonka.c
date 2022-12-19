#include <stdio.h>
#include <stdlib.h>

#define N 101 //размерность матрицы или число интервалов + 1
#define a 2 //решаем уравнение y'' = a
#define y0 0
#define yN 0
#define begin -10.
#define end 10

void fillSystem(double* A, double* f){
	double h = (end - begin) / (N - 1);
	for (int i = 0; i < N; i++)
		A[i] = !i;
	for (int i = 1; i < N - 1; i++){
		for (int j = 0; j < i - 1; j++)
			A[i*N + j] = 0;
		A[i*N + i - 1] = 1;
		A[i*N + i] = -2;
		A[i*N + i + 1] = 1;
		for (int j = i + 2; j < N; j++)
			A[i*N + j] = 0;
	}
	for (int i = 0; i < N; i++)
		A[N * (N - 1) + i] = (i == N - 1);
	f[0] = y0;
	for (int i = 1; i < N - 1; i++)
		f[i] = a * h * h;
	f[N - 1] = yN;
}

void forward(double* A, double* f, double* alpha, double* beta){
	alpha[0] = -A[1] / A[0];
	beta[0] = f[0] / A[0];
	for (int i = 1; i < N - 1; i++){
		alpha[i] = -A[i*N + i + 1] / (A[i*N + i] + alpha[i - 1] * A[i*N + i - 1]);
		beta[i] = (f[i] - beta[i - 1] * A[i*N + i - 1]) / (A[i*N + i] + alpha[i - 1] * A[i*N + i - 1]);
	}
	beta[N - 1] = (f[N - 1] - beta[N - 2] * A[N*N - 2]) / (A[N*N - 1] + alpha[N - 2] * A[N*N - 2]);
}

void backward(double* x, double* alpha, double* beta){
	x[N - 1] = beta[N - 1];
	for (int i = N - 2; i >= 0; i--)
		x[i] = alpha[i] * x[i + 1] + beta[i];
}

int main(){
	double* A = (double*)malloc(N * N * sizeof(double));
	double* x = (double*)malloc(N * sizeof(double));
	double* f = (double*)malloc(N * sizeof(double));
	double* alpha = (double*)malloc(N * sizeof(double));
	double* beta = (double*)malloc(N * sizeof(double));
	fillSystem(A, f);
	forward(A, f, alpha, beta);
	backward(x, alpha, beta);
	for (int i = 0; i < N; i++)
		printf("%lf  ", x[i]);
	free(A);
	free(x);
	free(f);
	free(alpha);
	free(beta);
	return 0;
}
