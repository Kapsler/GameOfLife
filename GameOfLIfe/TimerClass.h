#pragma once
#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std::chrono;

class TimerClass
{
public:
	TimerClass();
	TimerClass(const TimerClass&);
	~TimerClass();

	void StartTimer();

	double GetTime() const;
	std::string GetFormattedDuration(std::string text) const;

private:
	std::chrono::high_resolution_clock::time_point startTime;

};