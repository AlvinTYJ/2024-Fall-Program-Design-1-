#include <stdio.h>
#include <stdbool.h>

int main() {
    int N;
    scanf("%d", &N);

    int s[N];
    for (int i=0; i<N; i++) {
        scanf("%d", &s[i]);
    }

    int M = 0;
    bool inInterval = false;
    for (int i=0; i<N; i++) {
        if (s[i] >= 40 && s[i] <= 60) {
            if (!inInterval)
            {
                inInterval = true;
                M++;
            }
        }
        else
        {
            inInterval = false;
        }
    }

    printf("%d\n", M);
    return 0;
}