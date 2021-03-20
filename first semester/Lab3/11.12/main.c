#include <stdio.h>
#include "square.h"

int main() {
    struct square sq;

    printf("Координаты A\n");
    scanf("%lf %lf", &sq.aX, &sq.aY);

    printf("Координаты B\n");
    scanf("%lf %lf", &sq.bX, &sq.bY);

    printf("Координаты C\n");
    scanf("%lf %lf", &sq.cX, &sq.cY);

    printf("Координаты D\n");
    scanf("%lf %lf", &sq.dX, &sq.dY);

    printf("perimeter: %0.2f\n", square_Perimeter(sq));
    printf("area: %0.2f\n", square_Area(sq));

    return 0;
}
