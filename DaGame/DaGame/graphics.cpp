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
	for (SpriteMap::iterator iter = sprite_sheets_.begin();
		iter != sprite_sheets_.end();
		++iter){
		SDL_FreeSurface(iter->second);
	}
	SDL_FreeSurface(screen_);
}

Graphics::SurfaceID Graphics::loadImage(const std::string& file_path){
	//this means that we have NOT loaded in the sprite sheet
	if (sprite_sheets_.count(file_path) == 0){
		//loads it in now...
		sprite_sheets_[file_path] = SDL_LoadBMP(file_path.c_str());
	}
	//if already loaded then just return the sprite sheet
	return sprite_sheets_[file_path];
}

void Graphics::blitSurface(SurfaceID source, SDL_Rect* source_rectangle, SDL_Rect* destination_rectangle){
	SDL_BlitSurface(source, source_rectangle, screen_ , destination_rectangle);
}

void Graphics::clear(){
	// SDL_fillrect( this is our surface that we want to fill 
					//next parameter is the destination rectangle that we want to fill, we pul NULL here because we want it to fill the whole screen
	// next is the color (Uint32) but we will just put 0 for now as we just want it black
	SDL_FillRect(screen_ ,  NULL , 0);
}

void Graphics::flip(){
	SDL_Flip(screen_);
}