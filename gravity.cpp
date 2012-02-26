/* gravity.cpp -- the code that actually uses all and field to create
 * an animation of bodies interacting with each other's gravity
 *
 * Author : Suharsh Sivakumar
 * Date : 2/10/12
 */
 
#include "field.h"

using namespace std;

//global variables
int anim = 0;
int zoom = 20;
Field gravity(100);

//init -- initializes the viewing window
void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	gluOrtho2D(-1.5 * zoom, 1.5* zoom, -1*zoom, zoom);
}

//keyboard -- allows for user input into the program
void keyboard (unsigned char key, int x, int y)
{
	switch (key)
	{
		case 27: exit(0);
				break;
		case 'g': anim = 1;
				break;
		case 'p': anim = 0;
				break;
				// the next part will be once i figure out how to zoom in and out.
		case 'a': gravity.adjust_player(-1,0);
				break;
		case 'd': gravity.adjust_player(1,0);
				break;
		case 'w': gravity.adjust_player(0,1);
				break;
		case 's': gravity.adjust_player(0,-1);
				break;
		case 'b': Velocity v1;
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
				gravity.addBall(ball1);
				break;
	}
}

//idle -- determines when glutDisplayfunc is called back by glutMainLoop
void idle(void)
{
	//we only animate if anim == 1
	if (anim == 1)
		glutPostRedisplay();
}

void display(void)
{
	gravity.full_program();
}


//main -- the main function actually runs the program!!!! yay!!!
int main(int argc, char **argv)
{
	gravity.fill_rand_balls();

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
	glutInitWindowSize(1500,1000);
	glutInitWindowPosition(5,5);
	glutCreateWindow("Gravity Field!");
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);
	
	init();
	glutMainLoop();
}

