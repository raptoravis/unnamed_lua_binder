#include <iostream>

#include "Entity.h"
#include "Component.h"
#include "GraphicsComponent.h"
#include "NpcComponent.h"
#include "LuaHelperFunctions.h"

Entity::~Entity() {
    for (auto& c : components) {
        delete c.second;
    }
}

void Entity::addComponent(std::type_index type, Component* c) {
    components[type] = c;
}

Entity* Entity::loadEntity(lua_State* L, const std::string& type) {
	using namespace luabridge;
	
	auto e = new Entity();
	e->setType(type);
	auto v = luah::getTableKeys(L, type);
	LuaRef entityTable = getGlobal(L, type.c_str());
	for (auto& componentName : v) {
		if (componentName == "GraphicsComponent") {
			LuaRef gcTable = entityTable["GraphicsComponent"];
			Entity::addComponent<GraphicsComponent>(e, gcTable);
		} else if (componentName == "NpcComponent") {
			LuaRef npcTable = entityTable["NpcComponent"];
			Entity::addComponent<NpcComponent>(e, npcTable);
		}

		std::cout << "Added " << componentName << " to " << type << std::endl;
	}

    return e;
}