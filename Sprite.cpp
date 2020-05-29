#include "Sprite.h"
#include "Window.h"
#include "Enemy.h"
#include "Text.h"
#include "Timer.h"
#include "ScoreCounter.h"



#include <SDL_mixer.h>
#include "SDL_Image.h"	
#include <iostream>

//background music and sound affects initialised
Mix_Music* SOUND_backgroundMusic = NULL;
//Mix_Music* endMusic = NULL;

ScoreCounter sc;





Sprite::Sprite(int w, int h, int x, int y) :
	_w(w), _h(h), xDst(x), yDst(y)
{
	SDL_Surface* surface = IMG_Load(_image_path_idle.c_str());
	if (!surface)
	{
		cout << "Failed to create surface";
	}

	SDL_Surface* Walkingsurface = IMG_Load(_image_path_moving.c_str());
	if (!Walkingsurface)
	{
		cout << "Failed to create surface";
	}

	/*mPosx = 0;
	mPosy = 0;*/

	isMoving == false;


	playerSpeed = 5;
	brainPower = 100.0f;
	playerScore = 0;

	//collider.w = _w;
	//collider.h = _h;

	texture = SDL_CreateTextureFromSurface(Window::renderer, surface);
	if (!texture)
	{
		cout << "Failed to create texture";
	}

	walkingTexture = SDL_CreateTextureFromSurface(Window::renderer, Walkingsurface);
	if (!walkingTexture)
	{
		cout << "Failed to create texture";
	}

	SDL_FreeSurface(surface);
	SDL_FreeSurface(Walkingsurface);

	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		printf("No audio found!\n");
	}
	else
	{
		SOUND_backgroundMusic = Mix_LoadMUS("content/game music.wav");
		//endMusic = Mix_LoadMUS("content/EndMusic.wav");

	}

}

Sprite::~Sprite()
{
	SDL_DestroyTexture(texture);
	SDL_DestroyTexture(walkingTexture);
	Mix_Quit();
}

void Sprite::draw() const
{
	Timer* timer;
	timer = Timer::Instance();
	//ensures the sprite can move
	Uint32 ticks = SDL_GetTicks();
	Uint32 sprite = (ticks / 100) % 8;
	SDL_Rect srcRect = { sprite * 32, 0, 22, 32 };
	SDL_Rect rect = { xDst, yDst, 60, _h };






	//if the texture has loaded correctly and the player is moving then appropriate animation is loaded
	if ((walkingTexture) && (isMoving))
	{

		SDL_RenderCopyEx(Window::renderer, walkingTexture, &srcRect, &rect, angle, center, flip);

	}
	else
	{
		SDL_RenderCopyEx(Window::renderer, texture, NULL, &rect, angle, center, flip);


	}



}

void Sprite::pollEvent(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_LEFT:
			left = true;
			//_x -= playerSpeed;
			isMoving = true;
			//ensures animation is facing left 
			flip = SDL_FLIP_HORIZONTAL;
			break;
		case SDLK_RIGHT:
			right = true;
			//_x += playerSpeed;
			isMoving = true;
			//no flip needed because set to default
			flip = SDL_FLIP_NONE;
			playerScore += 1;
			break;
		case SDLK_UP:
			up = true;
			//_y -= playerSpeed;
			isMoving = true;

			break;
		case SDLK_DOWN:
			down = true;

			isMoving = true;
			break;

		case SDLK_SPACE:

			break;

		case SDLK_1:
			Mix_PlayMusic(SOUND_backgroundMusic, -1);
			break;
			//I.AddItem(0, 1, 1);
		case SDLK_2:
			Mix_PauseMusic();
			break;
		}


	}
	if (event.type == SDL_KEYUP)
	{
		isMoving = false;
		if (event.key.keysym.sym == SDLK_UP)
		{
			up = false;
		}
		if (event.key.keysym.sym == SDLK_DOWN)
		{
			down = false;
		}
		if (event.key.keysym.sym == SDLK_LEFT)
		{
			left = false;
		}
		if (event.key.keysym.sym == SDLK_RIGHT)
		{
			right = false;
		}
	}
	if (up == true)
	{
		yDst -= playerSpeed;
	}
	if (down == true)
	{
		yDst += playerSpeed;
	}
	if (left == true)
	{
		xDst -= playerSpeed;
	}
	if (right == true)
	{
		xDst += playerSpeed;
	}
}

void Sprite::update()
{

	playerSpeed = 2;
}




bool Sprite::collision(Rect& s)
{
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = s._x;
	rightA = s._x + s._w;
	topA = s._y;
	bottomA = s._y + s._h;

	//Calculate the sides of rect B
	leftB = xDst;
	rightB = xDst + _w;
	topB = yDst;
	bottomB = yDst + _h;

	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}


	xDst += playerSpeed;
	yDst -= playerSpeed;
	return true;




}

bool Sprite::gameInteractions(Enemy& e)
{
	if (xDst + _w < e._x || xDst> e._x + e._w ||
		yDst + _h < e._y || yDst > e._y + e._h)
	{
		//printf("no collision");
		return false;
	}



	return true;


}


