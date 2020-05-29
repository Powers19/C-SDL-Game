#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
class Score
{
public:
	Score();
	Score(int x, int y);
	~Score();

	void increment() { this->_score += 1; }

	int _score;

	int getScore() { return _score; }

	void draw(SDL_Renderer* renderer);

private:
	SDL_Texture* _texture;
	SDL_Surface* textsurface;
	TTF_Font* _font;

	//int _score;
	int _x, _y;


};

