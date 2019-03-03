#include <iostream>

#include "luaload.h"

void LuaStateDeleter::operator()(lua_State *ptr) const {
	lua_close(ptr);
}

LuaFile::LuaFile(std::string filename) {
	state = std::unique_ptr<lua_State, LuaStateDeleter>(luaL_newstate());
	luaL_openlibs(state.get());
	loadfile(filename);
}

void LuaFile::print_error() {
	const char* message = lua_tostring(state.get(), -1);
	std::cout << message << std::endl;
	lua_pop(state.get(), 1);
}

void LuaFile::loadfile(std::string filename) {
	int result = luaL_loadfile(state.get(), filename.c_str());
	if (result != LUA_OK) { print_error(); }
}

void LuaFile::call() {
	int result = lua_pcall(state.get(), 0, LUA_MULTRET, 0);
	if (result != LUA_OK) { print_error(); }
}