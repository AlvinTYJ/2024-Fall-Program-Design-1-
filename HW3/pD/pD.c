#include <stdio.h>

int main() {
    int num, reversedNum = 0;
    scanf("%d", &num);

    while (num != 0) {
        int digit = num%10;
        reversedNum = reversedNum*10 + digit;
        num /= 10;
    }

    printf("%d\n", reversedNum);
    return 0;
}