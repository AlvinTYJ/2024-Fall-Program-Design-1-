#include <stdio.h>
#include "pB.h"

int result[100][100];

void solve(int n, int m, int (*A)[100], int (*B)[100]){
    for(int i=0;i<n;i++) {
        for(int j=0;j<m;j++) {
            result[i][j] = A[i][j] + B[i][j];
        }
    }
}

int get_value(int x, int y){
    return result[x][y];
}