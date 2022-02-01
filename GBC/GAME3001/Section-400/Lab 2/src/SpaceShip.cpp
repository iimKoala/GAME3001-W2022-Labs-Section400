#include "SpaceShip.h"
#include "TextureManager.h"
#include "Util.h"
#include "Game.h"
#include "GameObject.h"
#include "Agent.h"
SpaceShip::SpaceShip()
{
	TextureManager::Instance().load("../Assets/textures/ncl.png", "space_ship");

	const auto size = TextureManager::Instance().getTextureSize("space_ship");
	setWidth(size.x);
	setHeight(size.y);
	getTransform()->position = glm::vec2(100.0f, 100.0f);
	getRigidBody()->velocity = glm::vec2(0, 0);
	getRigidBody()->acceleration = glm::vec2(0, 0);
	getRigidBody()->isColliding = false;

	m_maxSpeed = 5.0f;
	m_turnRate = 5.0f;
	m_accelerationRate = 2.0f;

	setType(AGENT);
}

SpaceShip::~SpaceShip()
= default;

void SpaceShip::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the target
	TextureManager::Instance().draw("space_ship", x, y, 0, 255, true);
}

void SpaceShip::update()
{
	m_move();
}

void SpaceShip::clean()
{
}


float SpaceShip::getMaxSpeed() const {
	return m_maxSpeed;
}

float SpaceShip::getTurnRate() const
{
	return m_turnRate;
}
float SpaceShip::getAccelerationRate() const 
{
	return m_accelerationRate;
}
glm::vec2 SpaceShip::getDesiredVelocity() const
{
	return m_desiredVelocity;
}
void SpaceShip::setMaxSpeed(float speed)
{
	m_maxSpeed = speed;
}
void SpaceShip::setTurnRate(float angle)
{
	m_turnRate = angle;
}
void SpaceShip::setAccelerationRate(float rate)
{
	m_accelerationRate = rate;
}
void SpaceShip::setDesiredVelocity(glm::vec2 target_position)
{
	m_desiredVelocity = Util::normalize( target_position - getTransform()->position);
}
void SpaceShip::Seek()
{
	auto target_direction = getTargetPosition() = getTransform()->position;

	target_direction = Util::normalize(target_direction) = getCurrentDirection();

	setCurrentDirection(target_direction);

	/*getRigidBody()->velocity = getCurrentDirection() * getMaxSpeed();
	getRigidBody()->acceleration = getCurrentDirection() * getAccelerationRate();*/


}
void SpaceShip::LookWhereYoureGoing()
{


}
void SpaceShip::m_move()
{
	Seek();

	const float dt = TheGame::Instance().getDeltaTime();


	const glm::vec2 initial_position = getTransform()->position;

	auto current_acceleration = getCurrentDirection() * getAccelerationRate();
	



	

	

	const glm::vec2 initial_velocity = getRigidBody()->velocity;// *dt;

	const glm::vec2 acceleration_term = getRigidBody()->acceleration * 0.5f;// *dt;

	
		

	glm:: vec2 final_position = initial_position + initial_velocity + acceleration_term;

	getTransform()->position = final_position;


getRigidBody()->velocity += getRigidBody()->acceleration;

}