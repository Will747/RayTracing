#include "Cube.h"

#include "Viewport.h"

Cube::Cube(Vector3 pos, Viewport* viewport) : Mesh(pos, viewport)
{
    dimensions = Vector3(50, 50, 50);
    colour = Colour::Random();
}

double Cube::DoesRayHit(Ray ray, Vector3& normal, Colour& outColour) const
{
    outColour = colour;

    // Based on https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-box-intersection.html
    // Intersection Point = p
    // Ray Origin = o
    // Ray Direction = d
    // Distance between p and o = t
    // p = o + dt

    // Set the point of intersection to an edge of the cube
    // c = A corner of the cube in one axis
    // c = o + dt
    // t = (c - o) / d

    const Vector3 pos = GetPosition();
    
    double tLowerX = (pos.x  - ray.origin.x) / ray.direction.x;
    double tUpperX = (pos.x + dimensions.x - ray.origin.x) / ray.direction.x;
    double tLowerY = (pos.y - ray.origin.y) / ray.direction.y;
    double tUpperY = (pos.y + dimensions.y - ray.origin.y) / ray.direction.y;
    double tLowerZ = (pos.z - ray.origin.z) / ray.direction.z;
    double tUpperZ = (pos.z + dimensions.z - ray.origin.z) / ray.direction.z;

    if (ray.direction.x < 0)
    {
        const double temp = tLowerX;
        tLowerX = tUpperX;
        tUpperX = temp;
    }

    if (ray.direction.y < 0)
    {
        const double temp = tLowerY;
        tLowerY = tUpperY;
        tUpperY = temp;
    }

    if (ray.direction.z < 0)
    {
        const double temp = tLowerZ;
        tLowerZ = tUpperZ;
        tUpperZ = temp;
    }

    // Check if ray goes through x, y plane
    if (tLowerX > tUpperY || tLowerY > tUpperX)
    {
        return -1;
    }

    // The value of t at the two points of intersection
    double firstT = tLowerX;
    double secondT = tUpperX;

    Side firstS = Side::Left;
    Side secondS = Side::Right;

    // Check if the ray first hits a y plane instead of x 
    if (firstT < tLowerY)
    {
        firstT = tLowerY;
        firstS = Side::Bottom;
    }

    if (secondT > tUpperY)
    {
        secondT = tUpperY;
        secondS = Side::Top;
    }

    // Check if ray also goes within z plane
    if (firstT > tUpperZ || secondT < tLowerZ)
    {
        return -1;
    }

    // Check if the z plane is the one the ray first intersects
    if (firstT < tLowerZ)
    {
        firstT = tLowerZ;
        firstS = Side::Front;
    }

    if (secondT > tUpperZ)
    {
        secondT = tUpperZ;
        secondS = Side::Back;
    }

    if (firstT > secondT)
    {
        normal = GetVectorFromSide(secondS);
        return secondT;
    }

    normal = GetVectorFromSide(firstS);
    return firstT;
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

    if (ImGui::ColorEdit3("Cube Colour", (float*)&colour))
    {
        GetViewport()->MarkForRender();
    }
}

Vector3 Cube::GetVectorFromSide(const Side s)
{
    switch (s)
    {
    case Side::Top:
        return Vector3(0, 1, 0);
    case Side::Left:
        return Vector3(-1, 0, 0);
    case Side::Right:
        return Vector3(1, 0, 0);
    case Side::Back:
        return Vector3(0, 0, -1);
    case Side::Front:
        return Vector3(0, 0, 1);
    case Side::Bottom:
        return Vector3(0, -1, 0);
    }

    return Vector3();
}
