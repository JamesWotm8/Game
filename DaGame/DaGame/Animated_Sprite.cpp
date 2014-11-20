#include "Animated_Sprite.h"
#include "game.h"

AnimatedSprite::AnimatedSprite(const std::string& file_path, int source_x, int source_y, int width, int height, int fps, int num_frames):
Sprite(file_path, source_x, source_y, width, height),
frame_time_(1000/ fps),
num_frames_(num_frames),
current_frame_(0),
elapsed_time_(0){}

void AnimatedSprite::update(int elapsed_time_ms){
	elapsed_time_ += elapsed_time_ms;
	if (elapsed_time_ > frame_time_){
		++current_frame_; // increment the current frame
		elapsed_time_ = 0; // reset the elapsed time for the next frame
		if (current_frame_ < num_frames_){ // update the frame
			source_rect_.x += Game::kTileSize;
		}
		else{
			source_rect_.x -= Game::kTileSize * (num_frames_ - 1);
			current_frame_ = 0;
		}
	}
}