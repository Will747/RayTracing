#include "Camera.h"

#include <imgui.h>
#include <iostream>

#include "Rotation.h"
#include "Viewport.h"

Camera::Camera(Viewport* viewport) : Component(viewport)
{
    position = Vector3(0, 0, -400);

    lookAtPos = Vector3();
    distanceFromLookAt = 500;
    azimuth = 180.001f;
    altitude = 0;
    
    SetDirection(Vector3(0, 0, 1));
}

void Camera::DrawUI()
{
    Component::DrawUI();

    static bool bUseLookAt = false;
    ImGui::Checkbox("Use look at", &bUseLookAt);

    if (bUseLookAt)
    {
        float lookAtPosF[3] = { (float)lookAtPos.x, (float)lookAtPos.y, (float)lookAtPos.z };
        if (ImGui::DragFloat3("Look at", lookAtPosF, 1, -1000, 1000))
        {
            lookAtPos = Vector3((double)lookAtPosF[0], (double)lookAtPosF[1], (double)lookAtPosF[2]);
            UpdateBasedOnLookAt();
        }
        
        if (ImGui::DragFloat("Distance from look at", &distanceFromLookAt))
        {
            UpdateBasedOnLookAt();
        }

        if (ImGui::DragFloat("Azimuth", &azimuth, 1, -360, 360))
        {
            UpdateBasedOnLookAt();
        }

        if (ImGui::DragFloat("Altitude", &altitude, 1, -89, 89))
        {
            UpdateBasedOnLookAt();
        }
    }
    else
    {
        float posF[3] = {(float)position.x, (float)position.y, (float)position.z};
        if (ImGui::DragFloat3("Position", posF, 1, -1000, 1000))
        {
            position.x = (double)posF[0];
            position.y = (double)posF[1];
            position.z = (double)posF[2];
            GetViewport()->MarkForRender();
        }

        static Rotation rotation;
        if (ImGui::DragFloat2("Direction (Yaw, Pitch)", (float*)&rotation, 1, -360, 360))
        {
            SetDirection(rotation.ToUnitVector());
        }   
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

void Camera::SetDirection(Vector3 inVPN)
{
    viewPlaneNormal = inVPN;

    viewRightVector.x = viewPlaneNormal.z;
    viewRightVector.z = -viewPlaneNormal.x;
    viewRightVector.y = 0;
    viewRightVector.Normalise();

    viewUpVector = viewPlaneNormal.CrossProduct(viewRightVector);
    viewUpVector.Normalise();

    GetViewport()->MarkForRender();   
}

void Camera::UpdateBasedOnLookAt()
{
    const Vector3 lookAtDirection = Rotation(azimuth, altitude, 0).ToUnitVector();

    position = lookAtPos + lookAtDirection * (double)distanceFromLookAt;
    SetDirection(-lookAtDirection);

    GetViewport()->MarkForRender();
}
