#include <stdio.h>
#include <limits.h>
#include <string.h>

void printBinary(unsigned int num) {
    for (int i = sizeof(num) * 8 - 1; i >= 0; i--) {
        printf("%u", (num >> i) & 1);
    }
    printf("\n");
}

void printBinarySeperated(unsigned int num) {
    unsigned int sign = (num >> 31) & 1;
    unsigned int exponent = (num >> 23) & 0xFF;
    unsigned int mantissa = num & 0x7FFFFF;

    printf("Sign bit: %u ", sign);
    printf("Exponent: ");
    for (int i = 7; i >= 0; i--) {
        printf("%u", (exponent >> i) & 1);
    }
    
    printf(" Mantissa: ");
    for (int i = 22; i >= 0; i--) {
        printf("%u", (mantissa >> i) & 1);
    }
    printf("\n");
}

int main() {
    float maxFloat = 3.4028235e+38f;
    printf("Max Float: %f\n", maxFloat);
    printBinary(*(unsigned int*)&maxFloat);
    printBinarySeperated(*(unsigned int*)&maxFloat);
    printf("\n");

    float minNormFloat = 1.17549435e-38f;
    printf("Smallest Normalized Float: %.23e\n", minNormFloat);
    printBinary(*(unsigned int*)&minNormFloat);
    printBinarySeperated(*(unsigned int*)&minNormFloat);
    printf("\n");

    float minDenormFloat = 1.401298464324817e-45f;
    printf("Smallest Positive Denormalized Float: %.23e\n", minDenormFloat);
    printBinary(*(unsigned int*)&minDenormFloat);
    printBinarySeperated(*(unsigned int*)&minDenormFloat);
    printf("\n");

    float infFloat = 1.0f / 0.0f;
    printf("Positive Infinity: %f\n", infFloat);
    printBinary(*(unsigned int*)&infFloat);
    printBinarySeperated(*(unsigned int*)&infFloat);
    printf("\n");

    float nanFloat = 0.0f / 0.0f;
    printf("NaN: %f\n", nanFloat);
    printBinary(*(unsigned int*)&nanFloat);
    printBinarySeperated(*(unsigned int*)&nanFloat);

    return 0;
}
