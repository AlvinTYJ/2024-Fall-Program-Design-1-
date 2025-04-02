#include <stdio.h>

int main() {
    int N, C, K;
    scanf("%d %d %d", &N, &C, &K);

    int fullCycles = C / (2*N);
    int remainingCandies = C % (2*N);
    int candyCount = 2*fullCycles;

    if (remainingCandies >= K) {
        candyCount++;
    }
    if (remainingCandies >= (2*N - K + 1)) {
        candyCount++;
    }
    printf("%d\n", candyCount);
    
    return 0;
}