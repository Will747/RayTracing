#pragma once
#include "Constants.h"
#include "Vector3.h"

/**
 * Represents a rotation with yaw, pitch, roll.
 */
struct Rotation
{
public:
    /** The rotation around the y axis in degrees. */
    float Yaw;

    /** The rotation around the z axis in degrees. */
    float Pitch;

    /** The rotation around the x axis in degrees. */
    float Roll;

    Vector3 ToUnitVector() const
    {
        // Based on https://math.stackexchange.com/q/1637464
        const double pitchRad = DegreesToRadians((double)Pitch);
        const double yawRad = DegreesToRadians((double)Yaw);

        const double pitchSin = sin(pitchRad);
        const double pitchCos = cos(pitchRad);

        const double yawSin = sin(yawRad);
        const double yawCos = cos(pitchCos);

        Vector3 direction;
        direction.x = pitchCos * yawSin;
        direction.y = pitchSin;
        direction.z = yawCos * pitchCos;
        direction.Normalise();
        
        return direction;
    }
};
