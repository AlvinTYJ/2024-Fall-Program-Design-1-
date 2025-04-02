#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    int i, j;
    int **h = malloc(n*sizeof(int *));
    for (i=0; i<n; i++) {
        h[i] = malloc(m*sizeof(int));
    }
    for (i=0; i<n; i++) {
        for (j=0; j<m; j++) {
            scanf("%d", &h[i][j]);
        }
    }

    int northSouthSkyline[m];
    int eastWestSkyline[n];
    memset(northSouthSkyline, 0, sizeof(northSouthSkyline));
    memset(eastWestSkyline, 0, sizeof(eastWestSkyline));
    for (j=0; j<m; j++) {
        for (i=0; i<n; i++) {
            northSouthSkyline[j] = max(northSouthSkyline[j], h[i][j]);
        }
    }
    
    for (i=0; i<n; i++) {
        for (j=0; j<m; j++) {
            eastWestSkyline[i] = max(eastWestSkyline[i], h[i][j]);
        }
    }
    for (i=0; i<n; i++) {
        printf("%d ", eastWestSkyline[i]);
    }
    printf("\n");

    long long int increasedHeight;
    for (i=0; i<n; i++) {
        for (j=0; j<m; j++) {
            increasedHeight += (min(northSouthSkyline[j], eastWestSkyline[i])-h[i][j]);
            //h[i][j] = min(northSouthSkyline[j], eastWestSkyline[i]);
        }
    }

    printf("%lld\n", increasedHeight);
    return 0;
}