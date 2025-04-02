#include <stdio.h>
#include <stdbool.h>

int main() {
    int a, b, c;
    bool isPresent1 = true, isPresent2 = true, isPresent3 = true;
    bool isFirst = true;
    scanf("%d %d %d", &a, &b, &c);

    if (a != 1 && b != 1 && c != 1) {
        if (!isFirst) {
            printf(" ");
        }
        printf("1");
        isFirst = false;
        isPresent1 = false;
    }
    if (a != 2 && b != 2 && c != 2) {
        if (!isFirst) {
            printf(" ");
        }
        printf("2");
        isFirst = false;
        isPresent2 = false;
    }
    if (a != 3 && b != 3 && c != 3) {
        if (!isFirst) {
            printf(" ");
        }
        printf("3");
        isFirst = false;
        isPresent3 = false;
    }
    if (isPresent1 && isPresent2 && isPresent3) {
        printf("Oh, Fried Shrimp, you're amazing!");
    }
    printf("\n");
    return 0;
}