#pragma once
#include <memory>

#include "Colour.h"
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

	/** Background colour. */
	Colour bgColour = Colour(0.f, 0.f, 0.f, 1.f);
private:
    /** Texture shown by viewport. */
    std::shared_ptr<Texture> texture;
};
