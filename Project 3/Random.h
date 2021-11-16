#pragma once
#include <random>

class Random {
private:
	static std::mt19937 random;

public:
	static int RandomInt(int min, int max);
};

