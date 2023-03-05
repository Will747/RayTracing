#pragma once
#include "Component.h"
#include "Vector3.h"

/**
 * A spot light that illuminates part of the scene.
 */
class Light final : public Component
{
public:
    explicit Light(Viewport* viewport);

    void DrawUI() override;
    std::string GetName() override;
    
    Vector3 GetPosition() const;
    float GetIntensity() const;
private:
    Vector3 position;
    float intensity;
};
