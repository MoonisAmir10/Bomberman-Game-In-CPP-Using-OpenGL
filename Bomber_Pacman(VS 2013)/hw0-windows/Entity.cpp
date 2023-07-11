#include "Entity.h"

void Entity::Draw(float sx/*center x*/, float sy/*center y*/, float radius)
{
	cout << "Entity drawn" << endl;
}

float Entity::getXpos()
{
	return m_x;
}

float Entity::getYpos()
{
	return m_y;
}

void Entity::setXpos(float sx)
{
	m_x = sx;
}

void Entity::setYpos(float sy)
{
	m_y = sy;
}

void Entity::setColor(ColorNames color)
{
	m_color = color;
}

ColorNames Entity::getColor()
{
	return m_color;
}

bool Entity::checkWall(Board& pb, int key)
{
	return false;
}

void Entity::setNextXdir(int xdir)
{
	cout << "Entity nextXdir" << endl;
}

void Entity::setNextYdir(int ydir)
{
	cout << "Entity nextYdir" << endl;
}

void Entity::resetNextXdir()
{
	cout << "Entity nextXdir" << endl;
}

void Entity::resetNextYdir()
{
	cout << "Entity nextYdir" << endl;
}

void Entity::setStatus(bool status)
{
	m_status = status;
}

bool Entity::getStatus()
{
	return m_status;
}

void Entity::destroy()
{
	m_status = false;
}

void Entity::reset()
{
	m_x = 0;
	m_y = 0;
	m_radius = 0;
	m_color = YELLOW;
	m_status = true;
}


