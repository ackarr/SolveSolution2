#include "Tests.h"

int RunSelectTest (ModesParam* modes_list)
{
    if(modes_list[TEST].switcher)
    {
        BadCode(RunAllHand());
        BadCode(RunAllRandom());
    }

    if(modes_list[TEST_HAND].switcher)
    {
        BadCode(RunAllHand());
    }

    if(modes_list[TEST_RAND].switcher)
    {
        BadCode(RunAllRandom());
    }

    return 0;
}

bool RunAllHand()
{
    bool is_success = true;

    EquationParam tests_list [] =
    {
        {.a = 0.0, .b = 0.0, .c = 0.0, .number_of_roots = INFINITY_ROOTS, .x1 = NAN, .x2 = NAN},
        {.a = 1,   .b = 2,   .c = 1,   .number_of_roots = ONE_ROOTS,      .x1 = -1,  .x2 = NAN},
        {.a = 0.0, .b = 2,   .c = -2,  .number_of_roots = ONE_ROOTS,      .x1 = 1,   .x2 = NAN},
        {.a = 0.0, .b = 0.0, .c = 1,   .number_of_roots = ZERO_ROOTS,     .x1 = NAN, .x2 = NAN},
        {.a = 3,   .b = 2,   .c = 1,   .number_of_roots = ZERO_ROOTS,     .x1 = NAN, .x2 = NAN},
        {.a = 1,   .b = -5,  .c = 6,   .number_of_roots = TWO_ROOTS,      .x1 = 2,   .x2 = 3  }
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

    return is_success;
}

bool RunAllRandom()
{
    bool is_success = true;
    int test_quant_r = 0;

    srand((unsigned int) (time(0)));

    for(int i = 0; i < QUANT_RANDOM_TESTS; i++)
    {
        EquationParam random_param = {.a = GenRandDouble(), .b = GenRandDouble(), .c = GenRandDouble(),
                                      .number_of_roots = INITIAL_ROOTS, .x1 = NAN, .x2 = NAN};

        if(int random_test_result = RunRandTest(random_param))
        {
            test_quant_r += random_test_result;
        }

        else
            is_success = false;
    }

    printf("Quantity correct random test %d / %d\n", test_quant_r, QUANT_RANDOM_TESTS);

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
            if(isnan(random_param.x2) && IsZeroEquation(random_param))
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
            if(isnan(random_param.x1) && isnan(random_param.x2))
                return 1;
            break;
        }

        case INITIAL_ROOTS:
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

    return false;
}

double GenRandDouble()
{
    return (double) ((rand() % (2 * MAX_RANDOM_NUM) - (MAX_RANDOM_NUM))) / 100;
}
