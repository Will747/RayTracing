#include "Viewport.h"

#include <vector>

#include "Colour.h"
#include "Ray.h"
#include "Sphere.h"
#include "Vector3.h"

Viewport::Viewport(int32_t width, int32_t height)
{
	texture = std::make_shared<Texture>(width, height);
}

void Viewport::UpdateTexture()
{
	// Get texture dimensions
	int width = texture->GetWidth();
	int height = texture->GetHeight();

	// Create new array of pixels to form a new texture
	uint32_t* pixelData = new uint32_t[width * height];

	// Sphere params
	const Colour sphereColour(0.5f, 0.0f, 0.4f, 1.0f);
	const Sphere testSphere(Vector3(), (double)100.f, sphereColour);

	const Vector3 cameraDirection(0, 0, 1);

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

			// Check if ray from pixel intersects the sphere
			Colour pixelColour;
			const double distance = testSphere.DoesRayHit(ray, pixelColour);
			
			// If the distance isn't -1 the ray hit the sphere
			if (distance >= 0)
			{
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
