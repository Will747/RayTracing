#include "Mesh.h"

#include <imgui.h>

#include "Viewport.h"

Mesh::Mesh(Vector3 pos, Viewport* viewport) : Component(viewport)
{
    position = pos;

    // Give mesh a unique id
    meshCount++;
    id = meshCount;
}

void Mesh::DrawUI()
{
	Component::DrawUI();

    float posF[] = { (float)position.x, (float)-position.y, (float)position.z };
	if (ImGui::DragFloat3("Position", posF, 1, -1000, 1000))
	{
        position.x = posF[0];
        position.y = -posF[1];
        position.z = posF[2];

        GetViewport()->MarkForRender();
	}
}

Vector3 Mesh::GetPosition() const
{
    return position;
}

void Mesh::SetPosition(const Vector3& pos)
{
    position = pos;
}

int Mesh::meshCount = 0;
