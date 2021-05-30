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

Entity* loadEntity(lua_State* L, const std::string& type) {
    auto e = new Entity();
    e->setType(type);
    auto v = luah::getTableKeys(L, type);
    for (auto& componentName : v) {
        if (componentName == "GraphicsComponent") {
            addComponent<GraphicsComponent>(e);
        } else if (componentName == "NpcComponent") {
            addComponent<NpcComponent>(e);
        }
 
        std::cout << "Added " << componentName << " to " << type << std::endl;
    }
    return e;
}