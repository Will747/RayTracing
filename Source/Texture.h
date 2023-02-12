#pragma once
#include <cstdint>
#include <imgui.h>
#include <glad/glad.h>

/**
 * Represents a 2D texture used by OpenGL.
 */
class Texture
{
public:
    /**
     * Constructs a new texture object.
     * @param width The width of the texture.
     * @param height The height of the texture.
     */
    Texture(int32_t width, int32_t height);

    /**
     * Constructs a new texture object.
     * @param width The width of the texture.
     * @param height The height of the texture.
     * @param data Pixel data of the texture.
     */
    Texture(int32_t width, int32_t height, const void* data);

    /**
     * Deletes this texture object.
     */
    ~Texture();

    /**
     * @return The ID used by OpenGL to identify this texture.
     */
    GLuint GetTextureID() const;
 
    /**
     * Binds this texture so that any texture commands
     * affect this texture.
     */
    void Bind() const;

    /**
     * Updates the texture with new pixel data.
     * @param data Pixel data for the texture.
     */
    void UpdatePixelData(const void* data) const;

    /**
     * @return The height and width of the texture.
     */
    ImVec2 GetDimensions() const;

    /**
     * @return The width of the texture.
     */
    int32_t GetWidth() const;

    /**
     * @return The height of the texture.
     */
    int32_t GetHeight() const;

private:
    /** ID used by OpenGL to identify texture. */
    GLuint ID;

    /** The width and height of the texture. */
    int32_t width;
    int32_t height;
};
