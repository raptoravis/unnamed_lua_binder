extern "C" {
	# include "lua.h"
	# include "lauxlib.h"
	# include "lualib.h"
}

#include <iostream>
#include <string>
#include "luawrapper.hpp"

#include "LibLuasocket.h"

class Character {
public:
	Character(const char* name, int hp);
	void say(const char* text);
	void heal(Character* character);
	const char* getName() { return name; }
	int getHealth() { return health; }
	void setHealth(int hp) { health = hp; }
private:
	const char* name;
	int health;
};

Character::Character(const char* name, int hp) {
	this->name = name;
	health = hp;
}

void Character::say(const char* text) {
	std::cout << name << ":" << text << std::endl;
}

void Character::heal(Character* character) {
	character->setHealth(100);
}

Character* Character_new(lua_State* L) {
	const char* name = luaL_checkstring(L, 1);
	int hp = luaL_checknumber(L, 2);
	return new Character(name, hp);
}

int Character_getName(lua_State* L) {
	Character* character = luaW_check<Character>(L, 1);
	lua_pushstring(L, character->getName());
	return 1;
}


int Character_getHealth(lua_State* L) {
	Character* character = luaW_check<Character>(L, 1);
	lua_pushnumber(L, character->getHealth());
	return 1;
}

int Character_setHealth(lua_State* L) {
	Character* character = luaW_check<Character>(L, 1);
	int hp = luaL_checknumber(L, 2);
	character->setHealth(hp);
	return 0;
}

// static functions
static luaL_Reg Character_table[] = {
	{ NULL, NULL }
};

static luaL_Reg Character_metatable[] = {
	{ "getName", Character_getName },
	{ "getHealth", Character_getHealth },
	{ "setHealth", Character_setHealth },
	{ NULL, NULL }
};

static int luaopen_Character(lua_State* L) {
	luaW_register<Character>(L, "Character", Character_table, Character_metatable, Character_new);
	return 1;
}

//https://eliasdaler.wordpress.com/2013/11/30/lua_and_cpp_pt3/
void Character_test() {
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);
	
	FLibLuasocketModule::SetupLuasocket(L);

	luaopen_Character(L);
	if (luaL_loadfile(L, "Character_test.lua")) {
		std::cout << "Error, can't open script" << std::endl;
	}

	lua_pcall(L, 0, 0, 0);
}
