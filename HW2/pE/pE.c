#include <stdio.h>
#include <stdlib.h>

int main() {
    long long n1, n2, n3, n4, n5;
    char c1, c2, c3, c4;
    scanf("NCKU%lld%c%lld%c%lld%c%lld%c%lld", &n1, &c1, &n2, &c2, &n3, &c3, &n4, &c4, &n5);
    printf("\"%lld\" \"%lld\" \"%lld\" \"%lld\" \"%lld\"\n", n1, n2, n3, n4, n5);
    return 0;
}