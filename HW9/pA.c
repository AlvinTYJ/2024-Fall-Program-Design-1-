#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef double (*F)(double, int);

double power(double x, int n) {
    return pow(x, n);
}

double multiply(double x, int n) {
    x = x * n;
    return x;
}

double divide(double x, int n) {
    x = x / n;
    return x;
}

double powerpower(F func, double x, int n, int m) {
    double res = pow(func(x, n), m);
    printf("%.6lf\n", res);
}

double powermultiply(F func, double x, int n, int m) {
    x = func(x,n) * m;
    printf("%.6lf\n", x);
}

double powerdivide(F func, double x, int n, int m) {
    x = func(x,n) / m;
    printf("%.6lf\n", x);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Error input.\n");
        return 1;
    }

    double x = atof(argv[1]);
    int n = atoi(argv[2]);
    int m = atoi(argv[3]);

    powerpower(power,x,n,m);
    powerpower(multiply,x,n,m);
    powerpower(divide,x,n,m);
    powermultiply(power,x,n,m);
    powermultiply(multiply,x,n,m);
    powermultiply(divide,x,n,m);
    powerdivide(power,x,n,m);
    powerdivide(multiply,x,n,m);
    powerdivide(divide,x,n,m);

    return 0;
}
