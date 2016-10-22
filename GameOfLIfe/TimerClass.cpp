#include "TimerClass.h"

TimerClass::TimerClass()
{
}

TimerClass::TimerClass(const TimerClass& other)
{
}

TimerClass::~TimerClass()
{
}

void TimerClass::StartTimer()
{
	startTime = high_resolution_clock::now();
}

double TimerClass::GetTime() const
{
	std::chrono::duration<double> roundTime = duration_cast<duration<double>>(high_resolution_clock::now() - startTime);
	return roundTime.count();
}
