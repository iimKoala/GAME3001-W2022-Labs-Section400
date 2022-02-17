#include "SpaceShip.h"

#include "SpaceShip.h"
#include "TextureManager.h"
#include "Util.h"
#include "Game.h"
#include "GameObject.h"
#include "Agent.h"
Person::Person()
{
	TextureManager::Instance().load("../Assets/textures/AISprite.png", "Person");

	const auto size = TextureManager::Instance().getTextureSize("Person");
	setWidth(size.x);
	setHeight(size.y);
	getTransform()->position = glm::vec2(100.0f, 100.0f);
	getRigidBody()->velocity = glm::vec2(0, 0);
	getRigidBody()->acceleration = glm::vec2(0, 0);
	getRigidBody()->isColliding = false;

	m_maxSpeed = 20.0f;
	m_turnRate = 5.0f;
	m_accelerationRate = 4.0f;

	setType(AGENT);
}

Person::~Person()
= default;

void Person::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the target
	TextureManager::Instance().draw("Person", x, y, getCurrentHeading(), 255, true);
}

void Person::update()
{
	m_move();
}

void Person::clean()
{
}


float Person::getMaxSpeed() const {
	return m_maxSpeed;
}

float Person::getTurnRate() const
{
	return m_turnRate;
}
float Person::getAccelerationRate() const 
{
	return m_accelerationRate;
}
glm::vec2 Person::getDesiredVelocity() const
{
	return m_desiredVelocity;
}
void Person::setMaxSpeed(float speed)
{
	m_maxSpeed = speed;
}
void Person::setTurnRate(float angle)
{
	m_turnRate = angle;
}
void Person::setAccelerationRate(float rate)
{
	m_accelerationRate = rate;
}
void Person::setDesiredVelocity(glm::vec2 target_position)
{
	m_desiredVelocity = Util::normalize( target_position - getTransform()->position);
}
void Person::Seek()
{
	setDesiredVelocity(getTargetPosition());

	

	const glm::vec2 steering_direction = getDesiredVelocity() - getCurrentDirection();

	LookWhereYoureGoing(steering_direction);

	
	getRigidBody()->acceleration = getCurrentDirection() * getAccelerationRate();


}
void Person::LookWhereYoureGoing(const glm::vec2 target_direction)
{
	float target_rotation = Util::signedAngle(getCurrentDirection(), target_direction); 

	float turn_sensitivity = 5.0f;

	if (abs(target_rotation) > turn_sensitivity)
	{
		if (target_rotation > 0.0f)
		{
			setCurrentHeading(getCurrentHeading() + getTurnRate());
		}
		else if (target_rotation < 0.0f)
			setCurrentHeading(getCurrentHeading() - getTurnRate());
	}
	

	
}
void Person::m_move()
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

getRigidBody()->velocity = Util::clamp(getRigidBody()->velocity, getMaxSpeed());

}