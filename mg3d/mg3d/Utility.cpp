#include "Utility.h"

float util::random_float(const float& a, const float& b)
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> dist(a, b);

	return dist(mt);
}