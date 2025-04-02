#include <stdio.h>

int main() {
    int a, b, c;
    int total_winnings = 0;
    scanf("%d-%d-%d", &a, &b, &c);

    if (a < b) {
        total_winnings += 50;
    }
    if (a + b < c) {
        total_winnings += 150;
    }
    if (a == c) {
        total_winnings += 100;
    }
    if (a == b && b == c) {
        total_winnings += 300;
    }

    printf("%d\n", total_winnings);
    return 0;
}