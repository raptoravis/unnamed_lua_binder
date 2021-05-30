#include <iostream>

extern "C" {
    # include "lua.h"
    # include "lauxlib.h"
    # include "lualib.h"
}

#include <LuaBridge/LuaBridge.h>

void printMessage(const std::string& s) {
	std::cout << s << std::endl;
}
 
void luabridge_test(const char* lua_file) {
    lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	luabridge::getGlobalNamespace(L).addFunction("printMessage", printMessage);

	//luabridge::getGlobalNamespace(L).
	//	beginNamespace("game")
	//		.addFunction("printMessage", printMessage)
	//	.endNamespace();

	if (luaL_dofile(L, lua_file)) {
		std::cout<<"Error loading script " << lua_file << std::endl;
	}
	else {
		{
			luabridge::LuaRef sumNumbers = luabridge::getGlobal(L, "sumNumbers");
			int result = sumNumbers(5, 4);
			std::cout << "Result:" << result << std::endl;
		}

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

			std::string titleString = title.cast<std::string>();
			std::cout << titleString << std::endl;

			luabridge::LuaRef size = t["size"];

			{
				luabridge::LuaRef w = size["w"];
				luabridge::LuaRef h = size["h"];
				int width = w.cast<int>();
				int height = h.cast<int>();

				std::cout << "size.w = " << width << std::endl;
				std::cout << "size.h = " << height << std::endl;
			}


			luabridge::LuaRef posx = t["posx"];
			luabridge::LuaRef posy = t["posy"];

			{
				int posx_n = posx.cast<int>();
				int posy_n = posy.cast<int>();

				std::cout << "posx = " << posx_n << std::endl;
				std::cout << "posy = " << posy_n << std::endl;
			}
		}
	}

	lua_close(L);
}
