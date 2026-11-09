#include "divide.h"

#include <math.h>

double divide(double dividend, double divisor)
{
    if (divisor == 0.0) {
        return NAN;
    }

    return dividend / divisor;
}
