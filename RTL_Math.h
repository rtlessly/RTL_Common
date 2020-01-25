#ifndef _RTL_Math_h_
#define _RTL_Math_h_

#include "PolarVector2D.h"
#include "StateVector2D.h"
#include "Vector3.h"
#include "Point2D.h"


//******************************************************************************
/// Macro to test the sign of a number: -1=negative, 1=positive, 0=zero
/// - Assumes that x is a numeric type that defines operator> and operator<.
//******************************************************************************
#define SIGN(x) ((x > 0) - (x < 0))

//******************************************************************************
/// Macro to compute unsigned difference between two unsigned numbers. Takes 
/// into consideration unsigned wrap-around. 
//******************************************************************************
#define UDIFF(x, y) abs(int32_t(uint32_t(x) - uint32_t(y)))
inline uint32_t udiff(uint32_t a, uint32_t b) { if (a > b) return(a - b); return abs(int32_t(a - b)); }
inline uint16_t udiff(uint16_t a, uint16_t b) { if (a > b) return(a - b); return abs(int16_t(a - b)); }
inline uint8_t  udiff(uint8_t  a, uint8_t  b) { if (a > b) return(a - b); return abs(int8_t(a - b)); }


/*******************************************************************************
 Fast trig functions
*******************************************************************************/

//******************************************************************************
/// Finds the sine of an angle specified in radians. 
/// Only valid over the domain of -2π to +2π.
//******************************************************************************
float sine(const float angle);

//******************************************************************************
/// Finds the sine of an angle specified in degrees. 
/// Only valid over the domain of -360 to +360 degrees.
//******************************************************************************
float sine(const int deg);

//******************************************************************************
/// Finds the cosine of an angle specified in radians. 
/// Only valid over the domain of -2π to +2π.
//******************************************************************************
float cosine(const float angle);

//******************************************************************************
/// Finds the cosine of an angle in specified degrees. 
/// Only valid over the domain of -360 to +360 degrees.
//******************************************************************************
float cosine(const int deg);

//******************************************************************************
/// Finds the arctanget of two values that comprise the legs of a right triangle,
/// where 'a' is the numerator (the 'rise') and 'b' is the denominator (the 'run'). 
/// Division by zero is accounted for and returns the appropriately signed angle 
/// (π/2 or -π/2).
//******************************************************************************
//float arctan(const float a, const float b) { return (abs(a) < 0.0001) ? 0 : ((abs(b) < 0.0001) ? HALF_PI*SIGN(a) : atan(a / b)); };

/*******************************************************************************
A fast method for computing a good approximation of 1/√x, the inverse square root.
*******************************************************************************/
float invsqrt(float x);

#endif
