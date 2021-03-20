#include <stdio.h>

int main() {
    //  #1
    int first_number;
    printf("Введите первое число в 16 сс: ");
    scanf("%x", &first_number);

    // #2
    printf("Первое число в 8 сс %o\n", first_number);

    // #3
    printf("Первое число: %x Первое число в 16сс сдиванутое на 4 бита: %x\n", first_number, first_number << 4);

    // #4
    printf("Первое число в 16сс: %x Первое число в 16сс после битового отрицания: %x\n", first_number, ~first_number );

    // #5
    int second_number;
    printf("Введите второе число в 16сс: ");
    scanf("%x", &second_number);
    printf("(первое число & второе число) в 16сс = %x\n", first_number & second_number);
    return 0;
}
