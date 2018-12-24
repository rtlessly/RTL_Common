#include <stdlib.h>
#include <inttypes.h>


template<typename T> struct Vector3
{
    T x;
    T y;
    T z;

    //*************************************************************************
    // Constructors
    //*************************************************************************
    Vector3() : x(0), y(0), z(0) {}; 

    Vector3(const T px, const T py, const T pz) : x(px), y(py), z(pz) {}; 

    Vector3(const Vector3<T>& rhs) : x(rhs.x), y(rhs.y), z(rhs.z) {}; 

    //*************************************************************************
    // Operations
    //*************************************************************************
    // Assign a scalar value to all elements of the vector
    Vector3<T> Set(T rhs) { x = y = z = rhs; return *this; };

    // Zero all elements of the vector
    Vector3<T> Zero() { x = y = z = 0; return *this; };

    // Determines if all elements of the vector are zero
    bool IsZero() { return (x == 0 && y == 0 && z == 0); };

    // Compute the magnitude (length) of the vector
    float Magnitude() { return sqrt(x*x + y*y + z*z); };

    // Returns the corresponding unit vector
    Vector3<T> Unit() { float mag = Magnitude(); return Vector3<T>( x/mag, y/mag, x/mag); };

    // Cross product c = a x b
    // cx = ay*bz − az*by
    // cy = az*bx − ax*bz
    // cz = ax*by − ay*bx
    Vector3<T> Cross(const Vector3<T>& rhs) { return Vector3<T>( y*rhs.z - z*rhs.y, z*rhs.x - x*rhs.z, x*rhs.y - y*rhs.x ); };

    // Compute the dot product of the vector
    T Dot(const Vector3<T>& rhs) { return x*rhs.x + y*rhs.y + z*rhs.x; };

    // Apply a function to each element of the vector and return a new vector containing the result
    Vector3<T> Apply(T *f(T value)) { return Vector3<T>(f(x), f(y), f(z)); };
    Vector3<float> Apply(double *f(double value)) { return Vector3<float>(f(x), f(y), f(z)); };

    //*************************************************************************
    // Operators
    //*************************************************************************

    // Assign a scalar value to all elements of the vector
    template<typename S>
    Vector3<T> operator=(const S& rhs) { x = y = z = rhs; return *this; };

    // Determine if  to all elements of the vector are equal to a scalar value
    template<typename S>
    bool operator==(const S& rhs) { return (x == rhs &&  y == rhs && z == rhs); };

    // Determine if  to any elements of the vector are not equal to a scalar value
    template<typename S>
    bool operator!=(const S& rhs) { return !(*this == rhs); };

    // Determine if the vector is equal to another vector
    template<typename S>
    bool operator==(const Vector3<S>& rhs) { return (x == rhs.x && y == rhs.y && z == rhs.z); };

    // Determine if the vector is not equal to another vector
    template<typename S>
    bool operator!=(const Vector3<S>& rhs) { return !(*this == rhs); };

    // Vector addition
    template<typename S> 
    Vector3<T> operator+(const Vector3<S>& rhs) { return Vector3<T>(x+rhs.x, y+rhs.y, z+rhs.z); };

    template<typename S> 
    Vector3<T>& operator+=(const Vector3<S>& rhs) { x += rhs.x; y += rhs.y; z += rhs.z; return *this; };

    // Vector subtraction
    template<typename S> 
    Vector3<T> operator-(const Vector3<S>& rhs) { return Vector3<T>(x-rhs.x, y-rhs.y, z-rhs.z); };

    template<typename S> 
    Vector3<T>& operator-=(const Vector3<S>& rhs) { x -= rhs.x; y -= rhs.y; z -= rhs.z; return *this; };

    // Vector scalar multiplication
    template<typename S> 
    Vector3<T> operator*(const S s) { return Vector3<T>(x*s, y*s, z*s); };

    template<typename S> 
    Vector3<T>& operator*=(const S s) { x *= s; y *= s; z *= s; return *this; };

    // Vector scalar division
    template<typename S> Vector3<T> operator/(const S d) { return Vector3<T>(x/d, y/d, z/d); };

    template<typename S> Vector3<T>& operator/=(const S d) { x /= d; y /= d; z /= d; return *this; };

    // Vector dot product
    template<typename S> 
    T operator*(const Vector3<S>& rhs) { return x*rhs.x + y*rhs.y + z*rhs.x; };
};


template<typename S, typename V>  
Vector3<V> operator*(const S s, const Vector3<V>& rhs) { return rhs * s; };


typedef Vector3<float> Vector3F;

typedef Vector3<int32_t> Vector3L;

typedef Vector3<int16_t> Vector3I;

typedef Vector3<uint8_t> Vector3B;
