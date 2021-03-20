#include <stdio.h>

int main(){
    char string1[50]; // объявление строк
    char string2[50];
    //1
    printf("Введите две строки для сложения строк: \n");
    scanf("%s", string1);
    scanf("%s", string2);
    int a = 0;
    for (int i = 0; i < 50; ++i){
        if (string1[i] == '\0'){
            a = i;
            break;
        }
    }
    for (int i = a; i < 100; ++i){
        if (string2[i - a] != '\0')
            string1[i] = string2[i-a];
        else{
            string1[i] = string2[i - a];
            break;
        }
    }
    printf("%s\n", string1);

    //3
    printf("Введите две строки для сравнения строк: \n");
    scanf("%s", string1);
    scanf("%s", string2);
    int flag = 1;
    for (int i = 0; i < 50; ++i){
        if ((string1[i] == '\0') && (string2[i] == '\0')){
            flag = 1;
            break;
        } else{
            if (string1[i] != string2[i]){
                flag = 0;
                break;
            }
        }
    }
    printf("%s\n", ((flag) ? "строки равны":"строки не равны"));

    //5
    printf("Введите две строки для копирования первой строки во вторую: \n");
    scanf("%s", string1);
    scanf("%s", string2);
    for (int i = 0; i < 50; ++i){
        string2[i] = string1[i];
        if (string1[i] == '\0')
            break;
    }
    printf("%s\n", string2);

    //7
    printf("Введите строку, чтобы узнать длину строки: \n");
    scanf("%s", string1);
    for (int i = 0; i < 50; ++i){
        if (string1[i] == '\0'){
            printf("Длина строки равна = %d\n", i);
            break;
        }
    }

    //12
    printf("Введите две строки для того, чтобы определить длину отрезка одной строки, не содержащего символы второй\n");
    scanf("%s", string1);
    scanf("%s", string2);
    for (int i = 0; i < 50; ++i){
        for (int j = 0; j < 50; ++j){
            if (string1[j] == string2[i]){
                printf("Длина отрезка одной строки, не содержащего символы второй: %d\n", i);
                return 0;
            }
        }
    }
    return 0;
}