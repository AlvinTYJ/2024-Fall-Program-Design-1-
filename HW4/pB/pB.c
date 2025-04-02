#include <stdio.h>

int main() {
    int N;
    scanf("%d", &N);

    float F;
    unsigned int U = (unsigned int)N;
    F = *((float*)&U);
    printf("%.23e\n", F); 

    return 0;
}