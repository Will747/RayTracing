#include "Component.h"

#include "Texture.h"

void Component::DrawUI()
{
    ImGui::Text(GetName().c_str());
}

std::string Component::GetName()
{
    return "A Component";
}
