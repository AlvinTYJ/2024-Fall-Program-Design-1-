#include <stdio.h>
#include "pC.h"
void f(int n, int *ans) {
    if (n <= 1) {
        *ans = n;
        return;
    }

    int temp1 = 0, temp2 = 0;
    f(n-1, &temp1);
    f(n-2, &temp2);
    *ans = temp1 + temp2;
}