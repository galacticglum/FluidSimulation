#pragma once

#include <chrono>

class Time
{
public:
	static double GetTime();
	static const double SECOND;
private:
	static std::chrono::high_resolution_clock::time_point* m_Epoch;
};