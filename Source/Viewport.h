#pragma once
#include <memory>
#include <vector>

#include "Camera.h"
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
	/** Adds a new sphere to the viewport. */
	void AddSphere();

	/** Adds a component to the list in controls window. */
	void AddComponentToList(std::shared_ptr<Component> component);

	/** Creates pixel data array of the correct size for the texture. */
	void InitPixelData();

	/** The component currently selected. */
	std::shared_ptr<Component> selectedComponent;

	/** Components that affect the viewport. */
	std::vector<std::shared_ptr<Component>> components;

	/** All 3D components being rendered. */
	std::vector<std::shared_ptr<Mesh>> meshes;

	/** The camera. */
	std::shared_ptr<Camera> camera;
	
    /** Texture shown by viewport. */
    std::shared_ptr<Texture> texture;

	/** Raw pixel data. */
	uint32_t* pixelData = nullptr;

	/** True when the texture needs regenerating. */
	bool bNeedsUpdate = false;
};
