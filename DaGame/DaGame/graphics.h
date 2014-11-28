#ifndef GRAPHICS_H_
#define GRAPHICS_H_

struct SDL_Surface;
struct SDL_Rect;

#include<string>
#include<map>


struct Graphics{
	typedef SDL_Surface* SurfaceID;

	SurfaceID loadImage(const std::string& file_path);

	Graphics();
	~Graphics();

	void blitSurface(SurfaceID source, SDL_Rect* source_rectangle, SDL_Rect* destination_rectangle);

	void flip();

private:
	std::map < std::string, SDL_Surface*> sprite_sheets_;
	SDL_Surface* screen_;
};

#endif // GRAPHICS_H_