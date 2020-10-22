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
	void setAngle(float angle) { this->angle = angle; }
	void setDstXY(glm::vec2 position) { dst.x = position.x +dst.w/2; dst.y = position.y - 15;  }

	// setters
	void setAnimationState(PlayerAnimationState new_state);

private:
	void m_buildAnimations();
	
	PlayerAnimationState m_currentAnimationState;
public:
	float angle = 0;
	SDL_Rect src;
	SDL_FRect dst;
};

#endif /* defined (__PLAYER__) */