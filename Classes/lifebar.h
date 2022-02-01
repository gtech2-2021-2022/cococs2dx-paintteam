#pragma once

#include <iostream>
#include <string>
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class LifeBar
{
public:
	LifeBar(int _life);
	cocos2d::ui::LoadingBar* getLifeBar() { return bar; };
	void updateLife(int dammage);
	int getLife() { return life; };

protected:
	float lifeMax = 0;
	int life = 0;
	cocos2d::ui::LoadingBar* bar;
};