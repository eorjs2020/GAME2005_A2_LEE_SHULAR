#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"

PlayScene::PlayScene()
{
	PlayScene::start();

}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	
	if(EventManager::Instance().isIMGUIActive())
	{
		GUI_Function();
	}
	glm::vec4 color(1, 0, 0, 255);
	drawDisplayList();
	SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 255, 255, 255, 255);
	
}

void PlayScene::update()
{
	Start = m_pPlayer->start;
	updateDisplayList();

	if (!Start)
	{
		m_pPlayer->setAngle(m_pPlaneSprite->getTriAngle() * 180 / 3.14159265359f, m_pPlaneSprite->getTriAngle2());
		m_pPlayer->getTransform()->position = glm::vec2(m_pPlaneSprite->getPositionPC().x + (cos(m_pPlaneSprite->getTriAngle2()) * 20),
			m_pPlaneSprite->getPositionPC().y - (sin(m_pPlaneSprite->getTriAngle2()) * 20));
	}
	

}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();

	// handle player movement with GameController
	if (SDL_NumJoysticks() > 0)
	{
		if (EventManager::Instance().getGameController(0) != nullptr)
		{
			const auto deadZone = 10000;
			if (EventManager::Instance().getGameController(0)->LEFT_STICK_X > deadZone)
			{
				m_pPlayer->setAnimationState(PLAYER_RUN_RIGHT);
				m_playerFacingRight = true;
			}
			else if (EventManager::Instance().getGameController(0)->LEFT_STICK_X < -deadZone)
			{
				m_pPlayer->setAnimationState(PLAYER_RUN_LEFT);
				m_playerFacingRight = false;
			}
			else
			{
				if (m_playerFacingRight)
				{
					
					//m_pPlayer->setAnimationState(PLAYER_IDLE_RIGHT);
				}
				else
				{
					m_pPlayer->setAnimationState(PLAYER_IDLE_LEFT);
				}
			}
		}
	}


	// handle player movement if no Game Controllers found
	if (SDL_NumJoysticks() < 1)
	{
		if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A))
		{
			m_pPlayer->setAnimationState(PLAYER_RUN_LEFT);
			m_playerFacingRight = false;
		}
		else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D))
		{
			
			m_pPlayer->setAnimationState(PLAYER_RUN_RIGHT);
			m_playerFacingRight = true;
		}
		else
		{
			if (m_playerFacingRight)
			{
				m_pPlayer->setAnimationState(PLAYER_IDLE_RIGHT);
			}
			else
			{
				m_pPlayer->setAnimationState(PLAYER_IDLE_LEFT);
			}
		}
	}
	

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(START_SCENE);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2))
	{
		TheGame::Instance()->changeSceneState(END_SCENE);
	}
}

void PlayScene::start()
{
	// triangle points
	startPoint = glm::vec2(500.0f, 300.0f);
	widthEnd = new glm::vec2(600.0f, 300.0f);
	heightEnd = new glm::vec2(500.0f, 200.0f);

	// Set GUI Title
	m_guiTitle = "Play Scene";
	
	

	// Player Sprite
	m_pPlayer = new Player();
	addChild(m_pPlayer);
	m_playerFacingRight = true;

	// Plane Sprite
	m_pPlaneSprite = new Plane();
	addChild(m_pPlaneSprite);

	
	//// Back Button
	//m_pBackButton = new Button("../Assets/textures/backButton.png", "backButton", BACK_BUTTON);
	//m_pBackButton->getTransform()->position = glm::vec2(300.0f, 400.0f);
	//m_pBackButton->addEventListener(CLICK, [&]()-> void
	//{
	//	m_pBackButton->setActive(false);
	//	TheGame::Instance()->changeSceneState(START_SCENE);
	//});

	//m_pBackButton->addEventListener(MOUSE_OVER, [&]()->void
	//{
	//	m_pBackButton->setAlpha(128);
	//});

	//m_pBackButton->addEventListener(MOUSE_OUT, [&]()->void
	//{
	//	m_pBackButton->setAlpha(255);
	//});
	//addChild(m_pBackButton);

	//// Next Button
	//m_pNextButton = new Button("../Assets/textures/nextButton.png", "nextButton", NEXT_BUTTON);
	//m_pNextButton->getTransform()->position = glm::vec2(500.0f, 400.0f);
	//m_pNextButton->addEventListener(CLICK, [&]()-> void
	//{
	//	m_pNextButton->setActive(false);
	//	TheGame::Instance()->changeSceneState(END_SCENE);
	//});

	//m_pNextButton->addEventListener(MOUSE_OVER, [&]()->void
	//{
	//	m_pNextButton->setAlpha(128);
	//});

	//m_pNextButton->addEventListener(MOUSE_OUT, [&]()->void
	//{
	//	m_pNextButton->setAlpha(255);
	//});

	//addChild(m_pNextButton);

	/* Instructions Label */
	m_pInstructionsLabel = new Label("Press the backtick (`) character to toggle Debug View", "Consolas");
	m_pInstructionsLabel->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.5f, 10.0f);

	addChild(m_pInstructionsLabel);
}

