#include <stdio.h>

int main(){
    // #1
    int a[7] = {23, 5678, 2, 564, 365, 77, 443};
    for (int i = 0; i < 7; ++i){
        printf("a[%d] = %d \n", i, a[i]);
    }
    // #2
    int matrix1[2][2] = {{1, 1}, {1, 4}};
    int matrix2[2][2] = {{1, 2}, {4, 1}};
    printf("Даны две матрицы:\n");
    for (int i = 0; i < 2; ++i){
        for (int j = 0; j < 2; ++j)
            printf("%d ", matrix1[i][j]);
        printf("\n");
    }
    printf("\n");
    for (int i = 0; i < 2; ++i){
        for (int j = 0; j < 2; ++j)
            printf("%d ", matrix2[i][j]);
        printf("\n");
    }
    int result[2][2];
    for (int i = 0; i < 2; ++i){
    for (int j = 0; j < 2; ++j){
        result[i][j] = 0;
        for (int k = 0; k < 2; ++k)
            result[i][j] += matrix1[i][k] * matrix2[k][j];
    }
}
    printf("\n");
    printf("Результат: \n");
    for (int i = 0; i < 2; ++i){
        for (int j = 0; j < 2; ++j)
            printf("%2d ", result[i][j]);
        printf("\n");
    }
    return 0;
}
