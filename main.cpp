#include <iostream>
#include <vector>

#include "scripting/luaload.h"
#include "lib/wave.h"

using namespace std;

int main() {
	LuaFile luafile("scripts/test.lua");
	// luafile.call();

	Wave wave(20);

	sequence seq;
	seq.start = 0;
	seq.end = 1000000;
	seq.sampling_rate = 20;
	seq.length = (double)(seq.end - seq.start) * seq.sampling_rate / SEQUENCE_TS_FACTOR;
	seq.amplitude = new amplitude_t[seq.length];

	for (size_t i = 0; i < seq.length; ++i) {
		seq.amplitude[i] = 1000 * (bool)(i < seq.length / 2);
	}

	wave.add(Sequence(seq));

	seq.start = 250000;
	seq.end = 1250000;
	wave.add(Sequence(seq));

	for (auto e : wave.synthesize()) {
		cout << e << ' ';
	}

	cout << endl;

	delete[] seq.amplitude;
	return 0;
}