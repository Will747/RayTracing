#pragma once
#include <string>

class Viewport;

/**
 * Configurable item that affects the viewport.
 */
class Component
{
public:
    /**
     * Constructs a new component.
     * @param viewport The viewport affected by this component.
     */
    explicit Component(Viewport* viewport);

    virtual ~Component() = default;

    /**
     * Draws the ImGui controls for adjusting this component.
     */
    virtual void DrawUI();

    /**
     * @returns The unique name of this component.
     */
    virtual std::string GetName();

    /**
     * @return The viewport affected by this component.
     */
    Viewport* GetViewport() const;

private:
    Viewport* parent;
};
