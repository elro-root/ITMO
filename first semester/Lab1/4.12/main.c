#include <stdio.h>
#include <stdbool.h>

int main() {
    int x;
    printf("Введите число: ");
    scanf("%d", &x);
    bool result;
    result = (x <= 56) && (x >= 21);
    printf("%d %s\n\n", x, (result ? "принадлежит отрезку [21; 56]":"не принадлежит отрезку [21; 56]"));

    printf("Введите число для проверки 12 бита: ");
    scanf("%d", &x);
    printf("В числе %d %d\n", x, ((x >> 11)&&1));
    printf("В числе %d %d\n", x, (x && (1 << 11)));
    return 0;
}
