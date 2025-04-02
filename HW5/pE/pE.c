#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, q, k;
    scanf("%d %d %d", &n, &q, &k);
    
    int i, j;
    int p[n+1];
    for (i=1; i<=n; i++) {
        scanf("%d", &p[i]);
    }

    int **range = malloc((q+1)*sizeof(int *));
    for (i=1; i<=q; i++) {
        range[i] = malloc(2*sizeof(int));
        scanf("%d %d", &range[i][0], &range[i][1]);
    }

    int violatedVehicles;
    for (i=1; i<=q; i++) {
        violatedVehicles = 0;
        for (j=range[i][0]; j<=range[i][1]; j++) {
            if (p[j]<k) {
                violatedVehicles++;
            }
        }
        printf("%d\n", violatedVehicles);
    }

    return 0;
}