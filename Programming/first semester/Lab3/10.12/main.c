#include <stdio.h>

void func1(unsigned int a, unsigned int b){
    unsigned int a_copy, b_copy;
    a_copy = a;
    b_copy = b;
    while (a != 0 && b != 0){
        if (a > b)
            a = a % b;
        else
            b = b % a;
    }
    printf("НОД этих чисел равен %d\n", a+b);
    printf("НОК этих чисел равен %d\n", (a_copy * b_copy / (a + b)));
}

void func3(unsigned int n) {
    int len = 0;
    unsigned int copy_number = n;
    while (copy_number){
        copy_number/= 10;
        len++;
    }

    unsigned int arr[len];

    for (int j = len - 1; j > -1; --j){
        arr[j] = n % 10;
        n = n / 10;
    }

    for (int j = 0; j < len-1; ++j){
        printf("[%d], ", arr[j]);
    }
    printf("[%d].", arr[len-1]);
}

int main(){
    unsigned int a, b, number;
    printf("Введите два числа для нахождения их НОДа и НОКа:\n");
    scanf("%d", &a);
    scanf("%d", &b);
    func1(a, b);
    printf("Введите число: ");
    scanf("%d", &number);
    func3(number);

    return 0;
}