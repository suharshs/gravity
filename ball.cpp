/* ball.pp -- source code for the ball class
 *
 * Author: Suharsh Sivakumar
 * 
 * Date : 2/9/2012
 *
 */
 
#include "ball.h"
 
// Constructors
Ball::Ball()
{
	position.x = 0;
	position.y = 0;
	velocity.x = 0;
	velocity.y = 0;
	mass = 700.0;
	radius = mass/2000;
	color.red = 255;
	color.green = 140;
	color.blue = 0;
	existence = 1;
}

Ball::Ball(Position start_place, Velocity start_speed, Color start_color , double Mass)
{
	position = start_place;
	velocity = start_speed;
	mass = Mass;
	radius = Mass/30;
	color = start_color;
	existence = 1;
}

Ball::Ball(Position start_place, Velocity start_speed, Color start_color , double Mass, double Radius)
{
	position = start_place;
	velocity = start_speed;
	mass = Mass;
	radius = Radius;
	color = start_color;
	existence = 1;
}

// Other functions
void Ball::setVelocity(Velocity new_v)
{
	velocity = new_v;
}

Velocity Ball::getVelocity() const
{
	return velocity;
}

void Ball::setPosition(Position new_p)
{
	position = new_p;
}

Position Ball::getPosition() const
{
	return position;
}

double Ball::getMass() const
{
	return mass;
}	

void Ball::setMass(double Mass)
{
	mass = Mass;
}

double Ball::getRadius() const
{
	return radius;
}

void Ball::setRadius(double Radius)
{
	radius = Radius;
}

int Ball::getExistence()
{
	return existence;
}

void Ball::setColor(Color c1)
{
	color = c1;
}

void Ball::gone()
{
	existence = 0;
}
	
void Ball::show() const
{
	glPushMatrix();
	glColor3ub(color.red, color.green, color.blue);
	glTranslatef(position.x, position.y, 0);
	glutSolidSphere(radius, 50, 50);
	glPopMatrix();
}
		
		
		
		
		
	
	