#include <stdio.h>

int main() {
    int a, b, reversed_a = 0;
    scanf("%d %d", &a, &b);

    int a_copy = a;
    int digits = 0;

    while (a_copy > 0) {
        a_copy /= 10;
        digits++;
    }

    while (a != 0) {
        int digit2 = a%10;
        reversed_a = reversed_a*10 + digit2;
        a /= 10;
    }

    for (int i = 0; i < digits; i++) {
        b *= 10;
    }

    printf("%d\n", (b+reversed_a));
    return 0;
}