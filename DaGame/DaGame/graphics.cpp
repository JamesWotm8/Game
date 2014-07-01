#include "graphics.h" // graphics class for the sprites. creates the screen in this class
#include "SDL.h"

namespace{
	const int sCREENWIDTH = 480; // moved over screen parameters to graphics class instead of in game
	const int sCREENHEIGHT = 640;
	const int bITSPERPIXEL = 32;
}

Graphics::Graphics(){
	screen_ = SDL_SetVideoMode(sCREENHEIGHT, sCREENWIDTH, bITSPERPIXEL, SDL_RESIZABLE);
}

Graphics::~Graphics(){
	SDL_FreeSurface(screen_);
}

void Graphics::blitSurface(SDL_Surface* source, SDL_Rect* source_rectangle, SDL_Rect* destination_rectangle){
	SDL_BlitSurface(source, source_rectangle, screen_ , destination_rectangle);
}

void Graphics::flip(){
	SDL_Flip(screen_);
}