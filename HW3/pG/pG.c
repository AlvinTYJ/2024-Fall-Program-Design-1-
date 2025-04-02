#include <stdio.h>

int main()
{
    long long a, b;
    long long Llong_max = 9223372036854775807;
    long long Llong_min = -9223372036854775807;
    scanf("%lld %lld", &a, &b);

    if (a > 0 && b > 0 && (a > Llong_max - b)) {
        printf("Yes\n");
    }
    else if (a < 0 && b < 0 && (a < Llong_min - 1 - b)) {
        printf("Yes\n");
    }
    else {
        printf("No\n");
    }
    
    return 0;
}