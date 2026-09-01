#include "SolveSolution.h"

int ChooseMode (const int argc, char* argv[], ModesParam* const modes_list)
{
    for(int j = 0; j < argc; j++)
    {
        for(int i = 0; i < QUANT_MODES; i++)
        {
            if(!strcmp(argv[j], modes_list[i].mode_name))
            {
                modes_list[i].switcher = true;
            }
        }
    }

    return 0;
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
    BadCode(!isnan(parametrs->a));
    BadCode(!isnan(parametrs->b));
    BadCode(!isnan(parametrs->c));

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

    BadCode(parametrs->number_of_roots != INITIAL_ROOTS);

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



void OutputRoots(const EquationParam parametrs)
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

        case INITIAL_ROOTS:
        default:
        {
            printf("wtf\n");
            break;
        }

    }

}



