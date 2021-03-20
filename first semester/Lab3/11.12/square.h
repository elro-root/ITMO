#ifndef SQUARE_H
#define SQUARE_H

struct square{
    double aX, aY, bX, bY, cX, cY, dX, dY;
};

double square_Perimeter(struct square sq);

double square_Area(struct square sq);

#endif //SQUARE_H
