#ifndef _RTL_Math_h_
#define _RTL_Math_h_

/*******************************************************************************
 Fast trig functions
*******************************************************************************/

//******************************************************************************
/// Finds ths sine of an angle specified in radians. 
/// Only valid over the domain of -2*PI to +2*PI.
//******************************************************************************
float sine(const float angle);

//******************************************************************************
/// Finds ths sine of an angle specified in degrees. 
/// Only valid over the domain of -360 to +360 degrees.
//******************************************************************************
float sine(const int deg);

//******************************************************************************
/// Finds ths cosine of an angle specified in radians. 
/// Only valid over the domain of -2*PI to +2*PI.
//******************************************************************************
float cosine(const float angle);

//******************************************************************************
/// Finds ths cosine of an angle in specified degrees. 
/// Only valid over the domain of -360 to +360 degrees.
//******************************************************************************
float cosine(const int deg);

#endif
