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
    double DoesRayHit(Ray ray, Vector3& outNormal, Colour& outColour) const override;
    std::string GetName() override;

    /**
     * @returns The radius of the sphere.
     */
    double GetRadius() const;
    
private:
    /** The colour of the sphere. */
    Colour colour;

    /** Radius of sphere. */
    double radius;
};
