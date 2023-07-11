#include "Bomberman.h"

void Bomberman::Draw(float sx/*center x*/, float sy/*center y*/, float radius)
{

	float hdegree = (M_PI - M_PI / 2.0) / 360.0;
	float angle = M_PI + M_PI / 6.0;
	for (int i = 0; i < npmvertices; ++i) {
		pmvertices[i][0] = radius * cos(angle);
		pmvertices[i][1] = radius * sin(angle);
		angle += hdegree;
	}

	setXpos(sx + nextXdir);
	setYpos(sy + nextYdir);

	glColor3fv(colors[getColor()]); // set the circle color
	glBegin(GL_TRIANGLE_FAN);
	glVertex4f(getXpos(), getYpos(), 0, 1);
	for (int i = 0; i < npmvertices; ++i)
		glVertex4f(getXpos() + pmvertices[i][0], getYpos() + pmvertices[i][1], 0, 1);
	glEnd();
	DrawCircle(getXpos() - radius + radius / 2, getYpos() + (radius - radius / 2),
	radius / 10, colors[BLACK]);
	
}

void Bomberman::setNextXdir(int xdir)
{
	nextXdir += xdir;
}

void Bomberman::setNextYdir(int ydir)
{
	nextYdir += ydir;
}

void Bomberman::resetNextXdir()
{
	nextXdir = 0;
}

void Bomberman::resetNextYdir()
{
	nextYdir = 0;
}

bool Bomberman::checkWall(Board& rb, int key)
{
	float xcoord = ((float)getXpos()) / (float)rb.GetCellSize();
	float check_xcoord = ((float)getXpos() - 19) / (float)rb.GetCellSize();

	float ycoord = ((float)getYpos()) / (float)rb.GetCellSize();

	float check_up_ycoord = ((float)getYpos() - 28) / (float)rb.GetCellSize();
	float check_down_ycoord = ((float)getYpos() - 32) / (float)rb.GetCellSize();

	if (key
		== GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) {
		// what to do when left key is pressed...

		if (rb.GetInitBlockPosition((int)check_xcoord, 12 - (int)ycoord) == NILL)
		{
			return true;
		}
	}
	else if (key
		== GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) {

		if (rb.GetInitBlockPosition((int)check_xcoord + 1, 12 - (int)ycoord) == NILL)
		{
			return true;
		}
	}
	else if (key
		== GLUT_KEY_UP/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/) {

		if (rb.GetInitBlockPosition((int)xcoord, 11 - (int)check_up_ycoord) == NILL)
		{
			return true;
		}
	}
	else if (key
		== GLUT_KEY_DOWN/*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/) {

		if (rb.GetInitBlockPosition((int)xcoord, 12 - (int)check_down_ycoord) == NILL)
		{
			return true;
		}
	}
		return false;
}

void Bomberman::setLives(int num)
{
	lives = num;
}

int Bomberman::getLives()
{
	return lives;
}

void Bomberman::reset(int initialX, int initialY)
{
	setXpos(initialX);
	setYpos(initialY);

	setStatus(true);

	resetNextXdir();
	resetNextYdir();
}
