#include "ComponentRef.h"

#include <stdexcept>

Component& ComponentRef::operator*() {
	if (!entity.isAlive()) {
		throw std::runtime_error("Attempted to reference component of a dead entity");
	}

	if (ptr.expired()) {
		throw std::runtime_error("Attempted to reference a dead component");
	}

	return *ptr.lock();
}
