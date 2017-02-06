#ifndef UNIT_H_
#define UNIT_H_

#include "game.hpp"
#include <string>

class Unit {
public:
	Unit(std::string name);
	
	int getHeadH() const {return head;};
	int getTorsoH() const {return torso;};
	int getL_ArmH() const {return l_arm;};
	int getR_ArmH() const {return r_arm;};
	int getL_LegH() const {return l_leg;};
	int getR_LegH() const {return r_leg;};
	std::string getName() const {return m_name;};
	int getX() const {return m_x;};
	int getY() const {return m_y;};
	
	void setPosition(int x, int y);
	
protected:
	int head, torso, l_arm, r_arm, l_leg, r_leg;
	int m_x, m_y;
	std::string m_name;
};

#endif
