#ifndef BOMB_H
#define BOMB_H

#include "Entity.h"
#include "Bomberman.h"

class Bomb : public Entity {

private:
	int m_time;
	bool m_isPlaced;

public:

	Bomb() : Entity()
	{
		setStatus(false);
		setColor(RED);
		m_time = 0;
		m_isPlaced = 0;
	}

	void Draw(float sx, float sy, float radius);

	void updateTimer();

	void explode(Board& pb, float bm_xpos, float bm_ypos, bool& flag);

	void setIsPlaced(bool isp);

	bool getIsPlaced();

	bool checkWall(Board& pb, int key = 0);

	void checkCascadedWall(Board& pb, int temp_checkX, int temp_checkY);

	void checkBombermanCollision(float bm_xpos, float bm_ypos, Board& pb, bool& flag);
};

#endif
