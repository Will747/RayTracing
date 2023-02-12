#pragma once
#include "Vector3.h"

/**
 * A ray with an origin and direction.
 */
struct Ray
{
public:
    /**
     * Constructs a ray.
     * @param inOrigin The origin of the ray.
     * @param inDirection The direction of the ray.
     */
    Ray(Vector3 inOrigin, Vector3 inDirection)
        : origin(inOrigin), direction(inDirection) {}
    
    Vector3 origin;
    Vector3 direction;
};
