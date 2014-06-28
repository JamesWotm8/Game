#include "game.h"
#include "SDL.h"
#include <iostream>

namespace{
	const int sCREENWIDTH = 480;
	const int sCREENHEIGHT = 640;
	const int bITSPERPIXEL = 32;
	const int fPS = 60;
}

Game::Game(){
	SDL_Init(SDL_INIT_EVERYTHING); // initiate everything in SDL header
	SDL_ShowCursor(SDL_DISABLE);
	screen_ = SDL_SetVideoMode(sCREENHEIGHT, sCREENWIDTH, bITSPERPIXEL, SDL_RESIZABLE);
	eventLoop(); // the infinite game loop
}

Game::~Game(){
	SDL_FreeSurface(screen_); // free the screen 
	SDL_Quit(); // restore all the resources that SDL was using to the original state
}

void Game::eventLoop() {
	SDL_Event event;

	bool running = true;
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

		update();
		draw();
		const int elapsed_time_ms = SDL_GetTicks() - start_time_ms; // end of the loop time - start of the loop time = elapsed time
		std::cout << "hey" + elapsed_time_ms;
		SDL_Delay(1000/*ms*/ / fPS /* - elapsed_time_ms commented out because currently not working*/);
	}

	update();
	draw();
}

void Game::update(){
	// update() . move the player move projectiles check collisions
}

void Game::draw(){
	// draw(). draw everything, background and stuff
}