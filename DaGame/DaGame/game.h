#ifndef GAME_H_ // checks if the token has been defined earlier
#define GAME_H_	// defines

struct SDL_Surface;

struct Game { // struct is the same as class, but struct's are default to public members while class is private, we want public
	Game();
	~Game();  // deconstructor
private:
	void eventLoop();
	void update();
	void draw();

	SDL_Surface* screen_; // declare the screen

};

#endif // GAME_H_