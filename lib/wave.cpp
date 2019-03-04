#include <algorithm>
#include <memory>
#include <limits>
#include <iostream>
#include <queue>
#include <cassert>

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
	size_t max_samples = max_t * sampling_rate / SEQUENCE_TS_FACTOR;

	std::vector<Sequence> source = sequences;
	std::for_each(source.begin(), source.end(), 
		[&](Sequence& s) -> void {
			s.resample(sampling_rate);
		});

	std::vector<amplitude_t> output(max_samples, 0);

	for (const Sequence& seq : sequences) {
		overlay(output, seq);

		std::cout << "+ ";
		for (auto& i : seq.get_amplitude()) {
			std::cout << i << ' ';
		}
		std::cout << std::endl;

		std::cout << "= ";
		for (auto& i : output) {
			std::cout << i << ' ';
		}
		std::cout << std::endl;
	}

	return output;
}

void Wave::overlay(std::vector<amplitude_t>& dest, const Sequence& seq) {
	assert((sampling_rate == seq.get_sampling_rate()));

	size_t start_idx = seq.get_start() * sampling_rate / SEQUENCE_TS_FACTOR;
	const std::vector<amplitude_t>& amplitudes = seq.get_amplitude();

	for (size_t i = 0; i < seq.get_length(); ++i) {
		std::cout << i << ' ' << start_idx + i << ',';
		dest[start_idx + i] = mix(dest[start_idx + i], amplitudes[i]);
	}
	std::cout << std::endl;
}

inline amplitude_t Wave::mix(const amplitude_t a, const amplitude_t b) const {
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