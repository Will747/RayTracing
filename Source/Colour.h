#pragma once
#include <cstdint>

struct Colour
{
    /** Red component between 0 and 1. */
    float r;

    /** Green component between 0 and 1. */
    float g;

    /** Blue component between 0 and 1. */
    float b;

    /** Alpha component between 0 and 1. */
    float a;

    /**
     * Construct a new white colour.
     */
    Colour() : r(0.f), g(0.f), b(0.f), a(1.0f) {}

    /**
     * Construct a new colour.
     * @param inR Red value between 0 and 1.
     * @param inG Green value between 0 and 1.
     * @param inB Blue value between 0 and 1.
     * @param inA Alpha value between 0 and 1.
     */
    Colour(float inR, float inG, float inB, float inA)
        : r(inR), g(inG), b(inB), a(inA) {}

    /**
     * Construct a new colour.
     * @param inR Red value between 0 and 255.
     * @param inG Green value between 0 and 255.
     * @param inB Blue value between 0 and 255.
     * @param inA Alpha value between 0 and 255.
     */
    Colour(uint8_t inR, uint8_t inG, uint8_t inB, uint8_t inA)
    {
        r = (float)inR / UINT8_MAX;
        g = (float)inG / UINT8_MAX;
        b = (float)inB / UINT8_MAX;
        a = (float)inA / UINT8_MAX;
    }

    uint32_t GetRGBA()
    {
        uint32_t rgba = (uint8_t)(r * UINT8_MAX);
        rgba |= (uint8_t)(g * UINT8_MAX) << 8;
        rgba |= (uint8_t)(b * UINT8_MAX) << 16;
        rgba |= (uint8_t)(a * UINT8_MAX) << 24;

        return rgba;
    }
};
