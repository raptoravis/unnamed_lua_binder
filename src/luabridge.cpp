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
		
		if (s.isNil() || !s.isString()) {
 		   std::cout << "Variable not found!" << std::endl;
		} else {
			std::string luaString = s.cast<std::string>();
			std::cout << luaString << std::endl;
		}
		
		luabridge::LuaRef n = luabridge::getGlobal(L, "number");

		if (n.isNil() || !n.isNumber()) {
 		   std::cout << "Variable not found!" << std::endl;
		} else {
			int answer = n.cast<int>();
			std::cout << "And here's our number:" << answer << std::endl;
		}

		luabridge::LuaRef t = luabridge::getGlobal(L, "window");

		if (t.isNil() || !t.isTable()) {
			std::cout << "Variable not found!" << std::endl;
		} else {
			luabridge::LuaRef title = t["title"];
			luabridge::LuaRef w = t["width"];
			luabridge::LuaRef h = t["height"];

			std::string titleString = title.cast<std::string>();
			int width = w.cast<int>();
			int height = h.cast<int>();

			std::cout << titleString << std::endl;
			std::cout << "width = " << width << std::endl;
			std::cout << "height = " << height << std::endl;
		}
	}

	lua_close(L);
}
