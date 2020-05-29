#include "Timer.h"
#include "Window.h"

#include <string>
#include <SDL_ttf.h>

Timer* Timer::tInstance = NULL;

Timer* Timer::Instance()
{
	if (tInstance == NULL)
	{
		tInstance = new Timer();
	}

	return tInstance;
}

void Timer::Release()
{
	delete tInstance;
	tInstance = NULL;
}

void Timer::Stop()
{
	deltaTime = 0;
}

Timer::Timer()
{
	Reset();
	timeScale = 1.0f;
	//countDown = 60;

}



Timer::~Timer()
{

}

void Timer::Reset()
{
	startTicks = SDL_GetTicks();
	elapsedTicks = 0;
	pausedTicks = 0;
	deltaTime = 0.0f;

}

void Timer::Pause()
{

	pausedTicks = SDL_GetTicks() - startTicks;
}

float Timer::DeltaTime()
{

	return deltaTime;
}

void Timer::TimeScale(float t)
{
	timeScale = t;
}

float Timer::TimeScale()
{
	return timeScale;
}


void Timer::update()
{
	elapsedTicks = SDL_GetTicks() - startTicks;
	deltaTime = elapsedTicks * 0.001f; //convert back to float from milliseconds

}

