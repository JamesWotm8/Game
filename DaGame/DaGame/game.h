#ifndef GAME_H_ // checks if the token has been defined earlier
#define GAME_H_	// defines

#include <boost/scoped_ptr.hpp>

struct Sprite;
struct Graphics;

struct Game { // struct is the same as class, but struct's are default to public members while class is private, we want public
	Game();
	~Game();  // deconstructor

	static int kTileSize;
private:
	void eventLoop();
	void update(int elapsed_time_ms);
	void draw(Graphics& graphics);

	boost::scoped_ptr<Sprite> sprite_;
};

#endif // GAME_H_