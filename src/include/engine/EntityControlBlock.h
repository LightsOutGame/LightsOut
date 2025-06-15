/*
 * EntityControlBlock.h
 * Defines the EntityControlBlock struct for managing entity metadata.
 */

#pragma once

#include <string>

// Struct for storing entity metadata
struct EntityControlBlock {
	// Unique identifier for the entity
	std::string uuid;
	// Flag indicating if the entity is active
	bool alive;
};