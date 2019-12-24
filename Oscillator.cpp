// 
// 
// 

#include "Oscillator.h"

Oscillator::Oscillator(accum88 new_BPM, saccum78 new_min, saccum78 new_max)
	:BPM(new_BPM),
	min(new_min),
	max(new_max)
{
}

Oscillator::~Oscillator()
{
}

float Oscillator::O1(saccum1516 offset)
{
	return beatsin88(BPM);
}

void Oscillator::update_tempo()
{
}
