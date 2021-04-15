#include <stdio.h>

int main(){
    //2
    double minute, price, up_price, total;
    printf("Введите количество минут: ");
    scanf("%lf", &minute);
    printf("\nВведите тариф за 499 минут: ");
    scanf("%lf", &price);
    printf("\nВведите повышенный тариф за минуту: ");
    scanf("%lf", &up_price);
    if (up_price <= price/499)
        printf("Минута по повышенному тарифу дешевле минуты в пакете на 499\n");
    else {
        if (minute <= 499)
            total = price;
        else
            total = price + up_price * (minute - 499);
        printf("С вас %.2lf\n", total);
    }


    //3
    char *str[] = {"Нуль", "Один", "Два", "Три", "Четыре", "Пять", "Шесть", "Семь", "Восемь", "Девять"};
    int n;
    printf("Введите 1 цифру: ");
    scanf("%d", &n);
    printf("%d == %s\n", n, str[n]);
    return 0;
}
