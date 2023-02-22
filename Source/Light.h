#pragma once
#include "Component.h"
#include "Vector3.h"

class Light final : public Component
{
public:
    explicit Light(Viewport* viewport);

    void DrawUI() override;
    std::string GetName() override;
    
    Vector3 GetPosition() const;
private:
    Vector3 position;
};
