#include "Score.h"
#include <string>

Score::Score()
{

}

Score::Score(int x, int y)
{
	this->_score = 1;
	this->_font = TTF_OpenFont("content/Roboto-BoldCondensed.ttf", 32);
	this->_x = x;
	this->_y = y;
}


void Score::draw(SDL_Renderer* renderer)
{
	std::string text = std::to_string(this->_score);
	SDL_Color colour = { 255,255,255,255 };
	SDL_Surface* textSurface = NULL;
	textSurface = TTF_RenderText_Solid(this->_font, text.c_str(), colour);
	if (textSurface != NULL)
	{
		this->_texture = SDL_CreateTextureFromSurface(renderer, textSurface);
		SDL_Rect destRect = { this->_x, this->_y, textSurface->w, textSurface->h };
		SDL_RenderCopy(renderer, this->_texture, NULL, &destRect);

	}

	SDL_FreeSurface(textSurface);
	textSurface = NULL;
	SDL_DestroyTexture(this->_texture);
}

Score::~Score()
{

}
