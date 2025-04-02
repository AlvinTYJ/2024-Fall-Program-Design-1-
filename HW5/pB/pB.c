#include <stdio.h>
#include <stdlib.h>

int main() {
    int N;
    scanf("%d", &N);

    int i, j;
    //int presentTime[N+1][2];
    int **presentTime = malloc((N+1) * sizeof(int *));
    for (i=0; i<=N; i++) {
        presentTime[i] = malloc(2*sizeof(int));
    }

    int largestR = 0;
    for (i=1; i<=N; i++) {
        scanf("%d %d", &presentTime[i][0], &presentTime[i][1]);
        if (presentTime[i][1]>largestR) largestR = presentTime[i][1];
    }
    
    //short int isPresent[N+1][largestR+1];
    short int **isPresent = calloc(N+1, sizeof(short int *));
    for (i=0; i<=N; i++) {
        isPresent[i] = calloc(largestR+1, sizeof(short int));
    }

    for (i=1; i<=N; i++) {
        for (j=presentTime[i][0]; j<presentTime[i][1]; j++) {
            isPresent[i][j] = 1;
        }
    }

    int count;
    int maxVehiclesPresent = 0;
    for (j=1; j<=largestR; j++) {
        count = 0;
        for (i=1; i<=N; i++) {
            count += isPresent[i][j];
        }
        if (count > maxVehiclesPresent) maxVehiclesPresent = count;
    }

    //for checking
    /*for (int i=1; i<=N; i++) {
        for (int j=1; j<=largestR; j++) {
            printf("%d ", isPresent[i][j]);
        }
        printf("\n");
    }*/
    printf("%d\n", maxVehiclesPresent);
    return 0;
}