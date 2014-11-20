#include "game.h"
#include "SDL.h"
#include <iostream>
#include "graphics.h"
#include "animated_sprite.h"

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
	SDL_Event event;

	sprite_.reset(new AnimatedSprite("Images/MyChar.bmp", 0, 0, kTileSize, kTileSize, 15, 3));

	bool running = true;
	int last_update_time = SDL_GetTicks();
	while (running) {  // this loop lasts 1/60th of a second which is the same as 1000/60ths ms
		const int start_time_ms = SDL_GetTicks(); // because it takes time for the whole loop to go through, we need to take into account the time it takes and take it away from the delay.
		while (SDL_PollEvent(&event)){
			switch (event.type){
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE){ // when esc is pressed, stop running 
					running = false;
				}
				break; // break while loop
			default:
				break;
			}
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
	sprite_->update(elapsed_time_ms);
}

void Game::draw(Graphics& graphics){
	sprite_->draw(graphics, 320, 240);
	graphics.flip(); // draw(). draw everything, background and stuff
}