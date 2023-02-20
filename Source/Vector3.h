#pragma once
#include <valarray>

/**
 * A vector with three dimensions of type double.
 */
struct Vector3
{
public:
    /** X Component. */
    double x;

    /** Y Component. */
    double y;

    /** Z Component. */
    double z;

    /**
     * Constructs a blank vector {0,0,0}.
     */
    Vector3() : x(0), y(0), z(0) {}
    
    Vector3(const double inX, const double inY, const double inZ)
    {
        x = inX; y = inY; z = inZ;
    }

    Vector3 operator-(const Vector3& a) const
    {
        return {x - a.x, y - a.y, z - a.z};
    }

    Vector3 operator+(const Vector3& a) const
    {
        return {x + a.x, y + a.y, z + a.z};
    }

    Vector3 operator*(const Vector3& a) const
    {
        return {x * a.x, y * a.y, z * a.z};
    }
    
    Vector3 operator*(const double& a) const
    {
        return {x * a, y * a, z * a};
    }

    double Dot(const Vector3& a) const
    {
        return x * a.x + y * a.y + z * a.z;
    }

    Vector3 CrossProduct(const Vector3& a) const
    {
        return {y * a.z - z * a.y,
                z * a.x - x * a.z,
                x * a.y - y * a.x};
    }

    double Size() const
    {
        return std::sqrt(x * x + y * y + z * z);
    }
    
    void Normalise()
    {
        const double size = Size();
        if (size != 0.0)
        {
            x /= size;
            y /= size;
            z /= size;
        }
    }
};
