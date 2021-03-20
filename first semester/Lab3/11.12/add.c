#include "square.h"
#include <math.h>


double square_Perimeter(const struct square sq) {
    double ab = sqrt(pow(sq.aX - sq.bX, 2) + pow(sq.aY - sq.bY, 2));
    double bc = sqrt(pow(sq.bX - sq.cX, 2) + pow(sq.bY - sq.cY, 2));
    double cd = sqrt(pow(sq.cX - sq.dX, 2) + pow(sq.cY - sq.dY, 2));
    double da = sqrt(pow(sq.dX - sq.aX, 2) + pow(sq.dY - sq.aY, 2));
    return ab + bc + cd + da;
}

double square_Area(const struct square sq) {
    double ab = sqrt(pow(sq.aX - sq.bX, 2) + pow(sq.aY - sq.bY, 2));
    double bc = sqrt(pow(sq.bX - sq.cX, 2) + pow(sq.bY - sq.cY, 2));
    return ab * bc;
}

