#include "Light.h"

#include <imgui.h>

#include "Viewport.h"

Light::Light(Viewport* viewport) : Component(viewport)
{
    position = Vector3(0, 300, -400);
    intensity = 0.4f;
}

void Light::DrawUI()
{
    Component::DrawUI();

    float posF[3] = {(float)position.x, (float)-position.y, (float)position.z};
    if (ImGui::DragFloat3("Position", posF, 1, -1000, 1000))
    {
        position.x = (double)posF[0];
        position.y = (double)-posF[1];
        position.z = (double)posF[2];
        GetViewport()->MarkForRender();
    }

    const float viewportAmbient = GetViewport()->GetAmbientLightIntensity();
    if (ImGui::DragFloat("Intensity", &intensity, 0.01f, .05f, 1 - viewportAmbient))
    {
        GetViewport()->MarkForRender();
    }
}

std::string Light::GetName()
{
    return "Light";
}

Vector3 Light::GetPosition() const
{
    return position;
}

float Light::GetIntensity() const
{
    return intensity;
}
