/*
* EntityRef.cpp
 * Implements the EntityRef struct and related functions for the entity-component
 * system. This provides functionality for checking entity aliveness, hashing entity
 * references, and creating new entities.
 */

#include "EntityRef.h"
#include "EntityControlBlock.h"

// Checks if the referenced entity is still active
bool EntityRef::isAlive() {
    return ctrlBlock->alive;
}

// Computes hash value for an EntityRef based on its UUID
size_t std::hash<EntityRef>::operator()(const EntityRef& k) const {
    return hash<string>()(k.ctrlBlock->uuid);
}

// Creates a new entity with an active control block
EntityRef makeEntity() {
    // Create a new control block
    std::shared_ptr<EntityControlBlock> ctrlBlock = std::make_shared<EntityControlBlock>();

    // Mark the entity as alive
    ctrlBlock->alive = true;

    // Return the entity reference
    return EntityRef(ctrlBlock);
}