void PlayScene::GUI_Function() const
{
	double posX = m_pPlayer->getTransform()->position.x,
		poY = m_pPlayer->getTransform()->position.y,
		velX = m_pPlayer->getRigidBody()->velocity.x,
		velY = m_pPlayer->getRigidBody()->velocity.y,
		magVel = Util::magnitude(m_pPlayer->getRigidBody()->velocity),
		accX = m_pPlayer->getRigidBody()->acceleration.x,
		accY = m_pPlayer->getRigidBody()->acceleration.y,
		magAcc = Util::magnitude(m_pPlayer->getRigidBody()->acceleration),
		force = m_pPlayer->getForce(),
		ang = (m_pPlaneSprite->getTriAngle() * 180 / 3.14159265359f);
	float dis = Util::distance(glm::vec2(m_pPlaneSprite->getPositionPB().x, 0), glm::vec2(m_pPlayer->getTransform()->position.x, 0))/ 50;
	//float dis = (m_pPlaneSprite->getPositionPB().x - m_pPlayer->getTransform()->position.x) / 50;
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();

	ImGui::Begin("Your Window Title Goes Here", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);
	if (!Start)
	{
		if (ImGui::Button("Start Simulation"))
		{
			m_pPlayer->MoveStart();
			m_pPlayer->start = true;
		}
	}
	else
	{
		if (ImGui::Button("Reset"))
		{
			m_pPlayer->Reset();
		}
	}
	ImGui::Separator();

	static float base = 1.0f;
	if (ImGui::SliderFloat("Ramp Base", &base, 1, 5))
	{
		m_pPlaneSprite->setTriBase(base * 50);
	}

	static float height = 1.0f;
	if (ImGui::SliderFloat("Ramp Height", &height, 1, 10))
	{
		m_pPlaneSprite->setTriHeight(height * 50);
	}
	static float mass = 12.4;
	if (ImGui::SliderFloat("Mass", &mass, 1, 100))
	{
		m_pPlayer->setMass(mass);
	}

	static float coeOfKinFric = 0.42;
	if (ImGui::SliderFloat("Friction", &coeOfKinFric, 0.01, 0.99))
	{
		m_pPlayer->setFriction(coeOfKinFric);
	}

	ImGui::Text("Velocity on x-axis = %.2f m/s", velX);
	ImGui::Text("Velocity on y-axis = %.2f m/s", velY);
	ImGui::Text("Velocity = %.2f m/s", magVel);
	ImGui::Text("The horizontal distance between Bottem right corner and the box %.2f m", dis);
	ImGui::Text("Acceleration on x-axis %.2f m/s^2", accX);
	ImGui::Text("Acceleration on y-axis %.2f m/s^2", accY);
	ImGui::Text("Acceleration %.2f m/s^2", magAcc);
	ImGui::Text("Force %.2f N", force);
	ImGui::Text("Angel of the triangle %.2f Degrees", ang);
	

	ImGui::End();
	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
	
}
