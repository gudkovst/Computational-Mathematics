#include <stdio.h>
#include <math.h>

#define f(x) (x*x*x + a*x*x + b*x + c)
#define isRoot(x) (fabs(f(x)) <= eps)

double a, b, c, eps, delta;

double finFind(double t, double s){
    double p = (t + s) / 2;
    double min = t < s? t : s;
    double max = t + s - min;
    if (isRoot(p))
        return p;
    if (f(p) * f(min) < 0)
        return finFind(min, p);
    return finFind(p, max);
}

double infFind(int orient, double p){ // -1 - -inf, 1 - +inf
    double step = delta;
    int k = 0;
    for (; f(p) * f((p + orient * step)) >= 0; step *= 2, k++);
    return finFind(p + orient * step/2 * (!!k), p + orient * step);
}

int main(){
    double halfDisc, alpha, beta;
    printf("coefficients of reduced polynomial:\n");
    scanf("%lf %lf %lf", &a, &b, &c);
    printf("epsilon and delta:\n");
    scanf("%lf %lf", &eps, &delta);
    printf("x^3 + %lfx^2 + %lfx + %lf = 0 <=>\n", a, b, c);
    halfDisc = a*a - 3*b; //половина D
    if (halfDisc <= eps*eps * a*a){
        if (isRoot(0))
            printf("x = 0\n");
        if (f(0) < -eps)
            printf("x = %lf\n", infFind(1, 0));
        if (f(0) > eps)
            printf("x = %lf\n", infFind(-1, 0));
        return 0;
    }
    alpha = (-a - sqrt(halfDisc)) / 3;
    beta = (-a + sqrt(halfDisc)) / 3;
    if (f(alpha) > eps && f(beta) > eps)
        printf("x = %lf\n", infFind(-1, alpha));
    else if (f(alpha) < -eps && f(beta) < -eps)
        printf("x = %lf\n", infFind(1, beta));
    else if (f(alpha) > eps && isRoot(beta)){
        printf("x = %lf\n", infFind(-1, alpha));
        printf("x = %lf\n", beta);
        printf("x = %lf\n", beta);
    }
    else if (isRoot(alpha) && f(beta) < -eps){
        printf("x = %lf\n", alpha);
        printf("x = %lf\n", alpha);
        printf("x = %lf\n", infFind(1, beta));
    }
    else if (f(alpha) > eps && f(beta) < -eps){
        printf("x = %lf\n", infFind(-1, alpha));
        printf("x = %lf\n", finFind(alpha, beta));
        printf("x = %lf\n", infFind(1, beta));
    }
    else if (isRoot(alpha) && isRoot(beta))
        printf("x = %lf\n", (alpha + beta) / 2);
    return 0;
}