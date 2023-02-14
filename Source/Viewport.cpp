#include "Viewport.h"

#include <vector>

#include "Colour.h"
#include "Ray.h"
#include "Sphere.h"
#include "Vector3.h"

Viewport::Viewport(int32_t width, int32_t height)
{
	texture = std::make_shared<Texture>(width, height);

	// Sphere params
	const Colour sphereColour(0.5f, 0.0f, 0.4f, 1.0f);
	Sphere* testSphere = new Sphere(Vector3(), (double)100.f, sphereColour);
	meshes.push_back(testSphere);
}

void Viewport::UpdateTexture()
{
	// Get texture dimensions
	int width = texture->GetWidth();
	int height = texture->GetHeight();

	// Create new array of pixels to form a new texture
	uint32_t* pixelData = new uint32_t[width * height];

	const Vector3 cameraDirection(0, 0, 1);
	const Vector3 lightPos(0, 300, -400);

	// Cycle through every pixel in the image
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			// Index of pixel in pixelData
			const int index = x + y * width;

			// Ray projected from current pixel
			const Vector3 rayOrigin(x - width / 2, y - height / 2, -400);
			const Ray ray(rayOrigin, cameraDirection);

			// Check if ray from pixel intersects the mesh
			Colour pixelColour;
			const Mesh* bestMesh = nullptr;
			double shortestDistance = UINT64_MAX;

			// Go through all meshes, find the closest one hit by the ray
			for (const Mesh* mesh : meshes)
			{
				Colour tempColour;
				const double distance = mesh->DoesRayHit(ray, tempColour);

				if (distance > 0 && distance < shortestDistance)
				{
					shortestDistance = distance;
					bestMesh = mesh;
					pixelColour = tempColour;
				}
			}
				
			
			// If the bestMesh isn't set no mesh was hit by the ray
			if (bestMesh)
			{
				Vector3 pointOfIntersection = rayOrigin + cameraDirection * shortestDistance;
				Vector3 normal = pointOfIntersection - bestMesh->GetPosition();
				normal.Normalise();

				Vector3 lightDirection = lightPos - pointOfIntersection;
				lightDirection.Normalise();
				
				double dp = lightDirection.Dot(normal);
				if (dp < 0) dp = 0;
				if (dp > 1) dp = 1;
				pixelColour = pixelColour * dp * 0.7 + pixelColour * 0.3;
				
				pixelData[index] = pixelColour.GetRGBA();
			} else
			{
				pixelData[index] = bgColour.GetRGBA();
			}
		}
	}

	// Update the texture with the new pixels
	texture->UpdatePixelData(pixelData);
	delete[] pixelData;
}

std::shared_ptr<Texture> Viewport::GetTexture()
{
	return texture;
}

void Viewport::DrawUI()
{
	static Component* selectedComponent = nullptr;

	// Controls tab
	ImGui::Begin("Controls");
	ImGui::ListBoxHeader("Components");
	for (Component* component : components)
	{
		std::string name = component->GetName();
		if (ImGui::Selectable(name.c_str(), component->selected))
		{
			component->selected = true;
			selectedComponent = component;
		}
	}

	for (Component* component : meshes)
	{
		std::string name = component->GetName();
		if (ImGui::Selectable(name.c_str(), component->selected))
		{
			component->selected = true;
			selectedComponent = component;
		}
	}
	ImGui::ListBoxFooter();
	
	ImGui::Text("Viewport Controls:");
	ImGui::ColorEdit3("Background Colour", (float*) &bgColour);
	
	ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
		ImGui::GetIO().Framerate);
	ImGui::End();

	// Properties tab
	ImGui::Begin("Properties");
	if (selectedComponent)
	{
		selectedComponent->DrawUI();
	} else
	{
		ImGui::Text("No component selected");
	}
	ImGui::End();
}
