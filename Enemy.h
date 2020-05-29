#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <vector>
#include "Window.h"


class Enemy : public Window
{
public:
	Enemy(const Window& window, int w, int h, int x, int y, float speed, const std::string& image_path);
	~Enemy();

	void draw();

	void move();

	float _speed;


	SDL_Rect _pos;

	int _w, _h;
	int _x, _y;

	float dirx;
	float diry;

private:


	SDL_Texture* texture = nullptr;
};


