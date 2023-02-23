#include "Cube.h"

#include "Viewport.h"

Cube::Cube(Vector3 pos, Viewport* viewport) : Mesh(pos, viewport)
{
}

double Cube::DoesRayHit(Ray ray, Colour& outColour) const
{
    return -1;
}

std::string Cube::GetName()
{
    return "Cube " + std::to_string(id);
}

void Cube::DrawUI()
{
    Mesh::DrawUI();

    static float dimensionsF[3] = { 50, 50, 50 };
    if (ImGui::DragFloat3("Size", dimensionsF, 1, 0, 200))
    {
        dimensions.x = (double)dimensionsF[0];
        dimensions.y = (double)dimensionsF[1];
        dimensions.z = (double)dimensionsF[2];

        GetViewport()->MarkForRender();
    }
}
