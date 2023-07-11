#ifndef GHOST_H
#define GHOST_H

#include "Entity.h"

class Ghost : public Entity {

private:
	int nextXdir;
	int nextYdir;
	float m_width;
	float m_height;

public:

	Ghost() : Entity() 
	{
		nextXdir = 0;
		nextYdir = 0;
		m_width = 6;
		m_height = 7;
		setColor(PINK);
	}

	void Draw(float x, float y, float radius = 0);

	void setWidth(float w);

	void setHeight(float h);

	void setNextXdir(int xdir);

	void setNextYdir(int ydir);

	void resetNextXdir();

	void resetNextYdir();

	bool checkWall(Board& rb, int key);

	void randMove(Board& rb, int key);

	void checkBombermanCollision(float bm_xpos, float bm_ypos, Board& pb, bool& flag);

	void reset(int initialX, int initialY);
};

#endif
