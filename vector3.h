#pragma once 

#include <cmath>
#include <float.h>
#include <string.h>
#include <iostream>
#include <cstdlib>
#include <cmath>

template <typename T>
class Vector3
{

public:
    T x, y, z;

    // trivial ctor
    constexpr Vector3<T>()
        : x(0), y(0), z(0) {}

    // setting ctor
    constexpr Vector3<T>(const T x0, const T y0, const T z0)
        : x(x0), y(y0), z(z0) {}

    // function call operator
    void operator()(const T x0, const T y0, const T z0)
    {
        x = x0;
        y = y0;
        z = z0;
    }

    // negation
    Vector3<T> operator-(void) const;

    // addition
    Vector3<T> operator+(const Vector3<T> &v) const;

    // subtraction
    Vector3<T> operator-(const Vector3<T> &v) const;

    // uniform scaling
    Vector3<T> operator*(const T num) const;

    // uniform scaling
    Vector3<T> operator/(const T num) const;

    // addition
    Vector3<T> &operator+=(const Vector3<T> &v);

    // subtraction
    Vector3<T> &operator-=(const Vector3<T> &v);

    // uniform scaling
    Vector3<T> &operator*=(const T num);

    // uniform scaling
    Vector3<T> &operator/=(const T num);

    // non-uniform scaling
    Vector3<T> &operator*=(const Vector3<T> &v)
    {
        x *= v.x;
        y *= v.y;
        z *= v.z;
        return *this;
    }

    // gain Multiply
    Vector3<T> multiplyGain(const Vector3<T> &v)
    {
        return Vector3<T>(x * v.x, y * v.y, z * v.z);
    }

    Vector3<T> bindToMaxVal(const Vector3<T> &v)
    {
        if (x > v.x)
            x = v.x;
        else if (x < -v.x)
            x = -v.x;

        if (y > v.y)
            y = v.y;
        else if (y < -v.y)
            y = -v.y;

        if (z > v.z)
            z = v.z;
        else if (z < -v.z)
            z = -v.z;

        return *this;
    }

    // dot product
    T operator*(const Vector3<T> &v) const;

    // cross product
    Vector3<T> operator%(const Vector3<T> &v) const;
};

typedef Vector3<float> Vector3f;

class PositionAndYawVector : public Vector3f
{
public:
    float yaw{};
    inline PositionAndYawVector() : Vector3f(0, 0, 0){};
    inline PositionAndYawVector(float x, float y, float z, float yaw) : Vector3f(x, y, z), yaw(yaw){};
};
