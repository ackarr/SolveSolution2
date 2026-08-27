#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>

#define QUANT_RIGHT_DOUBLE 3

#define QUANT_TESTS 6

#define MAX_RANDOM_NUM 1000000

enum NumberOfRoots
{
    BEGIN_ROOTS = -1,
    INFINITY_ROOTS = -1,
    ZERO_ROOTS,
    ONE_ROOTS,
    TWO_ROOTS
};

struct EquationParam
{
        double a, b, c;
        int number_of_roots;
        double x1, x2;
};


const double EPSILON = 1e-7;

bool IsCorEnter       (EquationParam* const parametrs);                        //Input

void EnterOneCoef     (double* const entered_coef, int* const quant_enter_double, const char used_letter);


int SolveEquation     (EquationParam* const parametrs);                       //Solving

int Linear            (const double slope, const double intercept = 0);

int Square            (EquationParam* const parametrs);

int Discriminant      (const double a, const double b, const double c);


bool IsEqualDouble    (const double num1, const double num2);                     //Service function

bool IsItSpace        (const int check_num);

bool DeleteBuf        ();


void OutputRoots      (EquationParam parametrs);                     //Output


void RunAllTests      ();                                            //Tests

void RunTest          (EquationParam test);

int RunTestRand       (EquationParam test);


int main()
{
    /*double a = NAN, b = NAN, c = NAN;
    double x1 = NAN, x2 = NAN;

    int number_of_roots = 0;
    */

/*    EquationParam parametrs = {.a = NAN, .b = NAN, .c = NAN, .number_of_roots = BEGIN_ROOTS, .x1 = NAN, .x2 = NAN};

    IsCorEnter(&parametrs);

    SolveEquation(&parametrs);

    OutputRoots(parametrs);
*/
    RunAllTests();

    return 0;

}


bool IsCorEnter(EquationParam* const parametrs)
{
    printf("Enter coefficients\n");
    int quant_enter_of_double = 0;
    double* used_coef[] = {&(parametrs->a), &(parametrs->b), &(parametrs->c)};

    for(int i = 0; i < QUANT_RIGHT_DOUBLE; i++)
    {
        char used_letter = (char)('a' + i);

        printf("Введите коэффициент %c \n", used_letter);

        EnterOneCoef(used_coef[i], &quant_enter_of_double, used_letter);
    }

    return true;
}

void EnterOneCoef(double* const entered_coef, int* const quant_enter_of_double, const char used_letter)
{
    //bool is_clean_buf = DeleteBuf();
    while(scanf("%lg", entered_coef) != 1 && !DeleteBuf())
    {
        printf("Enter good number for %c\n", used_letter);
        //is_clean_buf = DeleteBuf();
    }

    ++(*quant_enter_of_double);

}



int SolveEquation(EquationParam* const parametrs)
{
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

    Square(parametrs);

    //assert(parametrs->number_of_roots < 0);

    return 0;
}

int Linear (const double slope, const double intercept)
{
    //assert(slope == 0);
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

    else if(IsEqualDouble(discriminant, 0.0) && !IsEqualDouble(parametrs->a, 0.0))
    {
        parametrs->x1 = - parametrs->b / (2 * parametrs->a);
        parametrs->number_of_roots = ONE_ROOTS;
    }

    else if(! IsEqualDouble(parametrs->a, 0.0))
    {
        double corenb = sqrt(discriminant);
        parametrs->x1 = (- parametrs->b + corenb) / (2 * parametrs->a);
        parametrs->x2 = (- parametrs->b - corenb) / (2 * parametrs->a);

        parametrs->number_of_roots = TWO_ROOTS;
    }

}

int Discriminant (const double a, const double b, const double c)
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
        if(!IsItSpace(empty_letter))
        {
            flag = false;
        }
    }

    return flag;
}

bool IsItSpace(const int check_num)
{
    return (check_num == ' ' || check_num == '\t');
}



void OutputRoots(EquationParam parametrs)
{
    switch (parametrs.number_of_roots)
    {
        case ZERO_ROOTS:
        {
            printf("Корней нет \n");
            break;
        }

        case ONE_ROOTS:
        {
            printf("x = %lg \n", parametrs.x1);
            break;
        }

        case TWO_ROOTS:

            printf("x1 = %lg, x2 = %lg \n", parametrs.x1, parametrs.x2);
            break;
        }

        case INFINITY_ROOTS:
        {
            printf("Корней бесконечно много \n");
            break;
        }

        default:
        {
        }

    }

}




