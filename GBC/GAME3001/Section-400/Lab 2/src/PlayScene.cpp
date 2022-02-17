#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"
#include "SpaceShip.h"
#include "Target.h"

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"
#include "Util.h"

PlayScene::PlayScene()
{
	PlayScene::start();
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	drawDisplayList();

	

	if (m_bDebugView)
	{
		Util::DrawCircle(m_pTarget->getTransform()->position, m_pTarget->getWidth() * 0.5f);


	if (m_p_Person->isEnabled())
	{
		Util::DrawCircle(m_p_Person->getTransform()->position, Util::max(m_p_Person->getWidth() * 0.5f , m_p_Person->getHeight()*0.5f));
	}
	}

	SDL_SetRenderDrawColor(Renderer::Instance().getRenderer(), 255, 255, 255, 255);
}

void PlayScene::update()
{
	updateDisplayList();

	CollisionManager::squaredRadiusCheck(m_p_Person, m_pTarget);
}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();



	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance().quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance().changeSceneState(START_SCENE);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2))
	{
		TheGame::Instance().changeSceneState(END_SCENE);
	}
}

void PlayScene::start()
{
	// Set GUI Title
	m_guiTitle = "Play Scene";
	m_bDebugView = false;

	m_pTarget = new Target();
	
		addChild(m_pTarget);

		m_p_Person = new Person();
		m_p_Person->setCurrentHeading(0.0); 
		m_p_Person->setTargetPosition(m_pTarget->getTransform()->position);
		m_p_Person->getRigidBody()->acceleration = m_p_Person->getCurrentDirection() * m_p_Person->getAccelerationRate();
		m_p_Person->setEnabled(false);
		addChild(m_p_Person);
			
	ImGuiWindowFrame::Instance().setGUIFunction(std::bind(&PlayScene::GUI_Function, this));
}

void PlayScene::GUI_Function() 
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();
	
	ImGui::Begin("Lab 2 Debug Properties", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoMove);

	ImGui::Separator();

	static bool toggleDebug = m_p_Person->isEnabled();
	if (ImGui::Checkbox("toggle Debug", &toggleDebug))
	{
		m_bDebugView = toggleDebug;
	}



	ImGui::Separator();

	static float position[2] = { m_pTarget->getTransform()->position.x,m_pTarget->getTransform()->position.y };
	if(ImGui::SliderFloat3("Target Position", position, 0.0f, 800.0f))
	{
		m_pTarget->getTransform()->position = glm::vec2(position[0], position[1]);
		m_p_Person->setTargetPosition(m_pTarget->getTransform()->position);
	}
	
	ImGui::Separator();

	static bool toggleSeek = m_p_Person->isEnabled();
		if (ImGui::Checkbox("toggle Seek", &toggleSeek)) 
		{
			m_p_Person->setEnabled(toggleSeek);
	}

		static float speed = m_p_Person->getMaxSpeed();
		if (ImGui::SliderFloat("Max Speed", &speed, 0.0f, 100.0f))
		{
			m_p_Person->setMaxSpeed(speed);
		
		}
		static float acceleration = m_p_Person->getAccelerationRate();
		if (ImGui::SliderFloat("Acceleration Rate", &acceleration, 0.0f, 50.0f))
		{
			m_p_Person->setAccelerationRate(acceleration);
			m_p_Person->getRigidBody()->acceleration = m_p_Person->getCurrentDirection() * m_p_Person->getAccelerationRate();
		}

		static float turn_rate = m_p_Person->getTurnRate();
		if (ImGui::SliderFloat("Turn Rate", &turn_rate, 0.0f, 50.0f))
		{
			m_p_Person->setTurnRate(turn_rate);
			m_p_Person->getRigidBody()->acceleration = m_p_Person->getCurrentDirection() * m_p_Person->getAccelerationRate();
		}
		if (ImGui::Button("Reset"))
		{
		
			
			m_p_Person->getTransform()->position = glm::vec2(100.0f, 400.0f);
			m_pTarget->getTransform()->position = glm::vec2(500.0f, 100.0f);
			m_p_Person->setCurrentHeading(0.0);
			m_p_Person->setTargetPosition(m_pTarget->getTransform()->position);
			m_p_Person->getRigidBody()->velocity = glm::vec2(0, 0);
			
			
			m_p_Person->getRigidBody()->velocity = m_p_Person->getCurrentDirection();
			m_p_Person->getRigidBody()->acceleration = m_p_Person->getCurrentDirection() * m_p_Person->getAccelerationRate();
		}

	ImGui::End();
}
