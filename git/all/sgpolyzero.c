#include <stdio.h>
#include <math.h>

double sgpolypos(double a, double b, double c);
double sgpolyneg(double a, double b, double c);

int main() {
    double a, b, c;
    a = 1;
    b = 0;
    c = 0;
    printf("%lg %lg", sgpolypos(a, b, c), sgpolyneg(a, b, c));
}

double sgpolypos(double a, double b, double c) {
    double disc = b*b - 4*a*c;
    disc = sqrt(disc);

    return (-b + disc) / (2*a);
}

double sgpolyneg(double a, double b, double c) {
    double disc = b*b - 4*a*c;
    disc = sqrt(disc);

    return (-b - disc) / (2*a);
}