#include "Sphere.h"

#include <complex>

Sphere::Sphere(Vector3 inPosition, double inRadius, Colour inColour)
{
    position = inPosition;
    radius = inRadius;
    colour = inColour;
}

double Sphere::DoesRayHit(const Ray ray, Colour& outColour) const
{
    // Intersection Point = p
    // Ray Origin = o
    // Ray Direction = d
    // Distance between p and o = t
    // p = o + dt

    // Sphere Radius = r
    // Sphere Center = c
    // (p - c)^2 = r^2

    // Camera To Sphere = v
    // v = o - c
    const Vector3 cameraToSphere = ray.origin - position;

    // These three equations merge together:
    // (v + dt)^2 = r^2
    // (d^2)t^2 + 2vdt + v^2 - r^2 = 0

    // t can be found using the quadratic formula
    // at^2 + bt + c = 0
    // a = d^2, b = 2vd, c = v^2 - r^2
    
    const double a = ray.direction.dot(ray.direction);
    const double b = 2 * cameraToSphere.dot(ray.direction);
    const double c = cameraToSphere.dot(cameraToSphere) - radius * radius;

    // Discriminant = b^2 - 4ac
    const double discriminant = b * b - 4 * a * c;

    // If the discriminant is below 0 the ray can't hit the sphere.
    if (discriminant < 0) return -1;

    // Not sure what should happen if the ray is a tangent to the sphere.
    if (discriminant == 0) return -1;

    outColour = colour;
    
    // t = (-b +/- sqrt(discriminant)) / 2a
    // There are two solutions but the point closest to the origin is needed
    const double t1 = (-b + std::sqrt(discriminant)) / (2 * a);
    const double t2 = (-b - std::sqrt(discriminant)) / (2 * a);

    if (t1 < t2)
    {
        return t1;
    }

    return t2;
}
