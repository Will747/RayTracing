#pragma once
#include "Colour.h"
#include "Mesh.h"
#include "Ray.h"
#include "Vector3.h"

/**
 * A 3D Sphere that can be rendered by the viewport.
 */
class Sphere : public Mesh
{
public:
    /**
     * Constructs a new sphere.
     * @param inPosition The center position of the sphere.
     * @param inRadius The radius of the sphere.
     * @param inColour The colour of the sphere.
     */
    Sphere(Vector3 inPosition, double inRadius, Colour inColour, Viewport* viewport);

    void DrawUI() override;
    
    /**
     * Checks if a ray intersects with this sphere.
     * @param ray The ray being simulated.
     * @param outColour The colour of the sphere at the point of intersection.
     * @return The distance from the origin of the ray to point of intersection
     * or -1 if the ray does not hit the sphere.
     */
    double DoesRayHit(Ray ray, Colour& outColour) const override;

    std::string GetName() override;

    double GetRadius() const;
    
private:
    /** The colour of the sphere. */
    Colour colour;

    /** Radius of sphere. */
    double radius;
};
