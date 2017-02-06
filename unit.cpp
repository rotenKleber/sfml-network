#include "unit.hpp"

Unit::Unit(std::string name):
	head(10),
	torso(10),
	l_arm(10),
	r_arm(10),
	l_leg(10),
	r_leg(10),
	m_x((rand() % 8)),
	m_y((rand() % 8)),
	m_name(name)
{
}

void Unit::setPosition(int x, int y)
{
	m_x = x;
	m_y = y;
}
