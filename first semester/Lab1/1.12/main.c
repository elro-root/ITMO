#include <stdio.h>

int main(){
    // Get string with console and print it
    char str[100];
    printf("Input your string: ");
    scanf("%s", str);
    printf("%s %s \n","Your string is", str);

    // Get real number with console and print it
    double number;
    printf("Input your number: ");
    scanf("%lf", &number);
    printf("%s %lf", "Your float number is", number);

    return 0;
}