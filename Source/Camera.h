#pragma once
#include "Component.h"
#include "Vector3.h"

/**
 * Controls which part of the world the viewport renders.
 */
class Camera : public Component
{
public:
    /**
     * Constructs a new camera.
     * @param viewport The viewport using this camera.
     */
    Camera(Viewport* viewport);
 
    void DrawUI() override;
    std::string GetName() override;

    /**
     * @returns The position of the camera.
     */
    Vector3 GetPosition() const;

    /**
     * @returns The direction the camera is pointing (View Plane Normal).
     */
    Vector3 GetDirection() const;

    /**
     * @returns The ViewUpVector.
     */
    Vector3 GetViewUpVector() const;

    /**
     * @returns The ViewRightVector.
     */
    Vector3 GetViewRightVector() const;
private:
    Vector3 position;
    Vector3 viewPlaneNormal;
    Vector3 viewUpVector;
    Vector3 viewRightVector;
};
