/*
* RenderComponent.cpp
 * Implements the RenderComponent class: a subclass of Component that only has a onRender function
 * instead of the traditional callback map.
 */

#include "RenderComponent.h"

// Constructor
RenderComponent::RenderComponent(EntityRef boundEntity) : Component(boundEntity) {}