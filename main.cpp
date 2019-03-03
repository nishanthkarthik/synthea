#include <iostream>
#include <vector>

#include "scripting/luaload.h"
#include "lib/wave.h"

using namespace std;

int main() {
	LuaFile luafile("scripts/test.lua");
	luafile.call();

	Wave wave(48000);

	return 0;
}