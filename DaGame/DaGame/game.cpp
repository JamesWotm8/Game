#include "game.h"
#include "SDL.h"

Game::Game(){
	SDL_Init(SDL_INIT_EVERYTHING); // initiate everything in SDL header
	eventLoop(); // the infinite game loop
}

Game::~Game(){
	SDL_Quit(); // restore all the resources that SDL was using to the original state
}

void Game::eventLoop() {
	bool running = true;
	while (running) {
		// this loop lasts 1/60th of a second which is the same as 1000/60ths ms
		SDL_Delay(1000/*ms*/ / 60/*fps*/ /*ms*/);
	}
	// while (running) ~. 60 Hz  ((JUST FINISHED))
	// handle input. 
	//
	// update() . move the player move projectiles check collisions
	// draw(). draw everything, background and stuff
}