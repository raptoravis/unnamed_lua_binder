#include <iostream>

#include "Entity.h"

void ecs_test() {
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	const std::string filename = "ghost.lua";
	if (luaL_loadfile(L, filename.c_str()) || lua_pcall(L, 0, 0, 0)) {
		std::cout<<"Error: failed to load ("<<filename<<")"<<std::endl;
		L = 0;
	}

    auto e = loadEntity(L, "ghost");

	lua_close(L);
}