#pragma once
#include <chrono>

using namespace std::chrono;

class TimerClass
{
public:
	TimerClass();
	TimerClass(const TimerClass&);
	~TimerClass();

	void StartTimer();

	double GetTime() const;

private:
	std::chrono::high_resolution_clock::time_point startTime;

};