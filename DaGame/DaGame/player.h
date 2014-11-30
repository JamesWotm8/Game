#ifndef PLAYER_H_
#define PLAYER_H_

#include <boost/shared_ptr.hpp>
#include "sprite.h"
#include <map>

struct Graphics;

struct Player {
	Player(Graphics& graphics,int x, int y);

	void update(int elapsed_time_ms);
	void draw(Graphics& graphics);

	void startMovingLeft();
	void startMovingRight();
	void stopMoving();

private:
	//types of motion
	enum MotionType{
		STANDING,
		WALKING,
	};

	//which direction is quote facing
	enum HorizontalFacing{
		LEFT,
		RIGHT,
	};


	//create the map for sprite states
	struct SpriteState{
		SpriteState(MotionType motion_type = STANDING, HorizontalFacing horizontal_facing = LEFT) :
		motion_type(motion_type), horizontal_facing(horizontal_facing) {}
		MotionType motion_type;
		HorizontalFacing horizontal_facing;
	};
	friend bool operator<(const SpriteState& a, const SpriteState& b);


	int x_, y_;
	
	std::map<SpriteState, boost::shared_ptr<Sprite>> sprites_;

	float velocity_x_;
	float acceleration_x_;
	HorizontalFacing horizontal_facing_;

	void initializeSprites(Graphics& graphics);
	SpriteState getSpriteState();

};

#endif // PLAYER_H_
