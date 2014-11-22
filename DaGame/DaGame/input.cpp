#include "input.h"

void Input::beginNewFrame(){
	pressed_keys_.clear(); // we need to clear both mappings of the keys
	released_keys_.clear();
}

void Input::keyUpEvent(const SDL_Event& event){
	pressed_keys_[event.key.keysym.sym] = true; // when pushed it is both held down and pushed and map it accordingly
	held_keys_[event.key.keysym.sym] = false;
}
void Input::keyDownEvent(const SDL_Event& event){
	released_keys_[event.key.keysym.sym] = true; // when released it is released and not held down and map it accordingly
	held_keys_[event.key.keysym.sym] = true;
}

bool Input::wasKeyPressed(SDLKey key){
	return pressed_keys_[key];
}

bool Input::wasKeyReleased(SDLKey key){
	return released_keys_[key];
}

bool Input::isKeyHeld(SDLKey key){
	return held_keys_[key];
}