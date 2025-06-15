/*
 * EntityRef.h
 * Defines the EntityRef struct as the intended way to reference entities, as well as hashing support.
 */

#pragma once

#include <memory>

struct EntityControlBlock;

// Copyable reference to an entity inside our system
struct EntityRef {
	// Shared pointer to the entity's control block
	std::shared_ptr<EntityControlBlock> ctrlBlock;

	// Checks if the referenced entity is still active
	bool isAlive();

	// Equality operator to compare two entity references
	bool operator==(const EntityRef& other) const {
		return ctrlBlock.get() == other.ctrlBlock.get();
	}
};

// Specialization of std::hash for EntityRef to enable use in hash-based containers
template<>
struct std::hash<EntityRef> {
	// Computes hash value for an EntityRef
	size_t operator()(const EntityRef& k) const;
};

// Creates a new entity and returns its reference
EntityRef makeEntity();