#pragma once

#include <map>
#include <string>
#include <typeindex>

#include "Component.h"

class Entity {
public:
    ~Entity();
    void addComponent(std::type_index type, Component* c);

    template <typename T>
    T* get() {
        auto it = components.find(std::type_index(typeid(T)));
        if (it != components.end()) {
            return dynamic_cast<T*>(it->second);
        }
        return nullptr;
    }
    
    void setType(const std::string& type) {
        this->type = type;
    }

    std::string getType() const {
        return type;
    }

	template <typename T>
	static void addComponent(Entity* e, luabridge::LuaRef& componentTable) {
		e->addComponent(std::type_index(typeid(T)), new T(componentTable));
	}

	static Entity* loadEntity(lua_State* L, const std::string& type);

private:
    std::string type;
    std::map<std::type_index, Component*> components;
};

