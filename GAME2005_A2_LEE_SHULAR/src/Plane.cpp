#include "Plane.h"
#include "TextureManager.h"
#include "Util.h"


Plane::Plane()
{
	TextureManager::Instance()->loadSpriteSheet(
		"../Assets/sprites/atlas.txt",
		"../Assets/sprites/atlas.png", 
		"spritesheet");

	setSpriteSheet(TextureManager::Instance()->getSpriteSheet("spritesheet"));

	// set frame width
	setWidth(65);

	// set frame height
	setHeight(65);

	getTransform()->position = glm::vec2(400.0f, 200.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(PLANE);

	m_buildAnimations();
}

Plane::~Plane()
= default;

void Plane::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	//// draw the plane sprite with simple propeller animation
	//TextureManager::Instance()->playAnimation(
	//	"spritesheet", getAnimation("plane"),
	//	x, y, 0.5f, 0, 255, true);

	Util::DrawLine(pointA, pointB, color);
	Util::DrawLine(pointA, pointC, color);
	Util::DrawLine(pointC, pointB, color);

}

void Plane::update()
{
	pointA = glm::vec2{ posB, posA };
	pointB = glm::vec2{ base, posA };
	pointC = glm::vec2{ posB, height };
	hypotenuse = Util::distance(pointB, pointC);
	angle = asin(Util::distance(pointA, pointB) / hypotenuse);
	
}


void Plane::clean()
{
}

float Plane::getTriHeight()
{
	return height;
}

float Plane::getTriBase()
{
	return base;
}

float Plane::getTriAngle()
{
	return angle;
}

float Plane::getTriHypotenuse()
{
	return hypotenuse;
}

void Plane::setTriHeight(float a)
{
	height = posA - a;
}

void Plane::setTriBase(float b)
{
	base = posB + b;
}

void Plane::m_buildAnimations()
{
	Animation planeAnimation = Animation();

	planeAnimation.name = "plane";
	planeAnimation.frames.push_back(getSpriteSheet()->getFrame("plane1"));
	planeAnimation.frames.push_back(getSpriteSheet()->getFrame("plane2"));
	planeAnimation.frames.push_back(getSpriteSheet()->getFrame("plane3"));

	setAnimation(planeAnimation);
}