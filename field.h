/* field.h -- header file for the Field class
*
* Author : Suharsh Sivakumar
* Date : 2/9/2012
*
*/

#ifndef _FIELD_H_
#define _FIELD_H_

#include "ball.h"

using namespace std;

class Field{
	private:
		Ball ** ball_array;
		int max_balls;
		int num_balls;
		void compute_gravity(); // computes and changes the velocity for each ball;
		void change_position(); // computes and changes the position due to the velocity at that instance;
		void show_all(); // puts all the balls onto the screen;
		bool endgame;
	public:
		Field(int max); //constructor
		~Field(); //destructor
		void addBall(Ball * newball); // adds a ball into the array (or into the field)
		void fill_rand_balls(); //fills the ball_array with max_balls balls with random characteristics.
		void full_program(); // combines the compute_gravity, change_position and show_all functions into one display function fo GLUT to use.
		void adjust_player(double dx, double dy);
		void game_over();
};
#endif