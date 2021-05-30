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