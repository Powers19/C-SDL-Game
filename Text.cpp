#include "Text.h"
#include "Window.h"
#include <iostream>

using namespace std;

int* Text::score = 0;

Text::Text(SDL_Renderer* renderer, const std::string& font_path, int fontSize, const std::string& text, const SDL_Color& colour)
{
	textTexture = loadFont(renderer, font_path, fontSize, text, colour);
	SDL_QueryTexture(textTexture, nullptr, nullptr, &textRect.w, &textRect.h);
	//score = 0;
}

void Text::render(int x, int y, SDL_Renderer* renderer)
{
	textRect.x = x;
	textRect.y = y;

	//score = 0;

	SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
}

SDL_Texture* Text::loadFont(SDL_Renderer* renderer, const std::string& font_path, int fontSize, const std::string& text, const SDL_Color& colour)
{
	TTF_Font* font = TTF_OpenFont(font_path.c_str(), fontSize);
	if (!font)
	{
		cout << "Font failed to load";
	}

	auto textSurface = TTF_RenderText_Solid(font, text.c_str(), colour);
	if (!textSurface)
	{
		cout << "Failed to create text surface";
	}

	auto textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	if (!textTexture)
	{
		cout << "Faild to create text texture";
	}

	SDL_FreeSurface(textSurface);
	TTF_CloseFont(font);
	return textTexture;
}