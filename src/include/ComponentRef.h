#pragma once

#include <memory>

#include "Component.h"
#include "EntityRef.h"

struct ComponentRef {
	EntityRef entity;
	std::weak_ptr<Component> ptr;

	Component& operator*();
};
