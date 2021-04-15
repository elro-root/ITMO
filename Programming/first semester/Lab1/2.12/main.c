#include <stdio.h>
#include <math.h>

int main(){
    //Getting angel in radians with console
    double alpha;
    printf("Input your angle in radians: ");
    scanf("%lf", &alpha);
    //Print result
    printf("Z1 = %.53lf\n", ((sin(4 * alpha))/(1 + cos(4 * alpha)) * (cos(2 * alpha)/(1 + cos(2 * alpha)))));
    printf("Z2 = %.53lf\n", tan(alpha));
    return 0;
}

