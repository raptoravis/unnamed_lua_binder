#pragma once

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

#include <LuaBridge/LuaBridge.h>

//namespace luabridge {
//    class LuaRef;   
//} // forward declaration

class Component {
public:
    virtual ~Component() {};
};