// luabridge_character.h
#pragma once

#include <memory>
#include <string>

extern "C" {
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}

#include <LuaBridge/LuaBridge.h>

class Player;
class Character {
public:
    Character();
	virtual ~Character() = default;

    void loadScript(lua_State* L, const std::string& scriptFilename,
        const std::string& tableName);
    
    std::string getName() const { return name; }
    void setName(const std::string& name) { this->name = name; }

	void say(const std::string& text);

    void interact(Player* player);
protected:
    std::string name;
    std::unique_ptr<luabridge::LuaRef> interactFunc;
};

class Player : public Character {
public:
    Player();
 
    int getHp() const { return hp; }
    void setHp(int hp);
 
    int getMaxHp() const { return maxHp; }
    void setMaxHp(int maxHp) { this->maxHp = maxHp; }
private:
    int hp;
    int maxHp;
};