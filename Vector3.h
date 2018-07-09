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
    float Magnitude() { return sqrt(x*x + y*y + z*z); };

    Vector3<T> Unit() { float mag = Magnitude(); return Vector3<T>( x/mag, y/mag, x/mag); };

    // Cross product c = a x b
    // cx = ay*bz − az*by
    // cy = az*bx − ax*bz
    // cz = ax*by − ay*bx

    Vector3<T> Cross(const Vector3<T>& rhs) { return Vector3<T>( y*rhs.z - z*rhs.y, z*rhs.x - x*rhs.z, x*rhs.y - y*rhs.x ); };

    T Dot(const Vector3<T>& rhs) { return x*rhs.x + y*rhs.y + z*rhs.x; };

    //*************************************************************************
    // Operators
    //*************************************************************************
    // Vector addition
    template<typename S> Vector3<T> operator+(const Vector3<S>& rhs) { return Vector3<T>(x+rhs.x, y+rhs.y, z+rhs.z); };

    template<typename S> Vector3<T>& operator+=(const Vector3<S>& rhs) { x += rhs.x; y += rhs.y; z += rhs.z; return *this; };

    // Vector subtraction
    template<typename S> Vector3<T> operator-(const Vector3<S>& rhs) { return Vector3<T>(x-rhs.x, y-rhs.y, z-rhs.z); };

    template<typename S> Vector3<T>& operator-=(const Vector3<S>& rhs) { x -= rhs.x; y -= rhs.y; z -= rhs.z; return *this; };

    // Vector scalar multiplication
    template<typename S> Vector3<T> operator*(const S s) { return Vector3<T>(x*s, y*s, z*s); };

    template<typename S> Vector3<T>& operator*=(const S s) { x *= s; y *= s; z *= s; return *this; };

    // Vector scalar division
    template<typename S> Vector3<T> operator/(const S d) { return Vector3<T>(x/d, y/d, z/d); };

    template<typename S> Vector3<T>& operator/=(const S d) { x /= d; y /= d; z /= d; return *this; };

    // Vector dot product
    template<typename S> T operator*(const Vector3<S>& rhs) { return x*rhs.x + y*rhs.y + z*rhs.x; };
};


template<typename S, typename V>  Vector3<V> operator*(const S s, const Vector3<V>& rhs) { return rhs * s; };


typedef Vector3<float> Vector3F;

typedef Vector3<int32_t> Vector3L;

typedef Vector3<int16_t> Vector3I;

typedef Vector3<uint8_t> Vector3B;
