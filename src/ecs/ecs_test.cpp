#include <iostream>

#include "Entity.h"
#include "LuaHelperFunctions.h"
#include "NpcComponent.h"
#include "GraphicsComponent.h"

//https://eliasdaler.wordpress.com/2015/08/10/using-lua-and-cpp-in-practice/
void ecs_test() {
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	const std::string filename = "ghost.lua";

	luah::loadScript(L, filename.c_str());
	//luah::loadGetKeysFunction(L);

	auto e = Entity::loadEntity(L, "ghost");
	auto npcc = e->get<NpcComponent>();
	std::cout << e->getType() << " says: " << npcc->getPhrase() << std::endl;


	lua_close(L);
}