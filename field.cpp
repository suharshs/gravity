/* field.cpp -- source code for the Field class
*
* Author : Suharsh Sivakumar
* Date : 2/9/2012
*
*/

#include "field.h"
#include "time.h"

//Constructors
Field::Field(int max)
{
	max_balls = max;
	ball_array = new Ball *[max_balls];
	for (int i = 0; i < max_balls; i++)
	{
		ball_array[i] = NULL;
	}
	num_balls = 0;
	endgame = 1;
}

//Destructor
Field::~Field()
{
	for(int i = 0; i < max_balls; i++)
	{
		if (ball_array[i] != NULL)
			delete ball_array[i];
	}
	delete ball_array;
}

// addBall allows balls to be added to the field
void Field::addBall(Ball * newball)
{
	ball_array[num_balls] = newball;
	num_balls++;
}

//fill_rand_balls-- fills the array with random balls with random characteristics
void Field::fill_rand_balls()
{
	ball_array[0] = new Ball();
	srand(time(NULL));
	num_balls++;
	for(int i = 1; i < max_balls-2; i++)
	{
		Position p1;
		p1.x = ((rand() % 200)-(rand() % 200)) / 9.9;
		p1.y = ((rand() % 200)-(rand() % 200)) / 9.9;
		Velocity v1;
		v1.x = ((rand() % 100)-(rand() % 100)) / 0.5;
		v1.y = ((rand() % 100)-(rand() % 100)) / 0.5;
		Color c1;
		c1.red = rand() % 255;
		c1.green = rand() % 255;
		c1.blue = rand() % 255;
		double Mass = (rand() % 1200)+1;
		double Radius = Mass/ 2000.0;
		//printf(" p1 = %f %f. v1 = %f %f. c1 = %i %i %i. Mass = %f. Radius = %f.\n", p1.x, p1.y, v1.x, v1.y, c1.red, c1.green, c1.blue, Mass, Radius);
		ball_array[i] = new Ball(p1, v1, c1, Mass, Radius);
		num_balls++;
	}
}
	

// compute_gravity -- does gravity calculations and adjust velocities of balls
void Field::compute_gravity()
{
	double G = 100.0;
	double gravity_magnitude = 0.0;
	double x_component;
	double y_component;
	double distance_squared = 0.0;
	for (int i = 0; i < num_balls; i++)
	{
		if (ball_array[i]->getExistence())
		{
			x_component = 0.0;
			y_component = 0.0;
			Velocity new_v;
			for (int j = 0; j < num_balls; j++)
			{
				if(i != j && ball_array[j]->getExistence())
				{
					distance_squared = ((ball_array[i]->getPosition()).x - (ball_array[j]->getPosition()).x)*((ball_array[i]->getPosition()).x - (ball_array[j]->getPosition()).x) + ((ball_array[i]->getPosition()).y - (ball_array[j]->getPosition()).y)*((ball_array[i]->getPosition()).y - (ball_array[j]->getPosition()).y);
					gravity_magnitude = G*(ball_array[i]->getMass())*(ball_array[j]->getMass())/distance_squared; //this is only magnitude.
					x_component += gravity_magnitude * ((ball_array[j]->getPosition()).x - (ball_array[i]->getPosition()).x)/sqrt(distance_squared);
					y_component += gravity_magnitude * ((ball_array[j]->getPosition()).y - (ball_array[i]->getPosition()).y)/sqrt(distance_squared);
					if (sqrt(distance_squared) <= (ball_array[i]->getRadius() + ball_array[j]->getRadius()) && (ball_array[i]->getRadius()) > (ball_array[j]->getRadius()))
					{
						ball_array[i]->setRadius(pow(ball_array[i]->getRadius()*ball_array[i]->getRadius()*ball_array[i]->getRadius() + ball_array[j]->getRadius()*ball_array[j]->getRadius()*ball_array[j]->getRadius(), 1.0/3.0));
						ball_array[i]->setMass(ball_array[i]->getMass() + ball_array[j]->getMass());
						new_v.x = (ball_array[i]->getMass() * (ball_array[i]->getVelocity()).x + ball_array[j]->getMass() * (ball_array[j]->getVelocity()).x)/(ball_array[i]->getMass() + ball_array[j]->getMass());
						new_v.y = (ball_array[i]->getMass() * (ball_array[i]->getVelocity()).y + ball_array[j]->getMass() * (ball_array[j]->getVelocity()).y)/(ball_array[i]->getMass() + ball_array[j]->getMass());
						ball_array[j]->gone();
						ball_array[i]->setVelocity(new_v);
					}
				}
			}
			new_v.x = (ball_array[i]->getVelocity()).x + .00001 * x_component / ball_array[i]->getMass();
			new_v.y = (ball_array[i]->getVelocity()).y + .00001 * y_component / ball_array[i]->getMass();
			if ((ball_array[i]->getPosition()).x >= 30 - (ball_array[i]->getRadius()) || (ball_array[i]->getPosition()).x <= -30 + (ball_array[i]->getRadius()))
				new_v.x *= -1;
			if ((ball_array[i]->getPosition()).y >= 20 - (ball_array[i]->getRadius()) || (ball_array[i]->getPosition()).y <= -20 + (ball_array[i]->getRadius()))
				new_v.y *= -1;
			ball_array[i]->setVelocity(new_v);
		}
	}
}

// change_position -- changes the position needed for the objects to move on screen
void Field::change_position()
{
	for (int i = 0; i < num_balls; i++)
	{
		if (ball_array[i]->getExistence())
		{
			Position new_p;
			new_p.x = (ball_array[i]->getPosition()).x + .0001 * (ball_array[i]->getVelocity()).x;
			new_p.y = (ball_array[i]->getPosition()).y + .0001 * (ball_array[i]->getVelocity()).y;
			ball_array[i]->setPosition(new_p);
		}
	}
}

// show_all -- displays all the balls using the glut library
void Field::show_all()
{
	Color color;
	glClear(GL_COLOR_BUFFER_BIT);
	if (ball_array[0]->getExistence())
		ball_array[0]->show();
	for (int i = 1; i < num_balls; i++)
	{
		if (ball_array[i]->getExistence())
		{
			if (ball_array[i]->getRadius() > ball_array[0]->getRadius())
			{
				color.red = 255;
				color.green = 0;
				color.blue = 0;
			}
			else
			{
				color.red = 0;
				color.green = 0;
				color.blue = 200;
			}
			ball_array[i]->setColor(color);
			ball_array[i]->show();
		}
	}
	glFlush();
}

// full_program -- the actual function that will be used by the glutdisplay function in the client code
void Field::full_program()
{
	compute_gravity();
	change_position();
	show_all();
	game_over();
}

// adjust_player -- this function changes the balls so the user can control it.
void Field::adjust_player(double dx, double dy)
{
	Velocity new_v;
	new_v.x = (ball_array[0]->getVelocity()).x + (50*dx);
	new_v.y = (ball_array[0]->getVelocity()).y + (50*dy);
	ball_array[0]->setVelocity(new_v);
}

void Field::game_over()
{
	if (!(ball_array[0]->getExistence()) && endgame)
	{
		Velocity v1;
		v1.x = 0;
		v1.y = 0;
		Position p1;
		p1.x = 0;
		p1.y = 0;
		Color c1;
		c1.red = 0;
		c1.green = 0;
		c1.blue = 0;
		Ball * ball1 = new Ball(p1,v1,c1,10000000,.01);
		addBall(ball1);
		endgame = 0;
	}
}
