#include "Sphere.h"

#include <complex>
#include <imgui.h>

#include "Viewport.h"

Sphere::Sphere(Vector3 inPosition, double inRadius, Colour inColour, Viewport* viewport) : Mesh(inPosition, viewport)
{
    radius = inRadius;
    colour = inColour;

    // Give sphere a unique id
    sphereCount++;
    id = sphereCount;
}

void Sphere::DrawUI()
{
    Mesh::DrawUI();

    if (ImGui::ColorEdit3("Sphere Colour", (float*) &colour))
    {
        GetViewport()->MarkForRender();
    }

    float radiusf = (float)radius;
    if (ImGui::SliderFloat("Sphere Radius", &radiusf, 0, 500))
    {
        radius = (double)radiusf;
        GetViewport()->MarkForRender();
    }
}

double Sphere::DoesRayHit(const Ray ray, Colour& outColour) const
{
    // Intersection Point = p
    // Ray Origin = o
    // Ray Direction = d
    // Distance between p and o = t
    // p = o + dt

    // Sphere Radius = r
    // Sphere Center = c
    // (p - c)^2 = r^2

    // Camera To Sphere = v
    // v = o - c
    const Vector3 cameraToSphere = ray.origin - GetPosition();

    // These three equations merge together:
    // (v + dt)^2 = r^2
    // (d^2)t^2 + 2vdt + v^2 - r^2 = 0

    // t can be found using the quadratic formula
    // at^2 + bt + c = 0
    // a = d^2, b = 2vd, c = v^2 - r^2
    
    const double a = ray.direction.Dot(ray.direction);
    const double b = 2 * cameraToSphere.Dot(ray.direction);
    const double c = cameraToSphere.Dot(cameraToSphere) - radius * radius;

    // Discriminant = b^2 - 4ac
    const double discriminant = b * b - 4 * a * c;

    // If the discriminant is below 0 the ray can't hit the sphere.
    if (discriminant < 0) return -1;

    // Not sure what should happen if the ray is a tangent to the sphere.
    if (discriminant == 0) return -1;

    outColour = colour;
    
    // t = (-b +/- sqrt(discriminant)) / 2a
    // There are two solutions but the point closest to the origin is needed
    const double t1 = (-b + std::sqrt(discriminant)) / (2 * a);
    const double t2 = (-b - std::sqrt(discriminant)) / (2 * a);

    if (t1 < t2)
    {
        return t1;
    }

    return t2;
}

std::string Sphere::GetName()
{
    return "Sphere " + std::to_string(id);
}

double Sphere::GetRadius() const
{
    return radius;
}

int Sphere::sphereCount = 0; 
