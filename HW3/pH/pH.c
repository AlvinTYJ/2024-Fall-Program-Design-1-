#include <stdio.h>

int main()
{
    long long a, b;
    unsigned long long sum;
    scanf("%lld %lld", &a, &b);
    
    if ((a+1) == -9223372036854775807 && (b+1) == -9223372036854775807) {
        printf("-18446744073709551616\n");
    }
    else if ((a > 0 && b < 0) || (a < 0 && b > 0)) {
        printf("%lld\n", a+b);
    }
    else if (a > 0 && b > 0) {
        sum = a + b;
        printf("%llu\n", sum);
    }
    else if (a < 0 && b < 0) {
        a = a*(-1);
        b = b*(-1);
        sum = a + b;
        printf("-%llu\n", sum);
    }
    
    return 0;
}