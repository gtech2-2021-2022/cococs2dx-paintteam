#pragma once

#include <iostream>
#include <string>
#include "cocos2d.h"

class LifeBar
{
public:
	LifeBar(int _life);
	cocos2d::ProgressTimer* getLifeBar() { return bar; };
	void updateLife(int dammage);
	int getLife() { return life; };

protected:
	float lifeMax = 0;
	int life = 0;
	cocos2d::ProgressTimer* bar;
};