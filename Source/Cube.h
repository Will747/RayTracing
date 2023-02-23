#pragma once
#include "Mesh.h"

/**
 * A 3D cube that can be rendered by the viewport.
 */
class Cube final : public Mesh
{
public:
    Cube(Vector3 pos, Viewport* viewport);
    
    double DoesRayHit(Ray ray, Colour& outColour) const override;
    std::string GetName() override;
    void DrawUI() override;

private:
    /** The size of the cube. */
    Vector3 dimensions;
};
