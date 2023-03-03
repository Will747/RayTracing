#pragma once
#include "Colour.h"
#include "Component.h"
#include "Ray.h"

/**
 * 3D item that can be rendered in the viewport.
 */
class Mesh : public Component
{
public:
    /**
     * Constructs a new mesh and sets its position.
     * @param pos Position in the world.
     * @param viewport The viewport rendering this mesh.
     */
    Mesh(Vector3 pos, Viewport* viewport);
    
    /**
     * Checks if a ray intersects with this mesh.
     * @param ray The ray being simulated.
     * @param outNormal Direction pointing away from the plane being hit.
     * @param outColour The colour of the mesh at the point of intersection.
     * @return The distance from the origin of the ray to point of intersection
     * or -1 if the ray does not hit the mesh.
     */
    virtual double DoesRayHit(Ray ray, Vector3& outNormal, Colour& outColour) const = 0;

    void DrawUI() override;

    /** @returns The position of this mesh. */
    Vector3 GetPosition() const;

    /**
     * Sets the position of this mesh.
     * @param pos The new position.
     */
    void SetPosition(const Vector3& pos);

protected:
    /** Unique ID for this mesh. */
    int id;
 
private:
    /** Position of the mesh in world. */
    Vector3 position;

    /** Number of meshes created since program started. */
    static int meshCount;
};
