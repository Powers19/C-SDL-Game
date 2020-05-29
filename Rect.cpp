#include "Rect.h"

//includes reference to window class
Rect::Rect(const Window& window, int x, int y, int w, int h, int R, int G, int B, int a) :
	Window(window), _x(x), _y(y), _w(w), _h(h), _R(R), _G(G), _B(B), _a(a)
{
	draw();
}

void Rect::draw() const
{
	SDL_Rect rect;

	rect.w = _w;
	rect.h = _h;
	rect.x = _x;
	rect.y = _y;

	SDL_SetRenderDrawColor(renderer, _R, _G, _B, _a);
	SDL_RenderFillRect(renderer, &rect);
}

void Rect::pollEvent(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_LEFT:
			_x -= 10;
			break;
		case SDLK_RIGHT:
			_x += 10;
			break;
		case SDLK_UP:
			_y -= 10;
			break;
		case SDLK_DOWN:
			_y += 10;
			break;
		}
	}
}