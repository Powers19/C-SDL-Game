#pragma once
#include <SDL_ttf.h>
#include <SDL.h>
#include <string>

class ScoreCounter
{

public:
	ScoreCounter(SDL_Renderer* renderer, const std::string& font_path, int fontSize, int score, const SDL_Color& colour);

	ScoreCounter();
	~ScoreCounter();
	

	void render(int x, int y, SDL_Renderer* renderer);


	void displayScore(int score);

private:
	SDL_Texture* textTexture = nullptr;
	SDL_Rect textRect;
	SDL_Surface* surface;


};