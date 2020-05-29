#pragma once
#include "Window.h"
#include <SDL.h>

class Rect : public Window //allows use of inheritance from the window class, need to use the same renderer
{
public:
	Rect(const Window& window, int x, int y, int w, int h, int R, int G, int B, int a);

	void draw() const;
	void pollEvent(SDL_Event& event);

	int _w, _h;
	int _x, _y;

private:

	int _R, _G, _B, _a;
};
