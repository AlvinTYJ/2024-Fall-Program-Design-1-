#include <stdio.h>
#include <stdint.h>

void printBits(size_t size, void *ptr) {
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;
    
    for (i = size-1; i >= 0; i--) {
        for (j = 7; j >= 0; j--) {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
    }
    printf("\n");
}

int main() {
    int N;
    scanf("%d", &N);
    
    if (N == 1) {
        int X;
        scanf("%d", &X);
        printBits(sizeof(X), &X);
        
    }
    else if (N == 2) {
        float X;
        scanf("%f", &X);
        printBits(sizeof(X), &X);
        
    }
    else {
        return 0;
    }
    return 0;
}
