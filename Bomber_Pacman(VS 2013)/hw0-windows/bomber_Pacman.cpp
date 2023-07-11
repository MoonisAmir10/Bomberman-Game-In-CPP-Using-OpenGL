//============================================================================
// Name        : bubble-shooter.cpp
// Author      : Sibt ul Hussain
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game of Bubble Shooting...
//============================================================================
#ifndef BOMBER_PACMAN_CPP
#define BOMBER_PACMAN_CPP

//#include <GL/gl.h>
//#include <GL/glut.h>
#include "Board.h"
#include "util.h"
#include <iostream>
#include <cstring>
#include<cmath> // for basic math functions such as cos, sin, sqrt
#include "Bomberman.h"
#include "Entity.h"
#include "Bomb.h"
#include "Ghost.h"

using namespace std;

#define FPS 10

Entity* g_entities[3];

// seed the random numbers generator by current time (see the documentation of srand for further help)...

/* Function sets canvas size (drawing area) in pixels...
*  that is what dimensions (x and y) your game will have
*  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
* */
void SetCanvasSize(int width, int height) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/*
* Main Canvas drawing function.
* */
Board* b;

void GameDisplay()/**/{
	// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.

	glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
		0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear(GL_COLOR_BUFFER_BIT); //Update the colors

	int bm_iniX = 0, bm_iniY = 0, gh_iniX = 0, gh_iniY = 0;

	b->GetInitBombermanPosition(bm_iniX, bm_iniY);
	b->GetInitPinkyPosition(gh_iniX, gh_iniY);

	if (g_entities[0]->getStatus() == false)
	{
		dynamic_cast<Bomberman*>(g_entities[0])->reset(bm_iniX, bm_iniY);
		dynamic_cast<Bomberman*>(g_entities[0])->setLives(dynamic_cast<Bomberman*>(g_entities[0])->getLives() - 1);

		dynamic_cast<Ghost*>(g_entities[2])->reset(gh_iniX, gh_iniY);

		b->resetBoard();
	}

	b->Draw();
	int x = 0, y = 0;
	b->GetInitPinkyPosition(x, y);
	//cout << x << "  y= " << y << endl << flush;

	dynamic_cast<Ghost*>(g_entities[2])->setWidth((0.8 * b->GetCellSize()));

	dynamic_cast<Ghost*>(g_entities[2])->setHeight((0.8 * b->GetCellSize()));

	g_entities[2]->Draw(x, y);

	b->GetInitBombermanPosition(x, y);

	g_entities[0]->Draw(x, y, b->GetCellSize() / 2 - 2);

	b->GetInitTextPosition(x, y);
	//cout << endl << "Text Position = " << x << "  y= " << y << endl << flush;

	string lifenum = Num2Str(dynamic_cast<Bomberman*>(g_entities[0])->getLives());

	string LivesText = "Lives Left = " + lifenum;

	DrawString(x, y, "Score = 000", colors[5]);

	DrawString(x + 10 * b->GetCellSize(), y, LivesText, colors[5]);

	//	glPopMatrix();
	if (g_entities[1]->getStatus() == true) {
		//DrawCircle(450, 80, 15, colors[RED]); // To Draw a bomb. You will provide your own x and y relative to Bombermans position
		
		g_entities[1]->Draw(g_entities[1]->getXpos(), g_entities[1]->getYpos(), 15);

	}

	glutSwapBuffers(); // do not modify this line..

}

/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arrow)
* is pressed from the keyboard
*
* You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
*
* This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
* program coordinates of mouse pointer when key was pressed.
*
* */

void NonPrintableKeys(int key, int x, int y) {

	if (g_entities[0]->checkWall(*b, key) == true) {

		if (key
			== GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) {
			// what to do when left key is pressed...

			g_entities[0]->setNextXdir(-4);

		}
		else if (key
			== GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) {

				g_entities[0]->setNextXdir(4);
		}
		else if (key
			== GLUT_KEY_UP/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/) {
			
				g_entities[0]->setNextYdir(4);
		}

		else if (key
			== GLUT_KEY_DOWN/*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/) {
			
				g_entities[0]->setNextYdir(-4);
		}
	}

	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	* this function*/
	
	glutPostRedisplay();

	//glutSwapBuffers();
	
}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
* is pressed from the keyboard
* This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
* program coordinates of mouse pointer when key was pressed.
* */
void PrintableKeys(unsigned char key, int x, int y) {
	if (key == 27/* Escape key ASCII*/) {
		exit(1); // exit the program when escape key is pressed.
	}

	if (key == 'b' || key == 'B') //Key for placing the bomb
	{
		if (dynamic_cast<Bomb*>(g_entities[1])->getIsPlaced() == false)
		{
			int blockX = (int)(g_entities[0]->getXpos() / b->GetCellSize());
			int blockY = (int)(g_entities[0]->getYpos() / b->GetCellSize());

			int centerX = (blockX * b->GetCellSize()) + (b->GetCellSize() / 2);
			int centerY = (blockY * b->GetCellSize()) + (b->GetCellSize() / 2);

			cout << centerX << "  " << centerY << endl;

			g_entities[1]->setXpos(centerX - 10);
			g_entities[1]->setYpos(centerY);

			g_entities[1]->setStatus(true);
			dynamic_cast<Bomb*>(g_entities[1])->setIsPlaced(true);
		}

	}
	glutPostRedisplay();
}

/*
* This function is called after every 1000.0/FPS milliseconds
* (FPS is defined on in the beginning).
* You can use this function to animate objects and control the
* speed of different moving objects by varying the constant FPS.
*
* */
void Timer(int m) {
	// implement your functionality here

	cout << "Timer called" << endl;

	float bm_xpos = g_entities[0]->getXpos();

	float bm_ypos = g_entities[0]->getYpos();

	bool bm_deathflag = false;

	dynamic_cast<Bomb*>(g_entities[1])->updateTimer();

	dynamic_cast<Bomb*>(g_entities[1])->explode(*b, bm_xpos, bm_ypos, bm_deathflag);

	//For ghost movement
	InitRandomizer();

	int gh_key = GetRandInRange(100, 104);

	dynamic_cast<Ghost*>(g_entities[2])->randMove(*b, gh_key);

	cout << "ghost key = " << gh_key << endl;

	dynamic_cast<Ghost*>(g_entities[2])->checkBombermanCollision(bm_xpos, bm_ypos, *b, bm_deathflag);

	if (bm_deathflag == true)
	{
		g_entities[0]->setStatus(false);
	}

	glutPostRedisplay();
	
	// once again we tell the library to call our Timer function after next 1000/FPS
	glutTimerFunc(1000.0, Timer, 0);
}

/*
* our gateway main function
* */
int main(int argc, char*argv[]) {

	b = new Board(60, 60); // create a new board object to use in the Display Function ...

	g_entities[0] = new Bomberman();
	g_entities[1] = new Bomb();
	g_entities[2] = new Ghost();

	int width = 1020, height = 840; // i have set my window size to be 800 x 600

	b->InitalizeBoard(width, height);
	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("CP's Bomber Bomberman"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...

	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.
#ifdef WITH_TEXTURES
	RegisterTextures();
#endif
	glutDisplayFunc(GameDisplay); // tell library which function to call for drawing Canvas.
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutTimerFunc(1000.0, Timer, 0);

	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();
	return 1;
}
#endif /* Bomberman_CPP_ */
