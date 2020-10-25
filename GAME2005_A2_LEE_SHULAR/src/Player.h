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
	void Move();
	void MoveStart();
	void Reset();

	// setters
	void setAnimationState(PlayerAnimationState new_state);
	void setMass(float a) { mass = a; }
	void setFriction(float a) { Friction = a; }
	void setGravity(float a) { Gravity = a; }


	//getters 
	float getForce() { return m_force; };
	float getMass() { return mass; }
	float getFriction() { return Friction; }
	float getGravity() { return Gravity; }

	//calculation
	void calForce();
	
	

private:
	void m_buildAnimations();
	float mass = 12.4, m_force;
	PlayerAnimationState m_currentAnimationState;
public:
	bool start = false;
	bool teleport = true;
	SDL_Rect src;
	SDL_FRect dst;
	glm::vec2 initialVel;
protected:
	
	float angle2 = 0;
	float angle = 0;
	
	float Gravity = 9.8f;
	float Friction = 0.42;

};

#endif /* defined (__PLAYER__) */