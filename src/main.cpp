#include <iostream>
#include <string>

#include "LuaScript.h"

#include "LibLuasocket.h"

//https://eliasdaler.wordpress.com/2013/10/11/lua_cpp_binder/
void luascript_test(const char* lua_file) {
    LuaScript script(lua_file);

    float posX = script.get<float>("player.position.x");
    float posY = script.get<float>("player.position.y");
    std::string filename = script.get<std::string>("player.filename");
    int hp = script.get<int>("player.HP");

    std::cout<<"Position X = "<<posX<<", Y = "<<posY<<std::endl;
    std::cout<<"Filename:"<<filename<<std::endl;
    std::cout<<"HP:"<<hp<<std::endl;

    // getting arrays
    std::vector<int> v = script.getIntVector("array");
    std::cout<<"Contents of array:";
    for(std::vector<int>::iterator it = v.begin();
            it != v.end();
            it++) {
            std::cout<<*it<<",";
    }
    std::cout<<std::endl;

    // getting table keys:
    std::vector<std::string> keys = script.getTableKeys("player");
    std::cout<<"Keys of [player] table:";
    for(std::vector<std::string>::iterator it = keys.begin();
            it != keys.end();
            it++) {
            std::cout<<*it<<",";
    }

    std::cout<<std::endl;
}

/* 
* define a function that returns version information to lua scripts
*/
static int hostgetversion(lua_State *l)
{
	/* Push the return values */
	lua_pushnumber(l, 0);
	lua_pushnumber(l, 99);
	lua_pushnumber(l, 32);

	/* Return the count of return values */
	return 3;
}

//https://riptutorial.com/lua/example/3129/calling--lua-functions
void embedlua_test (const char* lua_file)
{
	lua_State *l = luaL_newstate();
	luaL_openlibs(l);

	FLibLuasocketModule::SetupLuasocket(l);

	/* register host API for script */
	lua_register(l, "hostgetversion", hostgetversion);
	/**
	lua_pushcfunction(L, hostgetversion);
	lua_setglobal(L, "hostgetversion"); // this is how function will be named in Lua
	*/

	/**
	if (luaL_loadfile(L, "mood.lua")) {
	std::cout<<"Error loading script"<<std::endl;
	}
	lua_pcall(L, 0, 0, 0); // run script
	*/

	/* load script */
	if (luaL_dofile(l, lua_file)) {
		std::cout<<"Error loading script " << lua_file << std::endl;
	}
	else {
		/* call mood() provided by script */
		lua_getglobal(l, "mood");
		lua_pushboolean(l, 1);
		lua_call(l, 1, 1);
		printf("The mood is %s\n", lua_tostring(l, -1));
		lua_pop(l, 1);
	}

	lua_close(l);
}

void Character_test(const char* lua_file);
void luabridge_test(const char* lua_file);

int main() {
	luascript_test("Player.lua");

	embedlua_test("mood.lua");
	
	Character_test("Character_test.lua");

	luabridge_test("luabridge_test.lua");

	return 0;
}
