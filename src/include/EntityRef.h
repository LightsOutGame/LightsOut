#pragma once

#include <memory>

struct EntityControlBlock;

/* Copyable reference to an entity inside our system */
struct EntityRef {
	std::shared_ptr<EntityControlBlock> ctrlBlock;

	bool isAlive();

	bool operator==(const EntityRef& other) const {
		return ctrlBlock.get() == other.ctrlBlock.get();
	}
};

EntityRef makeEntity();