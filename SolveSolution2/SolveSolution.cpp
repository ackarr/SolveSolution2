#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

#define QUANT_RIGHT_DOUBLE 3

#define MAX_RANDOM_NUM 10000

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


const double EPSILON = 1e-6;

const int QUANT_RANDOM_TESTS = 1000;

bool   IsCorEnter       (EquationParam* const parametrs);                        //Input

void   EnterOneCoef     (double* const entered_coef, const char used_letter);


int    SolveEquation    (EquationParam* const parametrs);                       //Solving

double Linear           (const double slope, const double intercept);

int    Square           (EquationParam* const parametrs);

double Discriminant     (const double a, const double b, const double c);


bool   IsEqualDouble    (const double num1, const double num2);                //Service function

bool   IsItSpace        (const int check_num);

bool   DeleteBuf        ();


void   OutputRoots      (EquationParam parametrs);                     //Output


int    StartTests       (int argc, char* argv);                         //Tests

bool   RunAllTests      ();

int    RunTest          (EquationParam test);

int    RunTestRand      (EquationParam test);

int    RunRandTest      (EquationParam parametrs);

bool   IsZeroEquation   (const EquationParam random_param);


double GenRandDouble    ();                                             //Random Generaation


int main(int argc, char* argv[])
{

    if(StartTests(argc, argv[1]))
    {

        EquationParam parametrs = {.a = NAN, .b = NAN, .c = NAN, .number_of_roots = INITIAL_ROOTS, .x1 = NAN, .x2 = NAN};

        IsCorEnter(&parametrs);

        SolveEquation(&parametrs);

        OutputRoots(parametrs);
    }


    return 0;

}


int StartTests (int argc, char* code_word)
{
    if(argc == 2 && !strcmp(code_word, "test"))
    {
        if(RunAllTests())
            return true;
        else
            return false;
    }

    return true;
}


bool IsCorEnter(EquationParam* const parametrs)
{
    printf("Enter coefficients\n");
    double* used_coef [QUANT_RIGHT_DOUBLE] = {&(parametrs->a), &(parametrs->b), &(parametrs->c)};

    for(int i = 0; i < QUANT_RIGHT_DOUBLE; i++)
    {
        char used_letter = (char)('a' + i);

        EnterOneCoef(used_coef[i], used_letter);
    }

    return true;
}

void EnterOneCoef(double* const entered_coef, const char used_letter)
{
    printf("Input coefficient %c: ", used_letter);

    int is_scan1 = scanf("%lg", entered_coef);
    bool is_clean_buf = DeleteBuf();

    while(is_scan1 != 1 || !is_clean_buf)
    {
        printf("Enter good number for %c: ", used_letter);
        is_scan1 = scanf("%lg", entered_coef);
        is_clean_buf = DeleteBuf();
    }
}



int SolveEquation(EquationParam* const parametrs)
{
    assert(!isnan(parametrs->a));
    assert(!isnan(parametrs->b));
    assert(!isnan(parametrs->c));

    if(IsEqualDouble(parametrs->a, 0.0) && IsEqualDouble(parametrs->b, 0.0) && IsEqualDouble(parametrs->c, 0.0))
    {
        parametrs->number_of_roots = INFINITY_ROOTS;
    }

    else if(IsEqualDouble(parametrs->a, 0.0) && IsEqualDouble(parametrs->b, 0.0) && ! IsEqualDouble((parametrs->c), 0.0))
    {
        parametrs->number_of_roots = ZERO_ROOTS;
    }

    else if(IsEqualDouble(parametrs->a, 0.0) && ! IsEqualDouble(parametrs->b, 0.0))
    {
        parametrs->x1 = Linear(parametrs->b, parametrs->c);
        parametrs->number_of_roots = ONE_ROOTS;
    }

    else
    {
        Square(parametrs);
    }

    assert(parametrs->number_of_roots != INITIAL_ROOTS);

    return 0;
}

double Linear (const double slope, const double intercept)
{
    return - intercept / slope;
}

int Square (EquationParam* const parametrs)
{
    double discriminant = 0.0;

    discriminant = Discriminant(parametrs->a, parametrs->b, parametrs->c);

    if(discriminant < 0.0 && !IsEqualDouble(discriminant, 0.0))
    {
        parametrs->number_of_roots = ZERO_ROOTS;
    }

    else if(IsEqualDouble(discriminant, 0.0))
    {
        parametrs->x1 = - parametrs->b / (2 * parametrs->a);
        parametrs->number_of_roots = ONE_ROOTS;
    }

    else
    {
        double corenb = sqrt(discriminant);

        parametrs->x1 = (- parametrs->b + corenb) / (2 * parametrs->a);
        parametrs->x2 = (- parametrs->b - corenb) / (2 * parametrs->a);
        parametrs->number_of_roots = TWO_ROOTS;
    }

    return 0;
}

double Discriminant (const double a, const double b, const double c)
{
    return b * b - 4 * a * c;
}




bool IsEqualDouble(const double num1, const double num2)
{
    if (isnan(num1))
    {
        return isnan(num2);
    }

    return (fabs(num1 - num2) < EPSILON);
}

bool DeleteBuf()
{
    int empty_letter = 0;
    bool flag = true;

    while ((empty_letter = getchar()) != '\n')
    {
        if(!isspace(empty_letter))
        {
            flag = false;
        }
    }

    return flag;
}



void OutputRoots(EquationParam parametrs)
{
    switch (parametrs.number_of_roots)
    {
        case ZERO_ROOTS:
        {
            printf("Zero roots\n");
            break;
        }

        case ONE_ROOTS:
        {
            printf("x = %lg \n", parametrs.x1);
            break;
        }

        case TWO_ROOTS:
        {
            printf("x1 = %lg, x2 = %lg \n", parametrs.x1, parametrs.x2);
            break;
        }

        case INFINITY_ROOTS:
        {
            printf("Infinity roots\n");
            break;
        }

        default:
        {
            break;
        }

    }

}




