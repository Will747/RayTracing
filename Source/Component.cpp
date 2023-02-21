#include "Component.h"

#include "Texture.h"

Component::Component(Viewport* viewport)
{
    parent = viewport;
}

void Component::DrawUI()
{
    ImGui::Text(GetName().c_str());
}

std::string Component::GetName()
{
    return "A Component";
}

Viewport* Component::GetViewport() const
{
    return parent;
}
