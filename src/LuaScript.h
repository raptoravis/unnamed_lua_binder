#ifndef LUASCRIPT_H
#define LUASCRIPT_H

#include <string>
#include <vector>
#include <iostream>

extern "C" {
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}

class LuaScript {
public:
    LuaScript(const std::string& filename);
    virtual ~LuaScript();

	void clean();

    std::vector<int> getIntVector(const std::string& name);
    std::vector<std::string> getTableKeys(const std::string& name);
    
	template<typename T>
	std::vector<T> getArray(const std::string& name) {
		std::vector<T> v;
		if(!lua_gettostack(name.c_str())) {
			printError(name, "Array not found");
			clean();
			return std::vector<T>();
		}
		lua_pushnil(L);
		while(lua_next(L, -2)) {
			v.push_back((T)lua_tonumber(L, -1));
			lua_pop(L, 1);
		}
		clean();
		return v;
	}

    template<typename T>
    T get(const std::string& variableName) {
      if(!L) {
        printError(variableName, "Script is not loaded");
        return lua_getdefault<T>();
      }
      
      T result;
      if(lua_gettostack(variableName)) { // variable succesfully on top of stack
        result = lua_get<T>(variableName);  
      } else {
        result = lua_getdefault<T>();
      }

     
      clean();
      return result;
    }

	// Generic get
    template<typename T>
    T lua_get(const std::string& variableName) {
      return 0;
    }

    template<typename T>
    T lua_getdefault() {
      return 0;
    }
private:
	void printError(const std::string& variableName, const std::string& reason);

	bool lua_gettostack(const std::string& variableName);
private:
    lua_State* L;
    std::string filename;
    int level;
};

 // Specializations
template<>
inline std::vector<std::string> LuaScript::getArray(const std::string& name) {
	std::vector<std::string> v;

	if(!lua_gettostack(name.c_str())) {
		printError(name, "Array not found");
		clean();
		return std::vector<std::string>();
	}

	lua_pushnil(L);
	while(lua_next(L, -2)) {
		v.push_back(std::string(lua_tostring(L, -1)));
		lua_pop(L, 1);
	}

	clean();
	return v;
}

template <> 
inline bool LuaScript::lua_get<bool>(const std::string& variableName) {
    return (bool)lua_toboolean(L, -1);
}

template <> 
inline float LuaScript::lua_get<float>(const std::string& variableName) {
    if(!lua_isnumber(L, -1)) {
      printError(variableName, "Not a number");
    }
    return (float)lua_tonumber(L, -1);
}

template <>
inline int LuaScript::lua_get<int>(const std::string& variableName) {
    if(!lua_isnumber(L, -1)) {
      printError(variableName, "Not a number");
    }
    return (int)lua_tonumber(L, -1);
}

template <>
inline std::string LuaScript::lua_get<std::string>(const std::string& variableName) {
    std::string s = "null";
    if(lua_isstring(L, -1)) {
      s = std::string(lua_tostring(L, -1));
    } else {
      printError(variableName, "Not a string");
    }
    return s;
}

template<>
inline std::string LuaScript::lua_getdefault<std::string>() {
  return "null";
}

#endif