bool RunAllTests()
{
    bool is_success = true;

    EquationParam tests_list [] =
    {
        {.a = 0.0, .b = 0.0, .c = 0.0, .number_of_roots = INFINITY_ROOTS, .x1 = NAN, .x2 = NAN},
        {.a = 1,   .b = 2,   .c = 1,   .number_of_roots = ONE_ROOTS,      .x1 = -1,  .x2 = NAN},
        {.a = 0.0, .b = 2,   .c = -2,  .number_of_roots = ONE_ROOTS,      .x1 = 1,   .x2 = NAN},
        {.a = 0.0, .b = 0.0, .c = 1,   .number_of_roots = ZERO_ROOTS,     .x1 = NAN, .x2 = NAN},
        {.a = 3,   .b = 2,   .c = 1,   .number_of_roots = ZERO_ROOTS,     .x1 = NAN, .x2 = NAN},
        {.a = 1,   .b = -5,  .c = 6,   .number_of_roots = TWO_ROOTS,      .x1 = 2,   .x2 = 3  },
    };

    int tests_size = sizeof(tests_list) / sizeof(EquationParam);

    int test_quant = 0;

    for(int i = 0; i < tests_size; i++)
    {
        if(int test_result = RunTest(tests_list[i]))
        {
            test_quant += test_result;
        }

        else
            is_success = false;
    }

    printf("Quantity correct hand test %d / %d\n", test_quant, tests_size);


    int test_quant_r = 0;

    srand(time(0));

    for(int i = 0; i < QUANT_RANDOM_TESTS; i++)
    {
        //printf("%lg %lg %lg\n", random_param.a, random_param.b, random_param.c);
        EquationParam random_param = {.a = GenRandDouble(), .b = GenRandDouble(), .c = GenRandDouble(),
                                      .number_of_roots = INITIAL_ROOTS, .x1 = NAN, .x2 = NAN};

        if(int random_test_result = RunRandTest(random_param))
        {
            test_quant += random_test_result;
        }

        else
            is_success = false;

        test_quant_r += RunRandTest(random_param);
    }
    printf("Quantity correct random test %d /  %d\n", test_quant_r, QUANT_RANDOM_TESTS);

    return is_success;
}


int RunTest(EquationParam test)
{

        EquationParam parametrs_testing = {.a = test.a, .b = test.b, .c = test.c,
                                           .number_of_roots = INITIAL_ROOTS, .x1 = NAN, .x2 = NAN};

        SolveEquation(&parametrs_testing);

        bool x1_cor = false, x2_cor = false, quant_roots_cor = false;

        x1_cor = IsEqualDouble(parametrs_testing.x1, test.x1)
             || (IsEqualDouble(parametrs_testing.x2, test.x1) && IsEqualDouble(parametrs_testing.x1, test.x2));

        x2_cor = IsEqualDouble(parametrs_testing.x2, test.x2)
             || (IsEqualDouble(parametrs_testing.x2, test.x1) && IsEqualDouble(parametrs_testing.x1, test.x2));

        quant_roots_cor = parametrs_testing.number_of_roots == test.number_of_roots;

        if(x1_cor && x2_cor && quant_roots_cor)
        {
            return 1;
        }

        else
        {
            printf("Test FAILED: \n"
                   "a = %lg, b = %lg, c = %lg \n"
                   "Reference: x1 = %lg, x2 = %lg, quantity roots = %d \n"
                   "Result: x1 = %lg, x2 = %lg, quantity roots = %d \n",

            test.a, test.b, test.c, test.x1,
            test.x2, test.number_of_roots,
            parametrs_testing.x1, parametrs_testing.x2, parametrs_testing.number_of_roots);

            return 0;
        }

}

int RunRandTest(EquationParam random_param)
{
    SolveEquation(&random_param);

    switch(random_param.number_of_roots)
    {
        case ZERO_ROOTS:
        {
            if(isnan(random_param.x1) && isnan(random_param.x2))
                return 1;
            break;
        }

        case ONE_ROOTS:
        {
            if(isnan(random_param.x2)
            && IsZeroEquation(random_param))
                return 1;
            break;
        }

        case TWO_ROOTS:
        {
            if(IsZeroEquation(random_param))
                return 1;
            break;
        }

        case INFINITY_ROOTS:
        {
            if(isnan(random_param.x1) && isnan(random_param.x2)
                && IsEqualDouble(random_param.a, 0.0)
                && IsEqualDouble(random_param.b, 0.0)
                && IsEqualDouble(random_param.c, 0.0))
                return 1;
            break;
        }

        default:
        {
            printf("wtf");
            return 0;
        }
    }
    return 0;
}

bool IsZeroEquation(EquationParam random_param)
{
    if(!isnan(random_param.x1))
    {
        if(!isnan(random_param.x2))
        {
            return IsEqualDouble(random_param.a * random_param.x1 * random_param.x1
                               + random_param.b * random_param.x1 + random_param.c, 0.0)
                && IsEqualDouble(random_param.a * random_param.x2 * random_param.x2
                               + random_param.b * random_param.x2 + random_param.c, 0.0);
        }

        else
        {
            return IsEqualDouble(random_param.a * random_param.x1 * random_param.x1
                               + random_param.b * random_param.x1 + random_param.c, 0.0);
        }
    }
}



double GenRandDouble()
{
    return (double) ((rand() % (2 * MAX_RANDOM_NUM) - (MAX_RANDOM_NUM))) / 100;
}




