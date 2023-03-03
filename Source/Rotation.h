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

    /**
     * Constructs a rotation set to zero.
     */
    Rotation() : Yaw(0), Pitch(0), Roll(0) {}

    /**
     * Constructs a new rotation.
     * @param inYaw The yaw in degrees.
     * @param inPitch The pitch in degrees.
     * @param inRoll The roll in degrees.
     */
    Rotation(const float inYaw, const float inPitch, const float inRoll)
    {
        Yaw = inYaw;
        Pitch = inPitch;
        Roll = inRoll;
    }
    
    Vector3 RotateVector(Vector3 a) const
    {
        const double yawRad = DegreesToRadians((double)Yaw);
        const double pitchRad = DegreesToRadians((double)Pitch);

        a.Normalise();

        // https://stackoverflow.com/a/14609567
        // Rotate by Pitch (Around X-axis)
        Vector3 pitchResult;
        pitchResult.x = a.x;
        pitchResult.y = a.y * cos(pitchRad) - a.z * sin(pitchRad);
        pitchResult.z = a.y * sin(pitchRad) + a.z * cos(pitchRad);
        
        // Rotate by Yaw (Around Y-axis)
        Vector3 result;
        result.x = pitchResult.x * cos(yawRad) + pitchResult.z * sin(yawRad);
        result.y = pitchResult.y;
        result.z = -pitchResult.x * sin(yawRad) + pitchResult.z * cos(yawRad);
        
        return result;
    }

    Vector3 ToUnitVector() const
    {
        // Based on https://math.stackexchange.com/q/1637464
        double pitchRad;
        if (Pitch == 0)
        {
            pitchRad = DegreesToRadians((double)Pitch + 0.001);
        } else
        {
	        pitchRad = DegreesToRadians((double)Pitch);
        }


        const double yawRad = DegreesToRadians((double)Yaw);

        const double pitchSin = sin(pitchRad);
        const double pitchCos = cos(pitchRad);

        const double yawSin = sin(yawRad);
        const double yawCos = cos(yawRad);

        Vector3 direction;
        direction.x = pitchCos * yawSin;
        direction.y = pitchSin;
        direction.z = yawCos * pitchCos;
        direction.Normalise();
        
        return direction;
    }
};
