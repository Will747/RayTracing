#include "Viewport.h"

#include <vector>
#include <cstdlib>

#include "Colour.h"
#include "Ray.h"
#include "Sphere.h"
#include "Vector3.h"

Viewport::Viewport(int32_t width, int32_t height)
{
	texture = std::make_shared<Texture>(width, height);
	camera = std::make_shared<Camera>(this);
	light = std::make_shared<Light>(this);
	
	components.push_back(camera);
	components.push_back(light);

	InitPixelData(width, height);
	AddSphere();
}

void Viewport::UpdateTexture(ImVec2 newSize)
{
	// Get texture dimensions
	int width = texture->GetWidth();
	int height = texture->GetHeight();
	bool bSizeChanged = false;

	constexpr int widthOffset = 20;
	constexpr int heightOffset = 60;

	const int newX = (int)(floor(newSize.x) - widthOffset) / 2;
	const int newY = (int)(floor(newSize.y) - heightOffset) / 2;

	if (newX != width || newY != height)
	{
		width = newX;
		height = newY;
		InitPixelData(width, height);

		bSizeChanged = true;
	}

	if (bNeedsUpdate)
	{
		const Vector3 cameraPos = camera->GetPosition();
		const Vector3 viewPlaneNormal = camera->GetDirection();
		const Vector3 viewUpNormal = camera->GetViewUpVector();
		const Vector3 viewRightNormal = camera->GetViewRightVector();
		
		const Vector3 lightPos = light->GetPosition();

		// Cycle through every pixel in the image
#pragma omp parallel for
		for (int x = 0; x < width; x++)
		{
			for (int y = 0; y < height; y++)
			{
				// Index of pixel in pixelData
				const int index = x + y * width;

				// Ray projected from current pixel
				const Vector3 upPixelOffset = viewUpNormal * ((double)y - height / 2);
				const Vector3 rightPixelOffset = viewRightNormal * ((double)x - width / 2);
				const Vector3 rayOrigin = cameraPos + upPixelOffset + rightPixelOffset;
				const Ray ray(rayOrigin, viewPlaneNormal);

				// Check if ray from pixel intersects the mesh
				Colour pixelColour;
				const Mesh* bestMesh = nullptr;
				double shortestDistance = UINT64_MAX;

				// Go through all meshes, find the closest one hit by the ray
				for (std::shared_ptr<Mesh>& mesh : meshes)
				{
					Colour tempColour;
					const double distance = mesh->DoesRayHit(ray, tempColour);

					if (distance > 0 && distance < shortestDistance)
					{
						shortestDistance = distance;
						bestMesh = mesh.get();
						pixelColour = tempColour;
					}
				}


				// If the bestMesh isn't set no mesh was hit by the ray
				if (bestMesh)
				{
					Vector3 pointOfIntersection = rayOrigin + viewPlaneNormal * shortestDistance;
					Vector3 normal = pointOfIntersection - bestMesh->GetPosition();
					normal.Normalise();

					Vector3 lightDirection = lightPos - pointOfIntersection;
					lightDirection.Normalise();

					float dp = (float)lightDirection.Dot(normal);
					if (dp < 0) dp = 0;
					if (dp > 1) dp = 1;
					pixelColour = pixelColour * dp * 0.7f + pixelColour * 0.3f;

					pixelData[index] = pixelColour.GetRGBA();
				}
				else
				{
					pixelData[index] = bgColour.GetRGBA();
				}
			}
		}

		// Update the texture with the new pixels
		if (bSizeChanged)
		{
			texture->UpdatePixelData(width, height, pixelData);
		} else
		{
			texture->UpdatePixelData(pixelData);
		}

		bNeedsUpdate = false;
	}
}

std::shared_ptr<Texture> Viewport::GetTexture()
{
	return texture;
}

void Viewport::DrawUI()
{
	// Controls tab
	ImGui::Begin("Controls");
	if (ImGui::ListBoxHeader("Components"))
	{
		for (const std::shared_ptr<Component>& component : components)
		{
			AddComponentToList(component);
		}

		for (const std::shared_ptr<Component> component : meshes)
		{
			AddComponentToList(component);
		}
		ImGui::ListBoxFooter();
	}
	
	ImGui::Text("Viewport Controls:");
	ImGui::ColorEdit3("Background Colour", (float*) &bgColour);

	if (ImGui::Button("Add Sphere"))
	{
		AddSphere();
	}

	ImGui::SameLine();
	const std::shared_ptr<Mesh> selectedMesh = std::static_pointer_cast<Mesh>(selectedComponent);
	if (selectedMesh && ImGui::Button("Remove Sphere"))
	{
		meshes.erase(std::remove(meshes.begin(), meshes.end(), selectedMesh));
		selectedComponent = nullptr;
	}
	
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

void Viewport::MarkForRender()
{
	bNeedsUpdate = true;
}

ImVec2 Viewport::GetDisplaySize() const
{
	ImVec2 Result;
	Result.x = (float)texture->GetWidth() * 2;
	Result.y = (float)texture->GetHeight() * 2;

	return Result;
}

void Viewport::AddSphere()
{
	const double randomRadius = 30 + (double)rand() / RAND_MAX * 200.f;
	std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>(Vector3(), randomRadius, Colour::Random(), this);
	meshes.push_back(sphere);

	MarkForRender();
}

void Viewport::AddComponentToList(const std::shared_ptr<Component> component)
{
	const std::string name = component->GetName();
	if (ImGui::Selectable(name.c_str(), component == selectedComponent))
	{
		selectedComponent = component;
	}
}

void Viewport::InitPixelData(const int width, const int height)
{
	delete[] pixelData;
	pixelData = new uint32_t[width * height];

	MarkForRender();
}
