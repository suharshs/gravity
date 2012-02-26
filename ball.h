/* ball.h -- header file for the ball class
 *
 * Author: Suharsh Sivakumar
 * 
 * Date : 2/9/2012
 *
 */
 
#ifndef _BALL_H_
#define _BALL_H_

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


using namespace std;
struct Color{
	int red;
	int green;
	int blue;
};

struct Position{
	double x;
	double y;
};

struct Velocity{
	double x;
	double y;
};

class Ball {
	private:
		Color color;
		Position position;
		Velocity velocity;
		double mass;
		double radius;
		int existence;
	public:
		Ball();//constructor
		Ball(Position start_place, Velocity start_speed, Color start_color , double Mass);//constructor
		Ball(Position start_place, Velocity start_speed, Color start_color , double Mass, double Radius); //constructor
		void setVelocity(Velocity new_v);
		Velocity getVelocity() const;
		void setPosition(Position new_p);
		Position getPosition() const;
		double getMass() const;
		void setMass(double Mass);
		double getRadius() const;
		void setRadius(double Radius);
		int getExistence();
		void setColor(Color c1);
		void gone();
		void show() const;
};



#endif