#include <stdio.h>
#include <stdlib.h>

int main() {
    int N;
    scanf("%d", &N);

    int i;
    //int presentTime[N+1][2];
    int **presentTime = malloc((N+1) * sizeof(int *));
    for (i=0; i<=N; i++) {
        presentTime[i] = malloc(2*sizeof(int));
    }

    //scan data
    int largestR = 0;
    for (i=1; i<=N; i++) {
        scanf("%d %d", &presentTime[i][0], &presentTime[i][1]);
        if (presentTime[i][1]>largestR) largestR = presentTime[i][1];
    }

    int d[largestR+1];
    memset(d, 0, sizeof(d));
    for (i=1; i<=N; i++) {
        d[presentTime[i][0]]++;
        d[presentTime[i][1]]--;
    }

    int currentVehiclesPresent = 0;
    int maxVehiclesPresent = 0;
    for (i=1; i<=largestR; i++) {
        currentVehiclesPresent += d[i];
        if (currentVehiclesPresent > maxVehiclesPresent) {
            maxVehiclesPresent = currentVehiclesPresent;
        }
    }
    
    /*for (i=1; i<=largestR; i++) {
        printf("d[%d] = %d ", i, d[i]);
    }*/
    printf("%d\n", maxVehiclesPresent);
    return 0;
}