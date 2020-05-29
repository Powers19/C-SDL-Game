#include "Enemy.h"

#include <SDL_image.h>
#include <iostream>
#include <vector>


Enemy::Enemy(const Window& window, int w, int h, int x, int y, float speed, const std::string& image_path) :
	Window(window), _w(w), _h(h), _x(x), _y(y)
{
	//_pos = pos;

	_speed = speed;


	SDL_Surface* surface = IMG_Load(image_path.c_str());
	if (!surface)
	{
		cout << "Failed to create surface";
	}

	texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (!texture)
	{
		cout << "Failed to create texture";
	}

	SDL_FreeSurface(surface);
}

Enemy::~Enemy()
{
	SDL_DestroyTexture(texture);

}

void Enemy::draw()
{
	//_x(x), _y(y);
	//ensures the sprite can move

	SDL_Rect rect = { _x, _y, _w, _h };
	//_pos = rect;

	if (texture)
	{
		SDL_RenderCopy(renderer, texture, NULL, &rect);

	}
	else
	{
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderFillRect(renderer, &rect);
	}



}
std::vector< Enemy > enemies;
void Enemy::move()
{
	bool moveUp = false;

	if ((_y > 60) && (moveUp == false))
	{
		moveUp = true;
		_y -= 100;
	}
	_y += 1;
	if ((_y < 30) && (moveUp == true))
	{
		_y += 1;
		moveUp = false;
	}



}
