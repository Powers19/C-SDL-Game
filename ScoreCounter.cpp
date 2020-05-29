#include "ScoreCounter.h"
#include "Window.h"
#include <iostream>

using namespace std;

ScoreCounter::ScoreCounter(SDL_Renderer* renderer, const std::string& font_path, int fontSize, int score, const SDL_Color& colour)
{
	TTF_Font* font = TTF_OpenFont(font_path.c_str(), fontSize);
	surface = TTF_RenderText_Solid(font, std::to_string(score).c_str(), colour);
	textTexture = SDL_CreateTextureFromSurface(renderer, surface);

	

	int w, h;
	SDL_QueryTexture(textTexture, nullptr, nullptr, &w, &h);
	textRect.w = w;
	textRect.h = h;


}

ScoreCounter::ScoreCounter()
{

}

ScoreCounter::~ScoreCounter()
{
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(textTexture);
}

void ScoreCounter::render(int x, int y, SDL_Renderer* renderer)
{
	textRect.x = x;
	textRect.y = y;

	SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
}

void ScoreCounter::displayScore(int score)
{
	score = score;
	


}


