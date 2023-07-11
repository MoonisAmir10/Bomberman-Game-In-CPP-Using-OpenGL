#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include "Board.h"

class Entity {

private:
	float m_x;
	float m_y;
	float m_radius;
	ColorNames m_color;
	bool m_status;

public:
	Entity()
	{
		m_x = 0;
		m_y = 0;
		m_radius = 0;
		m_color = YELLOW;
		m_status = true;
	}

	virtual void Draw(float sx/*center x*/, float sy/*center y*/, float radius = 0);

	virtual float getXpos();

	virtual float getYpos();

	virtual void setXpos(float sx);

	virtual void setYpos(float sy);

	virtual void setColor(ColorNames color);

	virtual ColorNames getColor();

	virtual bool checkWall(Board& pb, int key = 0);

	virtual void setNextXdir(int xdir);

	virtual void setNextYdir(int ydir);

	virtual void resetNextXdir();

	virtual void resetNextYdir();

	virtual void setStatus(bool status);

	virtual bool getStatus();

	virtual void destroy();

	virtual void reset();
};

#endif
