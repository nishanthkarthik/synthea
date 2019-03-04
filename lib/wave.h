#pragma once

#include <cstdlib>
#include <vector>

#include "sequence.h"
#include "common.h"

class Wave {

public:
	Wave(size_t sampling_rate);
	Wave(size_t sampling_rate, std::vector<Sequence> seq);

	void add(Sequence sequences);
	std::vector<amplitude_t> synthesize();

private:
	size_t max_t_end();
	std::vector<amplitude_t> mix(Sequence& a, Sequence& b);
	void overlay(std::vector<amplitude_t>& dest, const Sequence& seq);
	amplitude_t mix(const amplitude_t a, const amplitude_t b) const;

public:

private:
	size_t sampling_rate;
	std::vector<Sequence> sequences;
};
