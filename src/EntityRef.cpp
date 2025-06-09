#include "EntityRef.h"
#include "EntityControlBlock.h"

using namespace std;

bool EntityRef::isAlive() {
	return ctrlBlock->alive;
}

class EntityHasher {
	public:
	size_t operator()(const EntityRef& e) {
		return hash<string>()(e.ctrlBlock->uuid);
	}
};

EntityRef makeEntity() {
	shared_ptr<EntityControlBlock> ctrlBlock = make_shared<EntityControlBlock>();

	ctrlBlock->alive = true;

	return EntityRef(ctrlBlock);
}