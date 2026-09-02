#ifndef SOLVESOLUTION_H
#define SOLVESOLUTION_H


#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>

#include "general.h"
#include "BadCode.h"


int    ChooseMode       (const int argc, char* argv[], ModesParam* const modes_list); //Modes


bool   IsCorEnter       (EquationParam* const parametrs);                             //Input

void   EnterOneCoef     (double* const entered_coef, const char used_letter);


int    SolveEquation    (EquationParam* const parametrs);                             //Solving

double Linear           (const double slope, const double intercept);

int    Square           (EquationParam* const parametrs);

double Discriminant     (const double a, const double b, const double c);


bool   IsEqualDouble    (const double num1, const double num2);                      //Service function

bool   IsItSpace        (const int check_num);

bool   DeleteBuf        ();


void   OutputRoots      (const EquationParam parametrs);                             //Output

#endif //SOLVESOLUTION_H
