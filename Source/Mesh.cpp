#include "Mesh.h"

Mesh::Mesh(const Vector3 pos)
{
    position = pos;
}

Vector3 Mesh::GetPosition() const
{
    return position;
}

void Mesh::SetPosition(Vector3& pos)
{
    position = pos;
}