void RunAllTests()
{
    EquationParam tests_list [QUANT_TESTS] =
    {
    {.a = 0.0, .b = 0.0, .c = 0.0, .number_of_roots = INFINITY_ROOTS, .x1 = NAN, .x2 = NAN},
    {.a = 1,   .b = 2,   .c = 1,   .number_of_roots = ONE_ROOTS,      .x1 = -1,  .x2 = NAN},
    {.a = 0.0, .b = 2,   .c = -2,  .number_of_roots = ONE_ROOTS,      .x1 = 1,   .x2 = NAN},
    {.a = 0.0, .b = 0.0, .c = 1,   .number_of_roots = ZERO_ROOTS,     .x1 = NAN, .x2 = NAN},
    {.a = 3,   .b = 2,   .c = 1,   .number_of_roots = ZERO_ROOTS,     .x1 = NAN, .x2 = NAN},
    {.a = 1,   .b = -5,  .c = 6,   .number_of_roots = TWO_ROOTS,      .x1 = 2,   .x2 = 3  },
    };

    int tests_size = sizeof(tests_list) / sizeof(EquationParam);

    for(int i = 0; i < tests_size; i++)
    {
        RunTest(tests_list[i]);
    }

    int quant_cor_r = 0;

    for(int i; i < 1000; i++)
    {
        double x1_r = (double) (rand() %(2 * MAX_RANDOM_NUM) -  MAX_RANDOM_NUM) / 100;
        double x2_r = (double) (rand() %(2 * MAX_RANDOM_NUM) -  MAX_RANDOM_NUM) / 100;
        double a_r = rand() %(1000); // srand
        double b_r = - a_r * (x1_r+ x2_r);
        double c_r = a_r * x1_r * x2_r;

        int number_of_roots_r = BEGIN_ROOTS;
        if (IsEqualDouble(x1_r, x2_r))
        {
            number_of_roots_r = ONE_ROOTS;
            x2_r = NAN;
        }
        else
            number_of_roots_r = TWO_ROOTS;

        EquationParam random_param = {.a = a_r, .b = b_r, .c = c_r,
                                      .number_of_roots = number_of_roots_r, .x1 = x1_r, .x2 = x2_r};

        quant_cor_r = quant_cor_r + RunTestRand(random_param);
    }

    printf("Quantity correct random test %d\n", quant_cor_r);




    /*EquationParam test1 = {.a = 0.0, .b = 0.0, .c = 0.0, .number_of_roots = INFINITY_ROOTS, .x1 = NAN, .x2 = NAN};
    EquationParam test2 = {.a = 1,   .b = 2,   .c = 1,   .number_of_roots = ONE_ROOTS,      .x1 = -1,  .x2 = NAN};
    EquationParam test3 = {.a = 0.0, .b = 2,   .c = -2,  .number_of_roots = ONE_ROOTS,      .x1 = 1,   .x2 = NAN};
    EquationParam test4 = {.a = 0.0, .b = 0.0, .c = 1,   .number_of_roots = ZERO_ROOTS,     .x1 = NAN, .x2 = NAN};
    EquationParam test5 = {.a = 3,   .b = 2,   .c = 1,   .number_of_roots = ZERO_ROOTS,     .x1 = NAN, .x2 = NAN};
    EquationParam test6 = {.a = 1,   .b = -5,  .c = 6,   .number_of_roots = TWO_ROOTS,      .x1 = 2,   .x2 = 3  };


    RunTest(test1);
    RunTest(test2);
    RunTest(test3);
    RunTest(test4);
    RunTest(test5);
    RunTest(test6);
    */
}

void RunTest(EquationParam test)
{

        EquationParam parametrs_testing = {.a = test.a, .b = test.b, .c = test.c,
                                           .number_of_roots = 0, .x1 = NAN, .x2 = NAN};

        SolveEquation(&parametrs_testing);

        bool x1_cor = false, x2_cor = false, quant_roots_cor = false;

        x1_cor = IsEqualDouble(parametrs_testing.x1, test.x1)
                 || (IsEqualDouble(parametrs_testing.x2, test.x1) && IsEqualDouble(parametrs_testing.x1, test.x2));

        x2_cor = IsEqualDouble(parametrs_testing.x2, test.x2)
                 || (IsEqualDouble(parametrs_testing.x2, test.x1) && IsEqualDouble(parametrs_testing.x1, test.x2));

        quant_roots_cor = parametrs_testing.number_of_roots == test.number_of_roots;

        if(x1_cor && x2_cor && quant_roots_cor)
            printf("Test was end without errors \n");

        else
        {
            printf("Test FAILED: \n"
                   "a = %lg, b = %lg, c = %lg \n"
                   "Reference: x1 = %lg, x2 = %lg, quantity roots = %d \n"
                   "Result: x1 = %lg, x2 = %lg, quantity roots = %d \n",

            test.a, test.b, test.c, test.x1,
            test.x2, test.number_of_roots,
            parametrs_testing.x1, parametrs_testing.x2, parametrs_testing.number_of_roots);
        }

}



int RunTestRand(EquationParam random_param)
{

        EquationParam parametrs_testing = {.a = random_param.a, .b = random_param.b, .c = random_param.c,
                                           .number_of_roots = 0, .x1 = NAN, .x2 = NAN};

        SolveEquation(&parametrs_testing);

        bool x1_cor = false, x2_cor = false, quant_roots_cor = false;

        x1_cor = IsEqualDouble(parametrs_testing.x1, random_param.x1)
                 || (IsEqualDouble(parametrs_testing.x2, random_param.x1)
                 && IsEqualDouble(parametrs_testing.x1, random_param.x2));

        x2_cor = IsEqualDouble(parametrs_testing.x2, random_param.x2)
                 || (IsEqualDouble(parametrs_testing.x2, random_param.x1)
                 && IsEqualDouble(parametrs_testing.x1, random_param.x2));

        quant_roots_cor = parametrs_testing.number_of_roots == random_param.number_of_roots;

        if(x1_cor && x2_cor && quant_roots_cor)
            return 1;

        else
        {
            return 0;
        }
}








