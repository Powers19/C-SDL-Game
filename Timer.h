#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class Timer
{
public:

	Timer();
	~Timer();

	static Timer* Instance();
	static void Release();

	void Reset();
	void Stop();
	float DeltaTime();



	void TimeScale(float t);
	float TimeScale();


	void Pause();
	void update();


private:
	static Timer* tInstance;

	SDL_Texture* texture;
	SDL_Rect tRect;
	SDL_Surface* surface;

	unsigned int startTicks;
	unsigned int elapsedTicks;
	int pausedTicks;
	float deltaTime;
	float timeScale;





};

