#include <stdio.h>
#include <string.h>

int main() {
    int i;
    int N;
    scanf("%d", &N);
    long long int a[N+1];
    for (i=1; i<=N; i++) {
        scanf("%lld", &a[i]);
    }

    long long int b[N+1];
    memcpy(b+1, a+1, N*sizeof(long long int));
    for (i=2; i<=N; i++) {
        b[i] = b[i] + b[i-1];
    }

    int Q;
    scanf("%d", &Q);
    int range[Q][2];
    for (i=0; i<Q; i++) {
        scanf("%d %d", &range[i][0], &range[i][1]);
    }
    
    long long int sum;
    for (i=0; i<Q; i++) {
        if (range[i][0] == 1) {
            sum = b[range[i][1]];
        }
        else {
            sum = b[range[i][1]] - b[range[i][0]-1];
        }
        
        printf("%lld\n", sum);
    }

    return 0;
}