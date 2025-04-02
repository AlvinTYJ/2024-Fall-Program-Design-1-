#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, q, k;
    scanf("%d %d %d", &n, &q, &k);
    
    int i, l, r;
    int p[n+1], isViolate[n+1];
    for (i=1; i<=n; i++) {
        scanf("%d", &p[i]);
        isViolate[i] = (p[i]<k) ? 1:0;
    }

    isViolate[0] = 0;
    for (i=1; i<=n; i++) {
        isViolate[i] = isViolate[i] + isViolate[i-1];
    }

    int violatedInRange;
    for (i=0; i<q; i++) {
        scanf("%d %d", &l, &r);
        violatedInRange = isViolate[r]-isViolate[l-1];
        printf("%d\n", violatedInRange);
    }

    return 0;
}