/*
 * ComponentRef.cpp
 * Implements the ComponentRef struct.
 * So we can safely reference components with lifecycle checks.
 */

#include "engine/ComponentRef.h"

#include <stdexcept>

// Dereference operator to access the component
Component& ComponentRef::operator*() const {

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

ComponentRef::operator bool() const {
	// Thanks to https://stackoverflow.com/questions/45507041/how-to-check-if-weak-ptr-is-empty-non-assigned
	using wp = std::weak_ptr<Component>;
	return !ptr.owner_before(wp{}) && !wp{}.owner_before(ptr);
}