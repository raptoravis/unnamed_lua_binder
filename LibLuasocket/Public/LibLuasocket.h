// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

struct lua_State;

#define LIBLUASOCKET_API 

class LIBLUASOCKET_API FLibLuasocketModule
{
public:

	static void SetupLuasocket(lua_State* L);
	static void CloseLuasocket(lua_State* L);

protected:
	static int OpenLuaSocketFtp(lua_State* L);
	static int OpenLuaSocketHeaders(lua_State* L);
	static int OpenLuaSocketHttp(lua_State* L);
	static int OpenLuaSocketLtn12(lua_State* L);
	static int OpenLuaSocketMbox(lua_State* L);
	static int OpenLuaSocketMime(lua_State* L);
	static int OpenLuaSocketSmtp(lua_State* L);
	static int OpenLuaSocketSocket(lua_State* L);
	static int OpenLuaSocketTp(lua_State* L);
	static int OpenLuaSocketUrl(lua_State* L);
};
