#include "Component.h"

#include "Texture.h"

void Component::DrawUI()
{
    ImGui::Text(GetName().c_str());
}
