#include "game.h"
#include "SDL.h"
#include <iostream>
#include "graphics.h"
#include "player.h"
#include "input.h"

namespace{
	const int fPS = 60;
}

int Game::kTileSize = 32;

Game::Game(){
	SDL_Init(SDL_INIT_EVERYTHING); // initiate everything in SDL header
	SDL_ShowCursor(SDL_DISABLE);
	eventLoop(); // the infinite game loop
}

Game::~Game(){
	SDL_Quit(); // restore all the resources that SDL was using to the original state
}

void Game::eventLoop() {
	Graphics graphics; // initializes the graphics class, then at the end deconstructs.
	Input input; // include the input class
	SDL_Event event;

	player_.reset(new Player(graphics, 320, 240));



	bool running = true;
	int last_update_time = SDL_GetTicks();
	while (running) {  // this loop lasts 1/60th of a second which is the same as 1000/60ths ms
		const int start_time_ms = SDL_GetTicks(); // because it takes time for the whole loop to go through, we need to take into account the time it takes and take it away from the delay.
		input.beginNewFrame(); // clear all maps
		while (SDL_PollEvent(&event)){
			switch (event.type){
			case SDL_KEYDOWN:
				input.keyDownEvent(event); // instead of the if loop we used before, we can simply pass the event(the key) through to the input class
				break; // break while loop
			case SDL_KEYUP:
				input.keyUpEvent(event);
				break;
			default:
				break;
			}
		}

		if (input.wasKeyPressed(SDLK_ESCAPE)){ // checks if escape was pressed, if so.. running = false and terminates program
			running = false;
		}
		
		//player horizontal movement
		if (input.isKeyHeld(SDLK_LEFT) && input.isKeyHeld(SDLK_RIGHT)){
			//here is where we stop moving because both are pressed
			player_->stopMoving();
		}else if(input.isKeyHeld(SDLK_LEFT)){
			player_->startMovingLeft(); // moving left
		}else if(input.isKeyHeld(SDLK_RIGHT)){
			player_->startMovingRight(); // moving right
		}else {
			player_->stopMoving(); // else neither of the above are correct, stop moving.
		}

		//here we have player jump
		if (input.wasKeyPressed(SDLK_z)){
			player_->startJump();
		}else if (input.wasKeyReleased(SDLK_z)){
			player_->stopJump();
		}

		const int current_time_ms = SDL_GetTicks();
		update(current_time_ms - last_update_time);
		last_update_time = current_time_ms;


		draw(graphics);
		const int elapsed_time_ms = SDL_GetTicks() - start_time_ms; // end of the loop time - start of the loop time = elapsed time

		SDL_Delay(1000/*ms*/ / fPS /* - elapsed_time_ms commented out because currently not working*/);
	}
}

void Game::update(int elapsed_time_ms){
	player_->update(elapsed_time_ms);
}

void Game::draw(Graphics& graphics){
	graphics.clear();
	player_->draw(graphics);
	graphics.flip(); // draw(). draw everything, background and stuff
}