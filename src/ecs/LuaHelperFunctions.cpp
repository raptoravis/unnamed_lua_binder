#include <iostream>
#include "LuaHelperFunctions.h"

namespace luah {

    void loadGetKeysFunction(lua_State* L) {
        std::string code =
            R"(function getKeys(t)
            s = {}
            for k, v in pairs(t) do 
                table.insert(s, k)
                end 
            return s 
            end)";

        luaL_dostring(L, code.c_str());
    }


	void luah::lua_gettostack(lua_State* L, const std::string& variableName) {
		int level = 0;
		std::string var = "";
		for (unsigned int i = 0; i < variableName.size(); i++) {
			if (variableName.at(i) == '.') {
				if (level == 0) {
					lua_getglobal(L, var.c_str());
				}
				else {
					lua_getfield(L, -1, var.c_str());
				}

				if (lua_isnil(L, -1)) {
					std::cout << "Error, can't get " << variableName << std::endl;
					return;
				}
				else {
					var = "";
					level++;
				}
			}
			else {
				var += variableName.at(i);
			}
		}

		if (level == 0) {
			lua_getglobal(L, var.c_str());
		}
		else {
			lua_getfield(L, -1, var.c_str());
		}

        if (level == 0) { 
            return; 
        } // no need to remove anything
    
        int tableIndex = lua_gettop(L) - level;
        lua_replace(L, tableIndex);
        lua_settop(L, tableIndex);        
	}

    std::vector<std::string> getTableKeys(lua_State* L, const std::string& name) {
		lua_getglobal(L, "getKeys"); // get function

		if (lua_isnil(L, -1)) {
            std::cout << "Get keys function is not loaded. Loading..." << std::endl;
            loadGetKeysFunction(L);
            lua_getglobal(L, "getKeys");
        }

		lua_gettostack(L, name);

        // execute getKeys function.
        // One parameter, one return
        lua_pcall(L, 1, 1, 0); 
        
        std::vector<std::string> keys;

		lua_pushnil(L);
        while (lua_next(L, -2)) { // get values one by one
            if (lua_type(L, -1) == LUA_TSTRING) { // check if key is a string
                keys.push_back(lua_tostring(L, -1));
            }

            lua_pop(L, 1);
        }

        lua_settop(L, 0); // remove s table from stack 

        return keys;
    }

	bool loadScript(lua_State* L, const std::string& filename) {
		if (luaL_loadfile(L, filename.c_str()) || lua_pcall(L, 0, 0, 0)) {
			std::cout<<"Error: failed to load ("<<filename<<")"<<std::endl;

			return 1;
		}

		return 0;
	}

}