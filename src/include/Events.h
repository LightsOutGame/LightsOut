#pragma once

#include "ComponentKey.h"

namespace Events {
	enum EventType {
		PlayerUpdate,
		EnemyUpdate,
	};

	typedef void (*EventCallback)(void);

	void registerListener(EventType event, ComponentKey key);
}