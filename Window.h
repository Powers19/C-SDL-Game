#pragma once

#include <string>
#include <SDL.h>
using namespace std;

class Window
{
public:
	Window(const string& title, int w, int h);//, bool fullScreen);
	~Window();

	void pollEvent(SDL_Event& event);
	void clear() const;
	void update();

	void startMenu();
	void gameOverMenu();


public:

	//bool checkCollision(SDL_Rect a, SDL_Rect b);

	static SDL_Renderer* renderer;

	inline bool isClosed() const { return _closed; }
	inline bool startMenu() const { return _isStartMenu; }

	bool _isStartMenu;
	bool _isGameOver;
	bool isPaused;
	int R, G, B;

	int _w = 800;
	int _h = 600;

private:
	bool init();


	string _title;
	//int _w = 800;
	//int _h = 600;

	bool _closed = false;

	bool _fullScreen;

	//sets window pointer to nothing
	SDL_Window* window = nullptr;

	//allows inheritance, for the rect class to use the same renderer as the window


};

