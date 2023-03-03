#pragma once
#include "Mesh.h"

/**
 * A 3D cube that can be rendered by the viewport.
 */
class Cube final : public Mesh
{
public:
    Cube(Vector3 pos, Viewport* viewport);
    
    double DoesRayHit(Ray ray, Vector3& normal, Colour& outColour) const override;
    std::string GetName() override;
    void DrawUI() override;

private:
    enum class Side
    {
        Top,
        Left,
        Right,
        Back ,
        Front,
        Bottom
    };

    static Vector3 GetVectorFromSide(Side s);
    
    /** The size of the cube. */
    Vector3 dimensions;
};
