#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <SDL_rect.h>

#include "Timer.h"
#include "Window.h"
#include "Rect.h"

#include "Sprite.h"
#include "Enemy.h"
#include "Text.h"
#include "ScoreCounter.h"



#include <vector>
#include <iostream>
using namespace std;

//set to 60 to ensure constant frame rate 
const int FRAME_RATE = 60;

Mix_Chunk* sound = NULL;
Mix_Music* endMusic = NULL;



//Events function ensures that both window and rect use same pollevents so do not interfere
void pollEvent(Window& window, Sprite& sprite)
{
	SDL_Event event;

	if (SDL_PollEvent(&event))
	{

		window.pollEvent(event);
		sprite.pollEvent(event);
	}
}

float countDown = 30.0f;
bool deadbySport = false;
bool failedExams = false;
bool brainMalfunction = false;
bool badminton = false;
bool seriousInjury = false;
bool fixedGarage = false;
bool outofTime = false;
bool revised = false;
bool parentsFurious = false;
bool fullfilled = false;
bool helpedParents = false;
bool playedGames = false;



//needed to start SDL
int main(int argc, char** argv)
{



	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{

		return 1;
	}

	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		printf("No audio found!\n");
	}
	else
	{
		sound = Mix_LoadWAV("content/GameOver.wav");
		endMusic = Mix_LoadMUS("content/EndMusic.wav");
		

	}


	int lastEnemyPos = 50;
	SDL_Log("GAME STARTED");
	

	//call both window and rect class to initialise - can call multiple iterations of objects here
	Window window("Feargus Powers CGP2015M Game Programming 16654184", 800, 600);
	//player sprite called 
	Sprite sprite(60, 50, 0, 160);





	

	Enemy blue(window, 20, 20, 100, 200, 100, "content/Blue.png");
	Enemy red(window, 20, 20, 100, 120, 100, "content/Red.png");
	Enemy red2(window, 20, 20, 320, 120, 100, "content/Red.png");
	Enemy wood(window, 50, 80, 450, 90, 0, "content/dangerousWood.png");
	Enemy shoe(window, 30, 30, 30, 350, 0, "content/shoe.png");
	Enemy badmintonRacket(window, 70, 70, 500, 350, 0, "content/BadmintonRacket.png");
	Enemy line(window, 80, 50, 670, 170, 0, "content/QuestionMark.png");
	Enemy grass(window, 300, 200, 0, 250, 0, "content/grass.png");
	Enemy grassB(window, 200, 50, 200, 350, 0, "content/grass.png");
	Enemy grassC(window, 200, 200, 400, 250, 0, "content/grass.png");
	Enemy grassD(window, 200, 200, 430, 250, 0, "content/grass.png");
	Enemy pavement(window, 280, 200, 195, 250, 0, "content/Pavement.png");
	Enemy pathToRun(window, 700, 50, -200, 350, 0, "content/Pavement.png");
	Enemy badmintonPath(window, 600, 50, 150, 350, 0, "content/Pavement.png");
	Enemy endPoint(window, 80, 80, 0, 500, 0, "content/Bed.png");
	Enemy garageFixed(window, 20, 20, 580, 120, 0, "content/Red.png");
	Enemy finalChoice(window, 80, 50, 400, 500, 0, "content/QuestionMark.png");
	Enemy computer(window, 30, 40, 310, 530, 0, "content/Computer.png");
	Enemy smileyface(window, 30, 30, 320, 440, 0, "content/Smiley.png");
	Enemy book(window, 50, 50, 620, 250, 0, "content/Book.png");
	Enemy controller(window, 50, 50, 735, 250, 0, "content/GameController.png");

	Text gardenText(Window::renderer, "content/Roboto-BoldCondensed.ttf", 20, "Go in the garden? ", { 255, 255, 255, 255 });
	Text runText(Window::renderer, "content/Roboto-BoldCondensed.ttf", 20, "Go for a run?", { 0, 0, 0, 255 });
	Text badmintonText(Window::renderer, "content/Roboto-BoldCondensed.ttf", 20, "Play Badminton?", { 0, 0, 0, 255 });

	Timer* aTimer;
	
	//create walls for environment 
	Rect wall(window, 0, 70, 400, 1, 255, 0, 0, 255);
	Rect mazeWall(window, 600, 70, 190, 1, 255, 0, 0, 255);
	Rect middleLine(window, 630, 160, 1, 90, 255, 0, 0, 255);
	Rect redBlueLine(window, 110, 160, 520, 1, 255, 0, 0, 255);
	Rect bottomWall(window, 0, 250, 300, 1, 255, 0, 0, 255);
	Rect bottomWall2(window, 630, 250, 1, 200, 255, 0, 0, 255);
	Rect wall2(window, 790, 70, 100, 500, 255, 0, 0, 255);
	Rect wall3(window, 0, 400, 630, 1, 255, 0, 0, 255);
	Rect bottomWall3(window, 0, 570, 790, 1, 255, 0, 0, 255);
	Rect gardenPath(window, 300, 250, 1, 100, 255, 0, 0, 255);
	Rect gardenPath2(window, 400, 250, 1, 100, 255, 0, 0, 255);
	Rect bottomWall4(window, 400, 250, 230, 1, 255, 0, 0, 255);
	Rect cover(window, 200, 40, 800, 600, 0, 0, 0, 255);

	//timer instance called
	aTimer = Timer::Instance();


	//game loop
	while (!window.isClosed())
	{
		aTimer->update();



		//control frame rate
		if (aTimer->DeltaTime() >= (1.0f / FRAME_RATE))
		{
			int displayScore = sprite.getScore();
			int showBrainLevel = sprite.getBrain();
			//start menu functionality
			if (window._isStartMenu == true)
			{

				Text titleText(Window::renderer, "content/TitleFont.ttf", 50, "Quarantine Chaos", { 255, 255, 255, 255 });
				Text continueText(Window::renderer, "content/TitleFont.ttf", 40, "Press space to continue", { 255, 255, 255, 255 });
				Text tagline(Window::renderer, "content/TitleFont.ttf", 20, "Will you embrace the chaos or give in to the isolation boredom?", { 255, 255, 255, 255 });
				Text tagLineb(Window::renderer, "content/TitleFont.ttf", 20, "Get to your bed as you get through the day", { 255, 255, 255, 255 });
				Text instructions(Window::renderer, "content/Roboto-BoldCondensed.ttf", 20, "Arrow keys to move", { 255, 255, 255, 255 });
				Text instructionsB(Window::renderer, "content/Roboto-BoldCondensed.ttf", 20, "1 to play sound, 2 to mute", { 255, 255, 255, 255 });
				Text instructionsC(Window::renderer, "content/Roboto-BoldCondensed.ttf", 20, "F7 to toggle fullscreen", { 255, 255, 255, 255 });
				Text instructionsD(Window::renderer, "content/Roboto-BoldCondensed.ttf", 20, "Escape to exit game", { 255, 255, 255, 255 });

				titleText.render(160, 20, Window::renderer);
				continueText.render(135, 400, Window::renderer);
				tagline.render(32, 200, Window::renderer);
				tagLineb.render(140, 260, Window::renderer);
				instructions.render(580, 470, Window::renderer);
				instructionsB.render(580, 490, Window::renderer);
				instructionsC.render(580, 510, Window::renderer);
				instructionsD.render(580, 530, Window::renderer);

				printf("Frame Rate: %F\n", aTimer->DeltaTime());
				window.update();
				pollEvent(window, sprite);
				window.clear();
				aTimer->Reset();
			}
			if (window._isStartMenu == false)
				//goes to the actual game once player moves away from start menu
			{
				
				//ensures timer counts down from 30
				countDown -= aTimer->DeltaTime();
				if (countDown < 0)
				{
					countDown = 0; //value cannot go lower than 0
					window._isGameOver = true;
					outofTime = true; //ensures player cannot play anymore
				}
				//frame rate shown in console
				printf("Frame Rate: %F\n", aTimer->DeltaTime());
				sprite.brainPower -= aTimer->DeltaTime();
				if (sprite.brainPower < 0)
				{
					sprite.brainPower = 0;
					sprite.playerSpeed = 0;
					Text restText(Window::renderer, "content/Roboto-BoldCondensed.ttf", 30, "Time for a lie down, you have no energy left", { 255, 255, 255, 255 });
					restText.render(90, 480, Window::renderer);
				}






				//the declaration of these objects needs to be inside the loop to ensure that the score value is incremented

				Text text(Window::renderer, "content/Roboto-BoldCondensed.ttf", 20, "Score: ", { 255, 255, 255, 255 });
				Text timerText(Window::renderer, "content/Roboto-BoldCondensed.ttf", 20, "Timer: ", { 255, 255, 255, 255 });
				Text brainLevel(Window::renderer, "content/Roboto-BoldCondensed.ttf", 20, "Brain level:            %", { 255, 255, 255, 255 });
				Text redBlue(Window::renderer, "content/Roboto-BoldCondensed.ttf", 30, "RED OR BLUE?", { 255, 255, 255, 255 });


				ScoreCounter sc(Window::renderer, "content/Roboto-BoldCondensed.ttf", 20, displayScore, { 255, 255, 255, 255 });
				ScoreCounter timer(Window::renderer, "content/Roboto-BoldCondensed.ttf", 20, countDown, { 255, 255, 255, 255 });
				ScoreCounter brain(Window::renderer, "content/Roboto-BoldCondensed.ttf", 20, showBrainLevel, { 255, 255, 255, 255 });

				window.update();
				pollEvent(window, sprite);//calls function to allows square to move and mouse and button events




				

				blue.draw();
				red.draw();




				//draw all rectangles for the map
				SDL_SetRenderDrawColor(Window::renderer, 255, 0, 0, 255);
				redBlueLine.draw();
				wall.draw();
				bottomWall.draw();
				bottomWall2.draw();
				wall2.draw();
				wall3.draw();
				bottomWall3.draw();
				mazeWall.draw();
				bottomWall4.draw();
				line.draw();
				grass.draw();
				grassB.draw();
				grassC.draw();
				grassD.draw();
				pavement.draw();
				pathToRun.draw();
				badmintonPath.draw();
				endPoint.draw();
				finalChoice.draw();


				//collision function called for building
				sprite.collision(wall);
				sprite.collision(redBlueLine);
				sprite.collision(bottomWall);
				sprite.collision(bottomWall2);
				sprite.collision(wall2);
				sprite.collision(wall3);
				sprite.collision(bottomWall3);
				sprite.collision(mazeWall);
				sprite.collision(middleLine);

				//more collision detection for side and top of screen so player doesn't go too far
				if ((sprite.xDst < 0) || (sprite.xDst + sprite._w > window._w))
				{
					sprite.xDst += 2;
				}
				if ((sprite.yDst < 0) || (sprite.yDst + sprite._h > window._h))
				{
					sprite.yDst += 2;
				}

				//functionality for when player interacts with game objects
				if (sprite.gameInteractions(blue))
				{
					Text redText(Window::renderer, "content/Roboto-BoldCondensed.ttf", 20, "Hmm you chose blue", { 255, 255, 255, 255 });
					redText.render(200, 100, Window::renderer);
				}

				if (sprite.gameInteractions(red))
				{
					Text redText(Window::renderer, "content/Roboto-BoldCondensed.ttf", 20, "Hmm you chose red", { 255, 255, 255, 255 });
					redText.render(200, 100, Window::renderer);

				}
				if (sprite.gameInteractions(red2))
				{
					middleLine.draw();
					garageFixed.draw();

				}
				if (sprite.gameInteractions(line))
				{
					Text choiceText(Window::renderer, "content/Roboto-BoldCondensed.ttf", 20, "Study for exams or play new games?", { 255, 255, 255, 255 });
					choiceText.render(500, 200, Window::renderer);

					book.draw();
					controller.draw();

				}
				if (sprite.xDst > 100)
				{
					Text activityText(Window::renderer, "content/Roboto-BoldCondensed.ttf", 20, "Fix the falling parts in the shed", { 255, 255, 255, 255 });
					activityText.render(450, 40, Window::renderer);
					red2.draw();
					wood.draw();
					wood.move();
					gardenPath.draw();
					gardenPath2.draw();


				}
				if ((sprite.yDst > 170) && (sprite.xDst > 100))
				{

					gardenText.render(200, 200, Window::renderer);
					runText.render(30, 300, Window::renderer);
					shoe.draw();
					badmintonText.render(459, 300, Window::renderer);
					badmintonRacket.draw();
				}
				if (sprite.gameInteractions(shoe))
				{

					
					deadbySport = true;
					window._isGameOver = true;
				}
				//will lose energy playing badminton
				if (sprite.gameInteractions(badmintonRacket))
				{
					SDL_Delay(100);
					Text choiceText(Window::renderer, "content/Roboto-BoldCondensed.ttf", 20, "Very tiring", { 255, 255, 255, 255 });
					choiceText.render(10, 50, Window::renderer);
					sprite.update();
					badminton = true;
				}
				if (sprite.gameInteractions(finalChoice))
				{
					Text finalChoiceText(Window::renderer, "content/Roboto-BoldCondensed.ttf", 20, "One final choice, if you do this then you may escape the chaos in one piece", { 255, 255, 255, 255 });
					finalChoiceText.render(0, 390, Window::renderer);
					Text finalChoiceB(Window::renderer, "content/Roboto-BoldCondensed.ttf", 20, "Help your parents with technology or focus on yourself?", { 255, 255, 255, 255 });
					finalChoiceB.render(150, 420, Window::renderer);
					computer.draw();
					smileyface.draw();
				}
				if (sprite.gameInteractions(book) && (!badminton) && (fixedGarage))
				{
					sprite.brainPower -= 1;
					revised = true;
					Text choiceText(Window::renderer, "content/Roboto-BoldCondensed.ttf", 20, "You revised for a while, welcome after hard manual work", { 255, 255, 255, 255 });
					choiceText.render(10, 50, Window::renderer);
				}
				if (sprite.gameInteractions(book) && (badminton))
				{
					sprite.brainPower -= 0.4;
					revised = true;
					Text choiceText(Window::renderer, "content/Roboto-BoldCondensed.ttf", 20, "Revision after sport, is that the perfect formula?", { 255, 255, 255, 255 });
					choiceText.render(10, 70, Window::renderer);

				}
				if (sprite.gameInteractions(book) && (!badminton) && (!fixedGarage))
				{
					sprite.brainPower -= 1;
					Text choiceText(Window::renderer, "content/Roboto-BoldCondensed.ttf", 20, "After revising, you think you may have reached your peak, you feel enlightened, is this it?", { 255, 255, 255, 255 });
					choiceText.render(10, 70, Window::renderer);
					revised = true;
				}
				
				if (sprite.gameInteractions(controller) && (badminton))
				{

					failedExams = true;
					window._isGameOver = true;
				}

				if (sprite.gameInteractions(wood))
				{

					seriousInjury = true;
					window._isGameOver = true;
				}
				if (sprite.gameInteractions(garageFixed))
				{
					Text choiceText(Window::renderer, "content/Roboto-BoldCondensed.ttf", 20, "After avoiding bad injury and fixing the garage, you feel good but lost some energy", { 255, 255, 255, 255 });
					choiceText.render(30, 200, Window::renderer);
					sprite.playerSpeed = 2;
					sprite.brainPower = 90;
					fixedGarage = true;
				}
				if (sprite.gameInteractions(controller))
				{
					playedGames = true;
					Text relaxText(Window::renderer, "content/Roboto-BoldCondensed.ttf", 20, "Relaxation has helped you lots, you feel good", { 255, 255, 255, 255 });
					relaxText.render(30, 150, Window::renderer);
				}
				if (sprite.gameInteractions(computer) && (fixedGarage) && (playedGames))
				{
					Mix_PlayMusic(endMusic, -1);
					Text endingA(Window::renderer, "content/Roboto-BoldCondensed.ttf", 20, "Your family is pleased you have helped around the house today, how do you feel?", { 255, 255, 255, 255 });
					endingA.render(30, 150, Window::renderer);
					helpedParents = true;
				}
				if (sprite.gameInteractions(computer) && (!fixedGarage) && (playedGames))
				{
					Mix_PlayMusic(endMusic, -1);
					Text endingB(Window::renderer, "content/Roboto-BoldCondensed.ttf", 20, "The garage is still broken, yet family pleased you helped for once", { 255, 255, 255, 255 });
					endingB.render(30, 150, Window::renderer);
					helpedParents = true;
				}
				if (sprite.gameInteractions(computer) && (revised))
				{
					Mix_PlayMusic(endMusic, -1);
					Text endingB(Window::renderer, "content/Roboto-BoldCondensed.ttf", 20, "The garage is still broken, yet family pleased you helped for once", { 255, 255, 255, 255 });
					endingB.render(30, 150, Window::renderer);
					helpedParents = true;
				}
				if (sprite.gameInteractions(smileyface) && (playedGames) && (fixedGarage))
				{
					Mix_PlayMusic(endMusic, -1);
					fullfilled = true;
					Text endingC(Window::renderer, "content/Roboto-BoldCondensed.ttf", 20, "Family shout at you, does it matter?", { 255, 255, 255, 255 });
					endingC.render(30, 150, Window::renderer);
				}
				if (sprite.gameInteractions(smileyface) && (!revised) && (!fixedGarage) && (playedGames))
				{
					fullfilled = true;

					parentsFurious = true;
					window._isGameOver = true;
				}
				if (sprite.gameInteractions(smileyface) && (revised))
				{
					Mix_PlayMusic(endMusic, -1);
					fullfilled = true;
					sprite.brainPower = 100;
					Text endingC(Window::renderer, "content/Roboto-BoldCondensed.ttf", 20, "You have reached a good state of mind, although your family are not happy.", { 255, 255, 255, 255 });
					endingC.render(30, 150, Window::renderer);
				}
				if (sprite.gameInteractions(smileyface) && (fixedGarage) && (revised))
				{
					Mix_PlayMusic(endMusic, -1);
					fullfilled = true;
					Text endingC(Window::renderer, "content/Roboto-BoldCondensed.ttf", 20, "You have been productive today, will it matter", { 255, 255, 255, 255 });
					endingC.render(30, 150, Window::renderer);
				}

				//UI text rendered
				
				timerText.render(700, 20, Window::renderer);
				brainLevel.render(0, 20, Window::renderer);

				//ensures red or blue text only shown for 3 seconds 
				if (countDown > 27)
				{
					redBlue.render(250, 20, Window::renderer);
				}

				sprite.draw();

				
				timer.render(750, 20, Window::renderer);
				brain.render(110, 20, Window::renderer);

				window.clear(); //clears to screen

				aTimer->Reset();

			}
			//all possible endings - not deaths 
			if (sprite.gameInteractions(endPoint) && (revised) && (!fullfilled) && (!badminton) && (!fixedGarage) && (!helpedParents) && (!playedGames))
			{
				Mix_PauseMusic();
				window.clear();
				window._isGameOver = false; // ensures doesn't go the game over menu
				Text haverevisedText(Window::renderer, "content/TitleFont.ttf", 15, "Is that it, just revision, is that how you want to spend your lockdown", { 255, 255, 255, 255 });
				haverevisedText.render(50, 200, Window::renderer);
				window.clear();
				aTimer->Reset();
			}
			if (sprite.gameInteractions(endPoint) && (!revised) && (!badminton) && (!fixedGarage) && (!fullfilled) && (!helpedParents) && (!playedGames))
			{
				window.clear();
				window._isGameOver = false;
				Text boringText(Window::renderer, "content/TitleFont.ttf", 25, "Is that it, you have done nothing today. Is that fullfilling", { 255, 255, 255, 255 });
				boringText.render(50, 200, Window::renderer);
				window.clear();
				aTimer->Reset();
			}
			if (sprite.gameInteractions(endPoint) && (revised) && (badminton) && (!fixedGarage) && (!fullfilled) && (!helpedParents) && (!playedGames))
			{
				window.clear();
				window._isGameOver = false;
				Text twotasksText(Window::renderer, "content/TitleFont.ttf", 25, "Revised and a sport, well done, is that good?", { 255, 255, 255, 255 });
				twotasksText.render(50, 200, Window::renderer);
				window.clear();
				aTimer->Reset();
			}
			if (sprite.gameInteractions(endPoint) && (revised) && (badminton) && (fixedGarage) && (!fullfilled) && (!helpedParents) && (!playedGames))
			{
				window.clear();
				window._isGameOver = false;
				Text threetasksText(Window::renderer, "content/TitleFont.ttf", 25, "Revised, played sport and fixed the garage, well done, is that good?", { 255, 255, 255, 255 });
				threetasksText.render(50, 200, Window::renderer);
				window.clear();
				aTimer->Reset();
			}
			if (sprite.gameInteractions(endPoint) && (revised) && (fixedGarage) && (helpedParents) && (!badminton) && (!playedGames) && (!fullfilled))
			{
				window.clear();
				window._isGameOver = false;
				Text threetasksText(Window::renderer, "content/TitleFont.ttf", 15, "Revised, helped your parents and fixed the garage, well done, is that good?", { 255, 255, 255, 255 });
				threetasksText.render(50, 200, Window::renderer);
				window.clear();
				aTimer->Reset();
			}
			if (sprite.gameInteractions(endPoint) && (fixedGarage) && (playedGames) && (fullfilled) && (!badminton) && (!revised) && (!helpedParents))
			{
				window.clear();
				window._isGameOver = false;
				Text happinessText(Window::renderer, "content/TitleFont.ttf", 15, "You fixed the garage, and found  time for yourself, do you feel good?", { 255, 255, 255, 255 });
				happinessText.render(70, 200, Window::renderer);
				window.clear();
				aTimer->Reset();
			}

			if (sprite.gameInteractions(endPoint) && (fixedGarage) && (!revised) && (!badminton) && (!fullfilled) && (!helpedParents) && (!playedGames))
			{
				window.clear();
				window._isGameOver = false;
				Text fixerText(Window::renderer, "content/TitleFont.ttf", 25, "You fixed the garage, well done, is that good?", { 255, 255, 255, 255 });
				fixerText.render(50, 200, Window::renderer);
				window.clear();
				aTimer->Reset();
			}
			if (sprite.gameInteractions(endPoint) && (badminton) && (revised) && (helpedParents) && (!fixedGarage) && (!fullfilled) && (!playedGames))
			{
				window.clear();
				window._isGameOver = false;
				Text fixerText(Window::renderer, "content/TitleFont.ttf", 25, "Sport, revision and help, does that count as productive?", { 255, 255, 255, 255 });
				fixerText.render(50, 200, Window::renderer);
				window.clear();
				aTimer->Reset();
			}
			if (sprite.gameInteractions(endPoint) && (badminton) && (revised) && (fullfilled) && (!helpedParents) && (!fixedGarage) && (!playedGames))
			{
				window.clear();
				window._isGameOver = false;;
				Text fixerText(Window::renderer, "content/TitleFont.ttf", 25, "Sport, revision and personal satisfaction, does that help?", { 255, 255, 255, 255 });
				fixerText.render(50, 200, Window::renderer);
				window.clear();
				aTimer->Reset();
			}
			if (sprite.gameInteractions(endPoint) && (playedGames) && (helpedParents) && (!fullfilled) && (!revised) && (!badminton) && (!fixedGarage))
			{

				window.clear();
				window._isGameOver = false;
				Text fixerText(Window::renderer, "content/TitleFont.ttf", 20, "You have relaxed and helped your parents, is that fullfilling?", { 255, 255, 255, 255 });
				fixerText.render(50, 200, Window::renderer);
				window.clear();
				aTimer->Reset();
			}
			if (sprite.gameInteractions(endPoint) && (revised) && (helpedParents) && (!badminton) && (!fixedGarage) && (!fullfilled) && (!playedGames))
			{

				window.clear();
				window._isGameOver = false;
				Text fixerText(Window::renderer, "content/TitleFont.ttf", 15, "You have revised while finding brain power left to help your parents, does that feel good", { 255, 255, 255, 255 });
				fixerText.render(0, 200, Window::renderer);
				window.clear();
				aTimer->Reset();
			}
			if (sprite.gameInteractions(endPoint) && (badminton) && (revised) && (helpedParents) && (fullfilled) && (!playedGames) && (!fixedGarage))
			{
				window.clear();
				window._isGameOver = false;
				Text fixerText(Window::renderer, "content/TitleFont.ttf", 15, "You have revised while finding brain power left to help your parents and play sport, does that feel good", { 255, 255, 255, 255 });
				fixerText.render(0, 200, Window::renderer);
				window.clear();
				aTimer->Reset();
			}
			if (sprite.gameInteractions(endPoint) && (revised) && (fullfilled) && (!fixedGarage) && (!badminton) && (!playedGames) && (!helpedParents))
			{
				window.clear();
				window._isGameOver = false;
				Text fixerText(Window::renderer, "content/TitleFont.ttf", 20, "You have revised and found time for yourself, does it feel good?", { 255, 255, 255, 255 });
				fixerText.render(50, 200, Window::renderer);
				window.clear();
				aTimer->Reset();
			}
			if (sprite.gameInteractions(endPoint) && (fixedGarage) && (playedGames) && (helpedParents) && (!badminton) && (!revised) && (!fullfilled))
			{
				window.clear();
				window._isGameOver = false;

				Text fixerText(Window::renderer, "content/TitleFont.ttf", 15, "You have relaxed while finding brain power left to help your parents, does that feel good", { 255, 255, 255, 255 });
				fixerText.render(0, 200, Window::renderer);
				window.clear();
				aTimer->Reset();
			}


			//all logic for deaths
			//when game ends, game over is shown along with message depending on how you failed 
			if (window._isGameOver == true)
			{

				if (deadbySport)
				{
					window.gameOverMenu();

					Text deathText(Window::renderer, "content/Roboto-BoldCondensed.ttf", 17, "Sadly, due to the lack of recent exercise, your muscles are in agony, your day is over", { 255, 255, 255, 255 });
					deathText.render(70, 200, Window::renderer);


					window.update();
					pollEvent(window, sprite);
					window.clear();
					aTimer->Reset();
				}
				if (failedExams)
				{
					window.gameOverMenu();
					Text relaxText(Window::renderer, "content/Roboto-BoldCondensed.ttf", 20, "You are now very relaxed. Too relaxed - you have failed your exams!", { 255, 255, 255, 255 });
					relaxText.render(100, 50, Window::renderer);
					window.update();
					pollEvent(window, sprite);
					window.clear();
					aTimer->Reset();
				}
				if (brainMalfunction)
				{
					window.gameOverMenu();
					Text endText(Window::renderer, "content/Roboto-BoldCondensed.ttf", 17, "After lots of badminton you try and do some work, this backfires as your brain fails to cope with what you are reading", { 255, 255, 255, 255 });
					endText.render(30, 200, Window::renderer);
					window.update();
					pollEvent(window, sprite);
					window.clear();
					aTimer->Reset();
				}
				if (seriousInjury)
				{

					

					window.gameOverMenu();
					Text endText(Window::renderer, "content/Roboto-BoldCondensed.ttf", 20, "Ouch, you sustained a serious injury fixing the garage!", { 255, 255, 255, 255 });
					endText.render(200, 200, Window::renderer);
					window.update();
					pollEvent(window, sprite);
					window.clear();
					aTimer->Reset();
				}
				if (outofTime)
				{
					window.gameOverMenu();
					Text outofTimeText(Window::renderer, "content/Roboto-BoldCondensed.ttf", 20, "You have ran out of time, was your day a success, or did you dive further into quarantine chaos", { 255, 255, 255, 255 });
					outofTimeText.render(40, 200, Window::renderer);

					window.update();
					pollEvent(window, sprite);
					window.clear();
					aTimer->Reset();
				}
				if (parentsFurious)
				{
					window.gameOverMenu();
					Text outofTimeText(Window::renderer, "content/Roboto-BoldCondensed.ttf", 20, "Your parents are furious at your actions, they turned off the wifi, you fail your exams", { 255, 255, 255, 255 });
					outofTimeText.render(50, 200, Window::renderer);

					window.update();
					pollEvent(window, sprite);
					window.clear();
					aTimer->Reset();
				}


			}

		}





	}

	Mix_Quit();
	Timer::Release();
	aTimer = NULL;

	return 0;






}