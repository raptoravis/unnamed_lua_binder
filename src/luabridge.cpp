#include <iostream>

extern "C" {
    # include "lua.h"
    # include "lauxlib.h"
    # include "lualib.h"
}

#include <LuaBridge/LuaBridge.h>
 
void luabridge_test(const char* lua_file) {
    lua_State* L = luaL_newstate();
	if (luaL_dofile(L, lua_file)) {
		std::cout<<"Error loading script " << lua_file << std::endl;
	}
	else {
		luaL_openlibs(L);

		lua_pcall(L, 0, 0, 0);
		luabridge::LuaRef s = luabridge::getGlobal(L, "testString");
		luabridge::LuaRef n = luabridge::getGlobal(L, "number");
		std::string luaString = s.cast<std::string>();
		int answer = n.cast<int>();
		std::cout << luaString << std::endl;
		std::cout << "And here's our number:" << answer << std::endl;
	}

	lua_close(L);
}
