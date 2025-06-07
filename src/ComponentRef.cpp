#include "ComponentRef.h"

#include <exception>

Component& ComponentRef::operator*() {
	if (!entity.isAlive()) {
		throw new std::exception("Attempted to reference component of a dead entity");
	}

	if (ptr.expired()) {
		throw new std::exception("Attempted to reference a dead component");
	}

	return *ptr.lock();
}
