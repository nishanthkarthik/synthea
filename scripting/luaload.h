#pragma once

#include <memory>
#include "lua.hpp"

struct LuaStateDeleter {
	void operator()(lua_State* ptr) const;
};

class LuaFile {

private:
	void loadfile(std::string filename);
	void print_error();

public:
	LuaFile(std::string filename);
	void call();

private:
	std::unique_ptr<lua_State, LuaStateDeleter> state;
};