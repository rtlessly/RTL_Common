#ifndef _PolarVector2D_h_
#define _PolarVector2D_h_

#include <math.h>
#include "RTL_Math.h"


//******************************************************************************
/// A struct that contains 2D polar representation of a vector (aka a position 
/// vector). 
///
/// Positive angles are counter-clockwise (rotating leftward from the +y axis)
/// and negative angles are clockwise (rotating rightward from the +y axis).
//******************************************************************************
struct PolarVector2D
{
    float Radius;
    float Angle;

    /***************************************************************************
    Constructors
    ***************************************************************************/
    public: PolarVector2D(float radius, float angle=0) : Radius(radius), Angle(angle) { };
    
    /***************************************************************************
    Public implementation
    ***************************************************************************/
    
    public: float X() const { return Radius * cos(radians(Angle)); };
    
    public: float Y() const { return Radius * sin(radians(Angle)); };
};

#endif

