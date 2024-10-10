#include "stdafx.h"
#include "Agent.h"


Agent::Agent(float max_vel, float max_acc, float max_angvel, float max_angacc)
{
	max_velocity = max_vel;
	max_acceleration = max_acc;

	max_angvelocity = max_angvel;
	max_angacceleration = max_angacc;

	orientation.angle = 0.f;
}

Agent::Agent()
{
}


Agent::~Agent()
{
}

void Agent::updatePlayerControlledMovement(double dt)
{
	velocity.x = std::cos(orientation.angle) * speed * (dt / 1000);
	velocity.y = std::sin(orientation.angle) * speed * (dt / 1000);

	position += velocity;

	speed = std::clamp(speed, -50.0, 50.0);
	speed = speed * 0.995;
}

void Agent::increaseRotation()
{
	rotation++;
	//orientation.angle++;
	if (rotation > 359) {
		rotation = 0;
	}
	orientation.angle = rotation * (M_PI / 180);
}

void Agent::decreaseRotation()
{
	rotation--;
	//orientation.angle++;
	if (rotation < 0) {
		rotation =359;
	}
	orientation.angle = rotation * (M_PI / 180);
}

void Agent::increaseSpeed()
{

	speed += 5;
}

void Agent::decreaseSpeed()
{
	speed -= 5;
}
