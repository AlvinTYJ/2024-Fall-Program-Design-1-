#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *file;
    file = fopen(argv[1], "r");
    int num1, den1, num2, den2, a ,b;
    fscanf(file, "%d %d %d %d", &num1, &den1, &num2, &den2);
    fclose(file);

    a = (num1*den2) + (num2*den1);
    b = den1*den2;
    
    file = fopen("answer.txt", "w");
    fprintf(file,"%d/%d\n", a, b);
    fclose(file);
    return 0;
}