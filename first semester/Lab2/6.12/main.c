#include <stdio.h>
#include <stdlib.h>

int main(){
    printf("Первое задание:\n");
    double a[4];
    double * pa;
    a[0] = 56.4;
    a[1] = 36.5;
    a[2] = 7.7;
    a[3] = 44.3;

    pa = a;
    for (int i = 0; i < 4; ++i){
        printf("a[%d] = %.1lf\n", i, pa[i]);
    }
    printf("Второе задание:\n");
    double *arr;
    arr = (double *) calloc(4, sizeof(double));
    arr[0] = 56.4;
    arr[1] = 36.5;
    arr[2] = 7.7;
    arr[3] = 44.3;
    for (int i = 0; i < 4; i++){
        printf("a[%d] = %.1lf \n", i, arr[i]);
    }
    free(arr);
    return 0;
}

