#include <cmath>

#include "sequence.h"

Sequence::Sequence(sequence t) :
length(t.length), 
sampling_rate(t.sampling_rate),
start(t.start),
end(t.end) {
	amplitude.resize(t.length);
	for (size_t i = 0; i < t.length; ++i) {
		amplitude[i] = t.amplitude[i];
	}
}

sequence Sequence::to_sequence() const {
	sequence seq;
	seq.length = length;
	seq.sampling_rate = sampling_rate;
	seq.start = start;
	seq.end = end;
	seq.amplitude = new amplitude_t[amplitude.size()];

	for (size_t i = 0; i < amplitude.size(); ++i) {
		seq.amplitude[i] = amplitude[i];
	}

	return seq;
}

size_t Sequence::get_length() const {
	return length;
}

size_t Sequence::get_sampling_rate() const {
	return sampling_rate;
}

size_t Sequence::get_start() const {
	return start;
}

size_t Sequence::get_end() const {
	return end;
}

void Sequence::resample(size_t new_rate) {
	if (new_rate == sampling_rate) { return; }
	size_t new_length = new_rate * (end - start);
	std::vector<amplitude_t> result(new_length);

	for (size_t i = 0; i < new_length; ++i) {
		size_t pos = floor(i * (double)sampling_rate / new_rate);
		size_t pos_time_start = start + pos * SEQUENCE_TS_FACTOR / (double)sampling_rate;
		size_t pos_time_end = start + (pos + 1) * SEQUENCE_TS_FACTOR / (double)sampling_rate;
		size_t pos_time_new = start + i * SEQUENCE_TS_FACTOR / (double)new_rate;
		result[i] = linear_interpolate(pos_time_new, amplitude[i], pos_time_start, amplitude[i+1], pos_time_end);
	}

	amplitude = result;
}

const std::vector<amplitude_t>& Sequence::get_amplitude() const {
	return amplitude;
}

amplitude_t Sequence::linear_interpolate(
	size_t t,
	amplitude_t a,
	size_t t_a, 
	amplitude_t b, 
	size_t t_b
) {
	if (t_a == t_b) { return (a >> 1) + (b >> 1); }
	return a + (double)(b - a) * (t - t_a) / (t_b - t_a);
}

