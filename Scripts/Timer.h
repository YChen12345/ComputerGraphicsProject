#pragma once

#include <Windows.h>

class Timer
{
public:
	LARGE_INTEGER prev;
	LARGE_INTEGER now;
	LARGE_INTEGER freq;
	float deltaTime = 0;
	Timer()
	{
		QueryPerformanceFrequency(&freq);
		QueryPerformanceCounter(&prev);
	}
	float dt()
	{
		QueryPerformanceCounter(&now);
		float dtn = ((float)(now.QuadPart - prev.QuadPart) / (float)freq.QuadPart);// * 0.001f;
		prev = now;
		deltaTime = dtn;
		return dtn;
	}
};