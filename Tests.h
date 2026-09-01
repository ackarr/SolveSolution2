#ifndef TEST_H
#define TEST_H


#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "SolveSolution.h"
#include "general.h"


#define QUANT_RANDOM_TESTS 1000

#define MAX_RANDOM_NUM 10000

enum ModesNum
{
    TEST,
    TEST_HAND,
    TEST_RAND
};


int    RunSelectTest    (ModesParam* modes_list);
bool   RunAllHand       ();
bool   RunAllRandom     ();
int    RunTest          (const EquationParam test);
int    RunRandTest      (const EquationParam parametrs);
bool   IsZeroEquation   (const EquationParam random_param);
double GenRandDouble    ();

#endif //TEST_H
