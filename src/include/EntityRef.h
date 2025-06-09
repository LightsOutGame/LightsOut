#pragma once

#include <memory>

struct EntityControlBlock;

/* Copyable reference to an entity inside our system */
struct EntityRef {
	std::shared_ptr<EntityControlBlock> ctrlBlock;

	bool isAlive();

	friend class EntityHasher;
};

class EntityHasher;

EntityRef makeEntity();