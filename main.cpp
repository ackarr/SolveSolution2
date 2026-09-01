#include <stdio.h>

#include "SolveSolution.h"
#include "Tests.h"
#include "BadCode.h"

int main(int argc, char* argv[])
{
    ModesParam modes_list [] =
    {
        {.switcher = false, .mode_name = "test"  },
        {.switcher = false, .mode_name = "test_h"},
        {.switcher = false, .mode_name = "test_r"}
    };

    ChooseMode(argc, argv, modes_list);

    RunSelectTest(modes_list);

    EquationParam parametrs = {.a = NAN, .b = NAN, .c = NAN, .number_of_roots = INITIAL_ROOTS, .x1 = NAN, .x2 = NAN};

    IsCorEnter   (&parametrs);

    SolveEquation(&parametrs);

    OutputRoots   (parametrs);

    return 0;

}
