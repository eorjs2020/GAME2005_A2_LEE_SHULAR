#include "Player.h"
#include "TextureManager.h"
#include "Renderer.h"
#include "Util.h"

Player::Player(): m_currentAnimationState(PLAYER_IDLE_RIGHT)
{
	TextureManager::Instance()->load("../Assets/textures/rts_crate_small.png", "box");
	src.x = 0;
	src.y = 0;
	src.w = 512;
	src.h = 512;
	dst.x = 0;
	dst.y = 0;
	dst.w = 40;
	dst.h = 40;
	setWidth(20);
	setHeight(20);
	getTransform()->position = glm::vec2(400.0f, 300.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(PLAYER);
	

}

Player::~Player()
= default;

void Player::draw()
{
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	TextureManager::Instance()->draw("box", x, y, angle, 255, true, SDL_FLIP_NONE, 40, 40);
	//SDL_RenderCopyEx(Renderer::Instance()->getRenderer(), m_textureMap[id].get(), &srcRect, &destRect, angle, nullptr, flip);
	//SDL_RenderCopyExF(Renderer::Instance()->getRenderer(),TextureManager::Instance()->getTexture("box"), &src, &dst, angle , nullptr, SDL_FLIP_NONE);
}

void Player::update()
{
	if (start)
	{

	}
}

void Player::clean()
{
}

void Player::setAnimationState(const PlayerAnimationState new_state)
{
	m_currentAnimationState = new_state;
}

void Player::force()
{
	m_force = sqrt(Util::magnitude(getRigidBody()->acceleration) * mass);
}

void Player::m_buildAnimations()
{
	Animation idleAnimation = Animation();

	idleAnimation.name = "idle";
	idleAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-idle-0"));
	idleAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-idle-1"));
	idleAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-idle-2"));
	idleAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-idle-3"));

	setAnimation(idleAnimation);

	Animation runAnimation = Animation();

	runAnimation.name = "run";
	runAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-run-0"));
	runAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-run-1"));
	runAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-run-2"));
	runAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-run-3"));

	setAnimation(runAnimation);
}
