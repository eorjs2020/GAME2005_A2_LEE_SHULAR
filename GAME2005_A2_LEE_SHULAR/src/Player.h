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
	void setAngle(float angle, float angle2) { this->angle = angle; this->angle2 = angle2; }
	void setDstXY(glm::vec2 position) { dst.x = position.x + (float)(cos(angle2)*20); 
	dst.y = position.y - (float)(sin(angle2) * 20);  }

	// setters
	void setAnimationState(PlayerAnimationState new_state);
	float getMass() { return mass; }
	void setMass(float a) { mass += a; }

private:
	void m_buildAnimations();
	float mass = 12.4;
	PlayerAnimationState m_currentAnimationState;
public:
	float angle2 = 0;
	float angle = 0;
	SDL_Rect src;
	SDL_FRect dst;
	

};

#endif /* defined (__PLAYER__) */