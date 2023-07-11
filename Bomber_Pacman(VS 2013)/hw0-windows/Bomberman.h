#ifndef BOMBER_MAN_H
#define BOMBER_MAN_H

#include "Board.h"
#include "Entity.h"

const int npmvertices = 1220;

class Bomberman : public Entity {

private:
	int nextXdir;
	int nextYdir;
	GLfloat pmvertices[npmvertices][2];
	int lives;
public:

	Bomberman() : Entity(), nextXdir(0), nextYdir(0), pmvertices{ 0.0f }, lives(2) {}

	void Draw(float sx/*center x*/, float sy/*center y*/, float radius);

	bool checkWall(Board& rb, int key);

	void setNextXdir(int xdir);

	void setNextYdir(int ydir);

	void resetNextXdir();

	void resetNextYdir();

	void setLives(int num);

	int getLives();

	void reset(int initialX, int initialY);
};

#endif

