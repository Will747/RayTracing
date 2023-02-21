#include "Camera.h"

#include <imgui.h>

#include "Rotation.h"

Camera::Camera(Viewport* viewport) : Component(viewport)
{
    position = Vector3(0, 0, -400);
    viewPlaneNormal = Vector3(0, 0, 1);
    viewUpVector = Vector3(0, 1, 0);
    viewRightVector = Vector3(1, 0, 0);
}

void Camera::DrawUI()
{
    Component::DrawUI();

    float posF[3] = {(float)position.x, (float)position.y, (float)position.z};
    if (ImGui::DragFloat3("Position", posF, 1, -1000, 1000))
    {
        position.x = (double)posF[0];
        position.y = (double)posF[1];
        position.z = (double)posF[2];
    }

    static Rotation rotation;
    if (ImGui::DragFloat2("Direction (Yaw, Pitch)", (float*)&rotation, 1, -360, 360))
    {
        viewPlaneNormal = rotation.ToUnitVector();

        Rotation up = rotation;
        up.Pitch += 90;
        viewUpVector = up.ToUnitVector();

        viewRightVector = viewPlaneNormal.CrossProduct(viewUpVector);

        viewRightVector.Normalise();
    }
}

std::string Camera::GetName()
{
    return "Camera";
}

Vector3 Camera::GetPosition() const
{
    return position;
}

Vector3 Camera::GetDirection() const
{
    return viewPlaneNormal;
}

Vector3 Camera::GetViewUpVector() const
{
    return viewUpVector;
}

Vector3 Camera::GetViewRightVector() const
{
    return viewRightVector;
}
