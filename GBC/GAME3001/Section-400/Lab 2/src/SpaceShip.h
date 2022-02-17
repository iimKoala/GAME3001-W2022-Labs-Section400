#pragma once
#pragma once
#ifndef __Person__
#define __Person__

#include "Agent.h"

class Person final : public Agent
{
public:
	Person();
	~Person();

	// Inherited via GameObject
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	float getMaxSpeed() const;
	float getTurnRate() const;
	float getAccelerationRate() const;
	glm::vec2 getDesiredVelocity() const;

	void setMaxSpeed(float speed);
	void setTurnRate(float angle);
	void setAccelerationRate(float rate);
	void setDesiredVelocity(glm::vec2 target_position);

	void Seek();
	void LookWhereYoureGoing(glm::vec2 target_direction);

private:
	float m_maxSpeed;
	float m_turnRate;
	float m_accelerationRate;

	glm::vec2 m_desiredVelocity;

	void m_move();
};


#endif /* defined (__Person__) */
