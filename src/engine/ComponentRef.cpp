/*
 * ComponentRef.cpp
 * Implements the ComponentRef struct.
 * So we can safely reference components with lifecycle checks.
 */

#include "engine/ComponentRef.h"

#include <stdexcept>

// Dereference operator to access the component
Component& ComponentRef::operator*() {
	// Check if the entity is still alive
	if (!entity.isAlive()) {
		throw std::runtime_error("Attempted to reference component of a dead entity");
	}

	// Check if the component pointer is still valid
	if (ptr.expired()) {
		throw std::runtime_error("Attempted to reference a dead component");
	}

	// Return the component instance
	return *ptr.lock();
}