/*******************************************************************************
 This module implements fast trig functions for sine and cosine. The functions
 execute much faster than the standard C/C++ trig functions but at the expense 
 of small loss of precision. 
*******************************************************************************/

#include <arduino.h>;
#include <inttypes.h>;
#include "RTL_Stdlib.h"

/*******************************************************************************
This method uses a quadratic expression (i.e, a parabola) to approximate a sine 
curve in the domain -π to π. The basic quadratic expression is:

sin(x) = Q(4x/π - 4x²/π²) + P(4x/π - 4x²/π²)²

Where P and Q are weighted coefficients such that P + Q = 1. This expression is
only valid over the domain 0 to π.

Basically, this is the weighted sum of parabola and a parabola squared (which is 
effectively a 4th degree polynomial). The parabola part (the first term) gives 
the overall shape roughly similar to a sine curve from 0 to π, while the parabola 
squared part(the second term) 'pulls the curve down' to more closely match a
true sine curve. 

Note that expression 4x/π - 4x²/π² is common in both terms of sin(x), so we can
factor that out and compute it seperately as the value y:

y = 4x/π - 4x²/π²

and sin(x) becomes:

sin(x) = Q(y) + P(y)²

Solving for P and Q gives P = 0.225 and Q = 0.775 (the derivation of these values 
is beyond the scope of this simple explanation, but has to do with minimizing the 
error between this function and a true sine function).

Since P + Q = 1 then Q = 1 - P, and can restate the equation solely in terms of P as:

sin(x) = (1 - P)(y) + P(y)²
sin(x) = y - Py + Py²
sin(x) = P(y² - y) + y

This expression for sin(x) is only valid over the domain of 0 to π. We can extend
the domain over -π to π by replacing x² and y² with x·|x| and y·|y|. This gives 
us the magnitude of the square while preserving the sign of x and y, thus 'flipping'
the parabola for negative angles. So the final formulation is:

y = 4x/π - 4x·|x|/π²

and

sin(x) = P(y·|y| - y) + y

This function only works correctly over the domain -π to +π. However, the sine 
function is usually specified to operate over the domain 0 to 2π. We can extend 
the domain of the function to cover ±2π by subtracting 2π from angles over π or 
adding 2π to angles less than -π. In other words, 

if |x| > π then x = x - 2π·sign(x)

Where the function sign(x) yields -1 when x<0, +1 when x>0, and 0 when x=0.

Input angles that exceed the -2π to +2π must be converted to this range by performing 
the modulus of the angle with 2π, as follows:

x = (x % 2π), where % is the modulus operator.

This allows the function to work over the entire real number domain.
*******************************************************************************/
float sine(const float angle)
{
    const float B =  4/PI;
    const float C = -4/(PI*PI);
    const float P = 0.225;

    float x = (abs(angle) > TWO_PI) ? fmod(angle,TWO_PI) : angle;
    
    if (abs(x) > PI) x -= SIGN(x)*TWO_PI;

    float y = B * x + C * x * abs(x);

    y = P * (y * abs(y) - y) + y;

    return y;
}


float sine(const int deg)
{
    return sine(float(deg * DEG_TO_RAD));
}


float cosine(const float angle)
{
    return sine(float(angle + HALF_PI));
}


float cosine(const int deg)
{
    return sine(float((deg * DEG_TO_RAD) + HALF_PI));
}
