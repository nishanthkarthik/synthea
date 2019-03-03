#include <algorithm>
#include <memory>
#include <limits>

#include "wave.h"

Wave::Wave(size_t sampling_rate): sampling_rate(sampling_rate) {}

Wave::Wave(
	size_t sampling_rate, 
	std::vector<Sequence> sequences)
: sampling_rate(sampling_rate), sequences(sequences) {}

void Wave::add(Sequence sequence) {
	sequences.push_back(sequence);
}

std::vector<amplitude_t> Wave::synthesize() {
	size_t max_t = max_t_end();
	std::vector<Sequence> source = sequences;
	std::for_each(source.begin(), source.end(), 
		[&](Sequence& s) -> void {
			s.resample(sampling_rate);
		});

	// TODO
	// mix all signals

	return std::vector<amplitude_t>();
}

amplitude_t Wave::mix(const amplitude_t a, const amplitude_t b) const {
	const double upper_limit = std::numeric_limits<amplitude_t>::max();
	const double d_a = a / upper_limit;
	const double d_b = b / upper_limit;
	const double mixed_value = d_a + d_b - d_a * d_b;
	return upper_limit * mixed_value;
}


size_t Wave::max_t_end() {
	return std::max_element(
		sequences.begin(), 
		sequences.end(), 
		[](const Sequence& a, const Sequence& b) -> bool {
			return a.get_end() < b.get_end();
		}
	)->get_end();
}