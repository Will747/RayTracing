#include "Mesh.h"

#include <imgui.h>

Mesh::Mesh(const Vector3 pos)
{
    position = pos;
}

void Mesh::DrawUI()
{
	Component::DrawUI();

    float posF[] = { (float)position.x, (float)position.y, (float)position.z };
	if (ImGui::SliderFloat3("Position", posF, -1000, 1000))
	{
        position.x = posF[0];
        position.y = posF[1];
        position.z = posF[2];
	}
}

Vector3 Mesh::GetPosition() const
{
    return position;
}

void Mesh::SetPosition(Vector3& pos)
{
    position = pos;
}
