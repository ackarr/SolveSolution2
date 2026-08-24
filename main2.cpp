#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <TXLib.h>

#define QUANT_RIGHT_DOUBLE 3
#define QUANT_PARAMETRS 3

enum NumberOfRoots
{
    ZERO_ROOTS,
    ONE_ROOTS,
    TWO_ROOTS,
    INFINITY_ROOTS
};

struct EquationParam
{
        double a, b, c;
        int number_of_roots;
        double x1, x2;
};


const double EPSILON = 0.0000001;

int  SolveEquation2   (EquationParam* parametrs);

bool IsEqualDouble    (double num1, double num2);

bool IsCorEnter       (EquationParam* parametrs);

void OutputRoots      (EquationParam parametrs);

void DeleteBuf        (void);

void EnterStupedUser  (double* entered_coef, int *quant_enter_double);

bool IsItSpace        (int check_num);

void RunTest          (EquationParam test);

void RunAllTests      ();


int main()
{
    /*double a = NAN, b = NAN, c = NAN;
    double x1 = NAN, x2 = NAN;

    int number_of_roots = 0;
    */

    EquationParam parametrs = {.a = NAN, .b = NAN, .c = NAN, .number_of_roots = 0, .x1 = NAN, .x2 = NAN};

    printf("Введите значения коэффициентов \n");

    if (IsCorEnter(&parametrs))
    {
        SolveEquation2(&parametrs);
        OutputRoots(parametrs);
    }

    //RunAllTests();

    return 0;

}


int SolveEquation2(EquationParam* parametrs)
{
    double discriminant = 0.0;

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
        parametrs->x1 = -parametrs->c / parametrs->b;
        parametrs->number_of_roots = ONE_ROOTS;
    }


    discriminant = parametrs->b * parametrs->b - 4 * parametrs->a * parametrs->c;


    if(discriminant < 0.0)
    {
        parametrs->number_of_roots = ZERO_ROOTS;
    }

    else if(IsEqualDouble(discriminant, 0.0) && ! IsEqualDouble(parametrs->a, 0.0))
    {
        parametrs->x1 = -parametrs->b / (2 * parametrs->a);
        parametrs->number_of_roots = ONE_ROOTS;
    }

    else if(! IsEqualDouble(parametrs->a, 0.0))
    {
        double corenb = sqrt(discriminant);

        parametrs->x1 = (- parametrs->b + corenb) / (2 * parametrs->a);
        parametrs->x2 = (- parametrs->b - corenb) / (2 * parametrs->a);

        parametrs->number_of_roots = TWO_ROOTS;
    }

    return 0;
}

bool IsEqualDouble(double num1, double num2)
{
    return (fabs(num1 - num2) < EPSILON);
}


bool IsCorEnter(EquationParam* parametrs)
{
    int quant_enter_of_double = 0;
    double* used_coef[] = {&(parametrs->a), &(parametrs->b), &(parametrs->c)};

    while (quant_enter_of_double != QUANT_RIGHT_DOUBLE)
    {
        for(int i = 0; i < QUANT_PARAMETRS; ++i)
        {
            char used_letter = (char)('a' + i);

            printf("Введите коэффициент %c \n", used_letter);

            EnterStupedUser(used_coef[i], &quant_enter_of_double);
        }

    }

    return true;
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



void DeleteBuf(void)
{
        int empty_letter = 0;
        while(empty_letter != '\n')
        {
                //printf("H7\n");
                empty_letter = getchar();

               // printf("H8\n");
        }

}

//stdio.h

//getchar
//scanf

//cppreference


void EnterStupedUser(double* entered_coef, int *quant_enter_of_double)
{
    bool all_num = false;

    while (!all_num)
    {
       // printf("H1\n");

            if(scanf("%lg", entered_coef) == 1)
            {
                int check_num = 0;

               // printf("H2\n");

                while((check_num = getchar()) != '\n')
                {
                  //  printf("H3\n");

                    if (IsItSpace(check_num))
                    {
                        printf("q1");
                        continue;
                    }

                    else
                    {
                        all_num = false;
                        DeleteBuf();
                        break;
                    }

                    if (check_num == '\n')
                    {
                        break;
                    }
                }

               // printf("H4\n");

                all_num = true;
            }

            else
            {
                all_num = false;
            }

            //printf("H5\n");

            if (! all_num)
            {
                DeleteBuf();
                printf("Enter good number \n");
            }

           // printf("H6\n");
    }

    ++(*quant_enter_of_double);

}


bool IsItSpace(int check_num)
{
    return (check_num == ' ' || check_num == '\t');
}


void RunTest(EquationParam test)
{

        EquationParam parametrs_testing = {.a = test.a, .b = test.b, .c = test.c, .number_of_roots = 0, .x1 = NAN, .x2 = NAN};

        SolveEquation2(&parametrs_testing);

        bool condition1 = false, condition2 = false, condition3 = false;

        condition1 = IsEqualDouble(parametrs_testing.x1, test.x1) || (IsEqualDouble(parametrs_testing.x2, test.x1) && IsEqualDouble(parametrs_testing.x1, test.x2));
        condition2 = IsEqualDouble(parametrs_testing.x2, test.x2) || (IsEqualDouble(parametrs_testing.x2, test.x1) && IsEqualDouble(parametrs_testing.x1, test.x2));

        condition3 = parametrs_testing.number_of_roots == test.number_of_roots;

        if (isnan(parametrs_testing.x1))
        {
            condition1 = isnan(test.x1);
        }

        if (isnan(parametrs_testing.x2))
        {
            condition2 = isnan(test.x2);
        }

        if(condition1 && condition2 && condition3)
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


void RunAllTests(void)
{
    EquationParam test1 = {.a = 0.0, .b = 0.0, .c = 0.0, .number_of_roots = INFINITY_ROOTS, .x1 = NAN, .x2 = NAN};
    EquationParam test2 = {.a = 1,   .b = 2,   .c = 1,   .number_of_roots = ONE_ROOTS,      .x1 = -1,  .x2 = NAN};
    EquationParam test3 = {.a = 0.0, .b = 2,   .c = -2,  .number_of_roots = ONE_ROOTS,      .x1 = 1,   .x2 = NAN};
    EquationParam test4 = {.a = 0.0, .b = 0.0, .c = 1,   .number_of_roots = ZERO_ROOTS,     .x1 = NAN, .x2 = NAN};
    EquationParam test5 = {.a = 3,   .b = 2,   .c = 1,   .number_of_roots = ZERO_ROOTS,     .x1 = NAN, .x2 = NAN};
    EquationParam test6 = {.a = 1,   .b = -5,  .c = 6,   .number_of_roots = TWO_ROOTS,      .x1 = 2,   .x2 = 3};

    RunTest(test1);
    RunTest(test2);
    RunTest(test3);
    RunTest(test4);
    RunTest(test5);
    RunTest(test6);
}







