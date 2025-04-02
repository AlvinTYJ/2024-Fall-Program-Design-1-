#include <stdio.h>

int main() {
    int m, k;
    int magicalIndex = 0, count = 0;
    scanf("%d", &m);

    while (scanf("%d", &k) != EOF) {
        magicalIndex += k;
        count++;
        if (magicalIndex > m) {
            printf("Fried Pork!!!!\n");
            printf("%d\n", count);
            return 0;
        }
    }
    return 0;
}