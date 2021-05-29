#include <iostream>
#include <string>

#include "LuaScript.h"

void luascript_test() {
    LuaScript script("Player.lua");
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

void embedlua_test ()
{
	lua_State *l = luaL_newstate();
	luaL_openlibs(l);

	/* register host API for script */
	lua_register(l, "hostgetversion", hostgetversion);

	/* load script */
	luaL_dofile(l, "mood.lua");

	/* call mood() provided by script */
	lua_getglobal(l, "mood");
	lua_pushboolean(l, 1);
	lua_call(l, 1, 1);
	printf("The mood is %s\n", lua_tostring(l, -1));
	lua_pop(l, 1);

	lua_close(l);
}


int main() {
	luascript_test();

	embedlua_test();

	return 0;
}