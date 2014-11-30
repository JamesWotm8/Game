#include "player.h"
#include "game.h"
#include "sprite.h"
#include "Animated_Sprite.h"
#include "graphics.h"

#include <cmath>
#include <algorithm> 

namespace{
	const float kWalkingAcceleration = 0.0012f; // this is the acceleration in pixels per milisecond / per ms
	const float kSlowDownFactor = 0.8f;
	const float kMaxSpeedX = 0.325f; // max speed just pixels per ms

	const int kJumpTime = 275; // number of ms to jump
	const float kJumpSpeed = 0.325f; // pixels per ms
	const float kMaxSpeedY = 0.325f;

	const float kGravity = 0.0012f;
}

bool operator<(const Player::SpriteState& a, const Player::SpriteState& b){
	if (a.motion_type != b.motion_type){
		return a.motion_type < b.motion_type;
	}
	if (a.horizontal_facing != b.horizontal_facing){
		return a.horizontal_facing < b.horizontal_facing;
	}

	return false;
}

Player::Player(Graphics& graphics, int x, int y) :
x_(x), y_(y), velocity_x_(0.0f), velocity_y_(0.0f), acceleration_x_(0.0f), horizontal_facing_(LEFT), on_ground_(false)  {
	initializeSprites(graphics);// change this to the initializeSprite() method which does additional things
}


void Player::update(int elapsed_time_ms){
	sprites_[getSpriteState()]->update(elapsed_time_ms);
	jump_.update(elapsed_time_ms);

	x_ += round(velocity_x_ * elapsed_time_ms); // here is where we accelerate only deals with velocity, no directions
	velocity_x_ += acceleration_x_ * elapsed_time_ms;
	if (acceleration_x_ < 0.0f){
		velocity_x_ = std::max(velocity_x_, -kMaxSpeedX);
	}else if (acceleration_x_ > 0.0f){
		velocity_x_ = std::min(velocity_x_, kMaxSpeedX);
	}else if (on_ground()){
		velocity_x_ *= kSlowDownFactor;
	}

	y_ += round(velocity_y_ * elapsed_time_ms);
	if (!jump_.active()){
		velocity_y_ = std::min(velocity_y_ + kGravity * elapsed_time_ms, kMaxSpeedY); // dont want it to exceed a certain velocity Y
	}

	// TODO remove this quick fix for collision fall just to stop him from falling forever
	if (y_ >= 320){
		y_ = 320;
		velocity_y_ = 0.0f;
	}
	on_ground_ = y_ == 320;
}

void Player::draw(Graphics& graphics) {
	sprites_[getSpriteState()]->draw(graphics, x_, y_);
}

void Player::startMovingLeft() {
	acceleration_x_ = -kWalkingAcceleration;
	horizontal_facing_ = LEFT;
}

void Player::startMovingRight() {
	acceleration_x_ = kWalkingAcceleration;
	horizontal_facing_ = RIGHT;
}

void Player::stopMoving() {
	acceleration_x_ = 0.0f;
}

void Player::startJump(){
	if (on_ground()){ // if we are on ground
		jump_.reset();
		velocity_y_ = -kJumpSpeed;
	}else if(velocity_y_ < 0.0f){ // velocity y will be when we our velocity is aimed towards the top of the screen
		jump_.reactivate();
	}

	// if we are on the ground then we want to reset our jump (being able to jump) and give us a vertical velocity
	//otherwise we are not on the ground, no jump reset
	//if falling down, cannot do anything.
	//else if mid jump, can reactivate jump.
}

void Player::stopJump(){
	jump_.deactivate();
}


//the method now has different animations for which direction the player chooses quote to walk/stand
void Player::initializeSprites(Graphics& graphics){
	sprites_[SpriteState(WALKING, LEFT)] = boost::shared_ptr<Sprite>(new AnimatedSprite(graphics, "Images/MyChar.bmp", 0, 0, Game::kTileSize, Game::kTileSize, 15, 3)); // take note that both walking sprites for left and right are AnimatedSprites
	sprites_[SpriteState(STANDING, LEFT)] = boost::shared_ptr<Sprite>(new Sprite(graphics, "Images/MyChar.bmp", 0, 0, Game::kTileSize, Game::kTileSize)); // normal Sprite because of no animation when standing still
	sprites_[SpriteState(WALKING, RIGHT)] = boost::shared_ptr<Sprite>(new AnimatedSprite(graphics, "Images/MyChar.bmp", 0, Game::kTileSize, Game::kTileSize, Game::kTileSize, 15, 3)); // animated sprite
	sprites_[SpriteState(STANDING, RIGHT)] = boost::shared_ptr<Sprite>(new Sprite(graphics, "Images/MyChar.bmp", 0, Game::kTileSize, Game::kTileSize, Game::kTileSize)); //sprite
}

Player::SpriteState Player::getSpriteState(){
	return SpriteState(acceleration_x_ == 0.0f ? STANDING : WALKING,
		horizontal_facing_);
}

void Player::Jump::reset(){
	time_remaining_ms_ = kJumpTime;
	reactivate();
}

void Player::Jump::update(int elapsed_time_ms){
	if (active_){
		time_remaining_ms_ -= elapsed_time_ms;
		if (time_remaining_ms_ <= 0){
			active_ = false;
		}
	}
}