/*
 * Component.cpp
 * Implements the base Component class for the entity-component system.
 * Provides functionality for initializing components, handling events, and
 * managing callback mappings for derived components.
 */

#include "engine/Component.h"

// Constructor, initializes component with a reference to the Component's Entity
Component::Component(EntityRef boundEntity): entity(boundEntity) {}
