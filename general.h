#ifndef GENERAL_H
#define GENERAL_H

#define QUANT_RIGHT_DOUBLE 3
#define QUANT_MODES 3
#define MAX_MODE_NAME 40


enum NumberOfRoots
{
    INITIAL_ROOTS = -2,
    INFINITY_ROOTS,
    ZERO_ROOTS,
    ONE_ROOTS,
    TWO_ROOTS
};

struct EquationParam
{
    double a, b, c;
    NumberOfRoots number_of_roots;
    double x1, x2;
};

struct ModesParam
{
    bool switcher;
    char mode_name[MAX_MODE_NAME];
};


const double EPSILON = 1e-6;

#endif //GENERAL_H
