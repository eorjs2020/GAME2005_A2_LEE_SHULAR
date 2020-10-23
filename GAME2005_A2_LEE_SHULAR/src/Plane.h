#pragma once
#ifndef __PLANE__
#define __PLANE__

#include "Sprite.h"
#include "GLM/vec2.hpp"
#include "GLM/vec4.hpp"
#include "Config.h" 

class Plane final : public Sprite
{
public:
	Plane();
	~Plane();

	// Life Cycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	float getTriHeight();
	float getTriBase();
	float getTriAngle();
	float getTriAngle2();
	float getTriHypotenuse();
	void setTriHeight(float a);
	void setTriBase(float b);
	glm::vec2 getPositionPC() { return pointC; };
	glm::vec2 getPositionPB() { return pointB; };
	glm::vec2 getPositionPA() { return pointA; };
	

private:
	void m_buildAnimations();
	float angle, hypotenuse, angle2;
	glm::vec2 pointA{ 0.0f, 0.0f }, pointB{ 0.0f, 0.0f }, pointC{ 0.0f, 0.0f };
	glm::vec4 color{ 0.0f, 0.0f, 1.0f, 1.0f };
	//Used for where the orignal position of base and height points
	float height = 350, base = 200;
	//Used for where the Triangle is positioned on screen 
	float posA = Config::SCREEN_HEIGHT - 50, posB = 50.0f;
};

#endif /* defined (__PLANE__) */
