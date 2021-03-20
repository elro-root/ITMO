#include <stdio.h>
#include <math.h>

//1
enum corp{
    CJSC, //ООО
    LLC, // ЗАО
    Sole_Proprietor, //ИП
    JSC //ОАО
}a; //перечисляемый тип данных
//2
struct line{
    double p1[2];
    double p2[2];
};
//3
union{
    unsigned int statement;
    struct{
        unsigned short DSL: 1;
        unsigned short PPP: 1;
        unsigned short Link: 1;
    }bits; //биты
}ADSL; //юнион (объединение)

int main(){
    //1
    a = LLC;
    printf("Порядковый номер LLC: %d\n\n", a); // вывод на экран порядкового номера

    //2
    struct line line; //объявление структуры
    double len; // объявление длинны
    line.p1[0] = 0;
    line.p1[1] = 0;
    line.p2[0] = 0;
    line.p2[1] = 2;
    len = sqrt(pow(line.p2[0] - line.p1[0], 2) + pow(line.p2[1] - line.p1[1], 2)); // высчитывание длинны
    printf("Длина отрезка: %.2lf\n\n", len);

    //3
    printf("Введите число в 16СС: "); // вывод текста на экран
    scanf("%x", &ADSL.statement); //запрос числа и запись в юнион

    ADSL.bits.DSL ? printf("DSL вкл\n") : printf("DSL выкл\n");
    ADSL.bits.PPP ? printf("PPP вкл\n") : printf("PPP выкл\n");
    ADSL.bits.Link ? printf("Link вкл\n") : printf("Link выкл\n"); //проверка состояния битов и вывод на экран результата проверки

    return 0;
}
