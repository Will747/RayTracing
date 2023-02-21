#include "Texture.h"

#include <vector>

Texture::Texture(const int32_t inWidth, const int32_t inHeight)
{
    width = inWidth;
    height = inHeight;

    // Create and bind a new texture
    ID = 0;
    glGenTextures(1, &ID);
    Bind();

    // Generate the texture
    const std::vector<uint32_t> blankData(width * height);
    UpdatePixelData(inWidth, inHeight, blankData.data());
}

Texture::Texture(const int32_t inWidth, const int32_t inHeight, const void* data)
{
    // Create and bind a new texture
    ID = 0;
    glGenTextures(1, &ID);
    Bind();

    UpdatePixelData(inWidth, inHeight, data);
}

Texture::~Texture()
{
    glDeleteTextures(1, &ID);
}

GLuint Texture::GetTextureID() const
{
    return ID;
}

void Texture::Bind() const
{
    glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::UpdatePixelData(const void* data) const
{
    Bind();
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
}

void Texture::UpdatePixelData(const int32_t inWidth, const int32_t inHeight, const void* data)
{
    width = inWidth;
    height = inHeight;

    Bind();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height,
        0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
}

ImVec2 Texture::GetDimensions() const
{
    return {(float)width, (float)height};
}

int32_t Texture::GetWidth() const
{
    return width;
}

int32_t Texture::GetHeight() const
{
    return height;
}
