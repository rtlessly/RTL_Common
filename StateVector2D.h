#ifndef _StateVector2D_h_
#define _StateVector2D_h_

#include <math.h>
#include "RTL_Math.h"


//******************************************************************************
/// A struct that contains 2D state vector information. This includes an x and 
/// y position as well as a heading direction. The heading angle is always specified
/// in degrees.
///
/// For purposes of orientation, the +y axis is considered the "straight-ahead" 
/// direction relative to the initial origin position, while -x is to the left 
/// and +x is to the right. The heading angle is always relative to the +y axis
/// instead of the +x axis. This is significant because it affects the calculation
/// of the heading angle difference, where the angle difference is calculated as
/// arctan(dx/dy) instead of the more usual arctan(dy/dx) (since the angle's
/// reference axis is y instead of x).
/// 
/// Also, positive angles are counter-clockwise (rotating leftward from the +y 
/// axis) and negative angles are clockwise (rotating rightward from the +y axis).
//******************************************************************************
struct StateVector2D
{
    float X;
    float Y;
    float Heading;

    /***************************************************************************
    Constructors
    ***************************************************************************/
    public: StateVector2D(float x, float y, float heading=0) : X(x), Y(y), Heading(heading) { };
    
    /***************************************************************************
    Public implementation
    ***************************************************************************/
    public: StateVector2D const Difference(const float xpos, const float ypos) const
    {
        StateVector2D diff(xpos - X, ypos - Y);
        
        diff.Heading = -degrees(abs(diff.X) < 0.0001 ? 0 : atan2(diff.X, diff.Y));
        
        return diff;
    };
    
    public: float const Magnitude() const { return sqrt(X*X + Y*Y); };

    public: float const PositionAngle() const { return -degrees(abs(X) < 0.0001 ? 0 : atan2(X, Y)); }; //degrees((abs(Y) < 0.001) ? -HALF_PI*SIGN(X) : -atan(X / Y)); };
};

#endif

