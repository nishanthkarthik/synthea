#pragma once

#include <cstdio>
#include <vector>

#include "common.h"

enum AUDIO_DIRECTION { LEFT, RIGHT, BOTH };

enum CONSTANTS {
 	SEQUENCE_TS_FACTOR = 1000000
};

struct sequence {
	amplitude_t *amplitude;
	size_t length;
	AUDIO_DIRECTION direction;
	size_t sampling_rate;
	size_t start, end;
};

class Sequence {
public:
	Sequence(sequence t);
	Sequence();

	void from_sequence(sequence t);
	sequence to_sequence() const;

	size_t get_length() const;
	size_t get_sampling_rate() const;
	size_t get_start() const;
	size_t get_end() const;

	void resample(size_t sampling_rate);

private:	
	amplitude_t linear_interpolate(size_t t, amplitude_t a, size_t t_a, amplitude_t b, size_t t_b);

private:
	std::vector<amplitude_t> amplitude;
	size_t length;

	// Hz
	size_t sampling_rate;

	// micros
	size_t start, end;
};