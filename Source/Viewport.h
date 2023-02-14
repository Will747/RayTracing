#pragma once
#include <memory>
#include <vector>

#include "Colour.h"
#include "Component.h"
#include "Mesh.h"
#include "Texture.h"

/**
 * Generates an image based on rays
 * projected from the camera.
 */
class Viewport
{
public:
	/**
	 * Constructs a new viewport.
	 * @param width The width of the viewport.
	 * @param height The height of the viewport.
	 */
	Viewport(int32_t width, int32_t height);

    /**
     * Regenerates the texture shown by the viewport.
     */
    void UpdateTexture();

    /**
     * @return The texture that should be rendered on screen.
     */
    std::shared_ptr<Texture> GetTexture();

	/**
	 * Draws all controls for adjusting the viewport.
	 */
	void DrawUI();

	/** Background colour. */
	Colour bgColour = Colour(0.f, 0.f, 0.f, 1.f);
private:
	/** Components that affect the viewport. */
	std::vector<Component*> components;

	/** All 3D components being rendered. */
	std::vector<Mesh*> meshes;
	
    /** Texture shown by viewport. */
    std::shared_ptr<Texture> texture;
};
