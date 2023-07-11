#include "Ghost.h"

void Ghost::Draw(float x, float y, float radius)
{
	int ogw = 6, ogh = 7;

	setXpos(x + nextXdir);
	setYpos(y + nextYdir);

	glPushMatrix();
	float sx = (float)m_width / ogw, sy = (float)m_height / ogh;
	glTranslatef((int)getXpos(), (int)getYpos(), 1);
	glScalef(sx, sy, 1);

	// Draw Enemy
	DrawRoundRect(0, 1, 6, 3, colors[getColor()]);
	DrawCircle(3, 4, 3.01, colors[getColor()]);
	glPushMatrix();
	glScalef(0.9, 1.1, 1);
	//  legs
	DrawCircle(0.75, 1, 0.75, colors[getColor()]);
	DrawCircle(3.25, 1, 0.75, colors[getColor()]);
	DrawCircle(5.85, 1, 0.75, colors[getColor()]);

	glPopMatrix();
	//	glPopMatrix();

	// eyes

	glPushMatrix();
	glScalef(0.9, 1.1, 1);
	DrawCircle(1.85, 3.95, 0.75, colors[WHITE]);
	DrawCircle(4.95, 3.95, 0.75, colors[WHITE]);
	glPopMatrix();

	// eyes
	DrawCircle(1.65, 4.25, 0.45, colors[BLUE]);
	DrawCircle(4.45, 4.25, 0.45, colors[BLUE]);
	glPopMatrix();
}

void Ghost::setWidth(float w)
{
	m_width = w;
}

void Ghost::setHeight(float h)
{
	m_height = h;
}

void Ghost::setNextXdir(int xdir)
{
	nextXdir += xdir;
}

void Ghost::setNextYdir(int ydir)
{
	nextYdir += ydir;
}

void Ghost::resetNextXdir()
{
	nextXdir = 0;
}

void Ghost::resetNextYdir()
{
	nextYdir = 0;
}

bool Ghost::checkWall(Board& rb, int key)
{
	float xcoord = ((float)getXpos()) / (float)rb.GetCellSize();
	float check_xcoord = ((float)getXpos() - 20) / (float)rb.GetCellSize();


	float ycoord = ((float)getYpos()) / (float)rb.GetCellSize();
	float check_up_ycoord = ((float)getYpos() - 10) / (float)rb.GetCellSize();
	float check_down_ycoord = ((float)getYpos() - 28) / (float)rb.GetCellSize();

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

void Ghost::randMove(Board& rb, int key)
{
	if (checkWall(rb, key) == true)
	{
		if (key == GLUT_KEY_LEFT) 
		{
			setNextXdir(-4);
		}
		else if (key == GLUT_KEY_RIGHT)
		{
			setNextXdir(4);
		}
		else if (key == GLUT_KEY_UP) 
		{
			setNextYdir(4);
		}
		else if (key == GLUT_KEY_DOWN) 
		{
			setNextYdir(-4);
		}
	}
}

void Ghost::checkBombermanCollision(float bm_xpos, float bm_ypos, Board& pb, bool& flag)
{
	//checking right and left of ghost
	if ((getXpos() + 0.5 * pb.GetCellSize() >= bm_xpos) && (bm_xpos >= getXpos() - 0.5 * pb.GetCellSize()))
		if (bm_ypos <= getYpos() + 0.5 * pb.GetCellSize() && (bm_ypos >= getYpos() - 0.5 * pb.GetCellSize()))
		{
			cout << "Bomberman Killed Horizontally by ghost" << endl;

			flag = true;
		}

	//checking up and down of bomb
		else if ((getYpos() + 0.5 * pb.GetCellSize() >= bm_ypos) && (bm_ypos >= getYpos() - 0.5 * pb.GetCellSize()))
		{
			if (bm_xpos <= getXpos() + 0.5 * pb.GetCellSize() && (bm_xpos >= getXpos() - 0.5 * pb.GetCellSize()))
			{
				cout << "Bomberman Killed Vertically by ghost" << endl;

				flag = true;
			}
		}
}

void Ghost::reset(int initialX, int initialY)
{
	setXpos(initialX);
	setYpos(initialY);

	setStatus(true);

	resetNextXdir();
	resetNextYdir();
}