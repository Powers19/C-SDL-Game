#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Window.h"
#include "Rect.h"
#include "Enemy.h"
#include <string>

class Sprite
{
public:
	Sprite(int w, int h, int x, int y);
	~Sprite();

	void draw() const;
	void pollEvent(SDL_Event& event);
	void update();
	
	
	//use of reference ensures that copy of sprite made, as texture is destroyed to save memory
	bool collision(Rect& s);
	bool gameInteractions(Enemy& e);
	

	int playerScore;
	int getScore() { return playerScore; }

	
	float playerSpeed;
	//shown as percentage on screen - will depleet depending on activities 
	float brainPower;
	int getBrain() { return brainPower; }

	int frameWidthPixels, frameHeightPixels;
	int textureWidth, textureHeight;

	int _w, _h;
	int _x, _y;
	float yDst = 0.0f;
	float xDst = 0.0f;

	float velX = 0;
	float velY = 0;



private:





	//allows change between the sprite sheet frames when the player is moving to the idle sprite
	const std::string& _image_path_moving = "content/PlayerAnimationMain.png";
	const std::string& _image_path_idle = "content/PlayerSpriteMain.png";

	

	//if player is moving then set to true - used for help with animation
	bool isMoving;
	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;



	double angle = 0.0;

	SDL_Texture* texture = nullptr;
	SDL_Texture* walkingTexture = nullptr;
	SDL_Point* center = NULL;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	SDL_Rect spriteRect;


};