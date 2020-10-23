#pragma once
#ifndef __PLAYER__
#define __PLAYER__

#include "PlayerAnimationState.h"
#include "Sprite.h"

class Player final : public Sprite
{
public:
	Player();
	~Player();

	// Life Cycle Methods
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	void Start() { start += 1; }
	void setAngle(float angle, float angle2) { this->angle = angle; this->angle2 = angle2; }
	void PixelPerMeter(float ppm) { dst.h *= ppm; dst.w *= ppm; }

	// setters
	void setAnimationState(PlayerAnimationState new_state);

private:
	void m_buildAnimations();
	
	PlayerAnimationState m_currentAnimationState;
public:

	SDL_Rect src;
	SDL_FRect dst;
protected:
	bool start = false;
	float angle2 = 0;
	float angle = 0;
	
	float Gravity = 9.8f;
	float Friction = 0.42;

};

#endif /* defined (__PLAYER__) */