#include <stdio.h>
#include <stdlib.h>

int f(int x, int y, int z) {
    return ((x+z)^(y-z)) - (x&z&(y&2024)|abs(z-y));
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);
    
    int maxValue = f(a, b, c);
    maxValue = max(maxValue, f(a, c, b));
    maxValue = max(maxValue, f(b, a, c));
    maxValue = max(maxValue, f(b, c, a));
    maxValue = max(maxValue, f(c, a, b));
    maxValue = max(maxValue, f(c, b, a));

    printf("%d\n", maxValue);
    return 0;
}