#include "Rect.h"
#include "Window.h"
#include "Score.h"
#include "Text.h"
#include <SDL_image.h>
#include <SDL_ttf.h>

using namespace std;
#include <iostream>

SDL_Renderer* Window::renderer = nullptr;

Window::Window(const string& title, int w, int h) ://, bool fullScreen) :
	_title(title), _w(w), _h(h) //_fullScreen(fullScreen)
{
	/*if (!init())
	{
		_closed = true;
	}*/

	//opposite of init means that it will not run therefore it is true
	_closed = !init();
	_isStartMenu = true;
	_isGameOver = false;
	isPaused = false;
	//_fullScreen = SDL_WINDOW_BORDERLESS;
}

Window::~Window()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();

}

bool Window::init()
{
	//Colour settings
	R = 0;
	G = 0;
	B = 0;

	//_fullScreen = false;


	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		cout << "SDL initialisation failed";
		return 0;
	}

	if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		cout << "Failed to start SDL image";
		return 0;
	}

	if (TTF_Init() == -1)
	{
		cout << "Failed to start text";
		return 0;
	}

	window = SDL_CreateWindow(_title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _w, _h, 0);

	if (window == nullptr)
	{
		cout << "Failed to create a window";
		return 0;
	}


	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == nullptr)
	{
		cout << "renderer failed";
		return 0;
	}

	return true;
}



void Window::update()
{
	//fullscreen toggle
	if (_fullScreen)
	{
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

	}
	if (!_fullScreen)
	{
		SDL_SetWindowFullscreen(window, 0);
	}
}

void Window::pollEvent(SDL_Event& event)
{
	/*const Uint8* keystates = SDL_GetKeyboardState(NULL);
	if (keystates[SDL_SCANCODE_F7]) _fullScreen = !_fullScreen;*/
	switch (event.type)
	{
	case SDL_QUIT:
		_closed = true;
		break;

	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
			//closes program when escape pressed
		case SDLK_ESCAPE:
			_closed = true;
			break;
			//fullscreen functionality
		case SDLK_F7:
			_fullScreen = !_fullScreen;
			break;
		case SDLK_SPACE:
			_isStartMenu = false;
			break;
		case SDLK_p:
			isPaused = true;
			break;
		}

		//shows coordinates of mouse
	//case SDL_MOUSEMOTION:
	//	cout << "mouse coordinates: " << event.motion.x << "," << event.motion.y << '\n';
	//	break;
	//	//mouse clicked
	//case SDL_MOUSEBUTTONDOWN:
	//	cout << "You clicked the mouse";
	//	break;

	default:
		break;
	}
}

void Window::clear() const
{
	//sets colour, clears colour onto screen then present on screen.
	//_isStartMenu == false;
	SDL_RenderPresent(renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);




}

void Window::startMenu()
{
	//_isStartMenu = true;
	SDL_RenderPresent(renderer);
	SDL_SetRenderDrawColor(renderer, R, G, B, 255);
	SDL_RenderClear(renderer);

}

void Window::gameOverMenu()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);


	Text gameOverText(Window::renderer, "content/TitleFont.ttf", 100, "GAME OVER", { 255, 0, 0, 255 });
	gameOverText.render(120, 240, Window::renderer);
}


