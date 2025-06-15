/*
* ComponentRef.h
* Defines the ComponentRef struct for referencing components.
*/

#pragma once

#include <memory>

#include "engine/Component.h"
#include "engine/EntityRef.h"

// Struct for referencing a component and its bound entity
struct ComponentRef {
    // Reference to the entity this component is attached to
    EntityRef entity;
    // Weak pointer to the component instance
    std::weak_ptr<Component> ptr;

    // Dereference operator to access the component
    Component& operator*();
};