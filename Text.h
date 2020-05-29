#pragma once
#include <SDL_ttf.h>
#include <SDL.h>
#include <string>

class Text
{
public:
	//string 'text' can be changed to score variable which is incremented depending on certain factors
	Text(SDL_Renderer* renderer, const std::string& font_path, int fontSize, const std::string& text, const SDL_Color& colour);

	static int* score;

	void render(int x, int y, SDL_Renderer* renderer);

	static SDL_Texture* loadFont(SDL_Renderer* renderer, const std::string& font_path, int fontSize, const std::string& text, const SDL_Color& colour);

private:
	SDL_Texture* textTexture = nullptr;
	SDL_Rect textRect;
};