#pragma once

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

    double dot(const Vector3& a) const
    {
        return x * a.x + y * a.y + z * a.z;
    }
};
