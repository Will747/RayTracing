#pragma once
#include <string>

/**
 * Configurable item that affects the viewport.
 */
class Component
{
public:
    virtual ~Component() = default;

    /**
     * Draws the ImGui controls for adjusting this component.
     */
    virtual void DrawUI();

    /**
     * @returns The unique name of this component.
     */
    virtual std::string GetName() = 0;

    /** True when selected by the properties panel. */
    bool selected = false;
};
