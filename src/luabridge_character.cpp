#include "luabridge_character.h"

Character::Character() : interactFunc(nullptr)
{ }


void Character::say(const std::string& text) {
    std::cout << name << ": " << text << std::endl;
}
 
void Character::loadScript(lua_State* L, const std::string& scriptFilename, const std::string& tableName) {
    using namespace luabridge;
    if (luaL_dofile(L, scriptFilename.c_str()) == 0) { // script has opened
        LuaRef table = getGlobal(L, tableName.c_str());
        if (table.isTable()) {
            if (table["name"].isString()) {
                name = table["name"].cast<std::string>();
            } else {
                name = "Null";
            }
 
            if (table["interact"].isFunction()) {
                interactFunc = std::make_unique<LuaRef>(table["interact"]);
            }
        }
    } else {
        std::cout << "Error, can't open script!" << std::endl;
    }
}

void Character::interact(Player* player) {
    if (interactFunc) {
        try {
            (*interactFunc)(this, player);
        }
        catch (luabridge::LuaException const& e) {
            std::cout << "LuaException: " << e.what() << std::endl;
        }
    }
}

Player::Player() : Character(), maxHp(10)
{
    hp = maxHp;
}
 
void Player::setHp(int hp) {
    this->hp = hp;
    std::cout << "> Player: " << hp << " HP" << std::endl;
}

//https://eliasdaler.wordpress.com/2014/11/01/using-lua-with-c-luabridge-part-2-using-scripts-for-object-behaviour/
void luabridge_test_character() {
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	luabridge::getGlobalNamespace(L)
		.beginClass<Character>("Character")
			.addConstructor<void(*)(void)>()
			.addProperty("name", &Character::getName, &Character::setName)
			.addFunction("say", &Character::say)
		.endClass()
		.deriveClass<Player, Character>("Player")
			.addProperty("hp", &Player::getHp, &Player::setHp)
			.addProperty("maxHp", &Player::getMaxHp, &Player::setMaxHp)
		.endClass();

	{
		Player player;

		player.setName("Player");

		Character witch;
		witch.loadScript(L, "witch.lua", "witch");

		Character guard;
		guard.loadScript(L, "guard.lua", "guard");

		std::cout << "|Player walks around the town and talks with some npcs" << std::endl;
		witch.interact(&player);
		guard.interact(&player);

		std::cout << "|Player goes on a great adventure!" << std::endl;
		std::cout << "|but gets beaten up by some foes..." << std::endl;
		player.setHp(player.getHp() - 5);
		std::cout << "|Back to the town... Let's talk to the witch" << std::endl;
		witch.interact(&player);
	}

	lua_close(L);
}
