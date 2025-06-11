#include "EntityRef.h"
#include "EntityControlBlock.h"

bool EntityRef::isAlive() {
	return ctrlBlock->alive;
}

namespace std {
	template<>
	struct hash<EntityRef> {
		size_t operator()(const EntityRef& k) const {
			return hash<string>()(k.ctrlBlock->uuid);
		}
	};
}

EntityRef makeEntity() {
	std::shared_ptr<EntityControlBlock> ctrlBlock = std::make_shared<EntityControlBlock>();

	ctrlBlock->alive = true;

	return EntityRef(ctrlBlock);
}