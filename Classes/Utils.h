#pragma once
//#ifndef __UTILS_H__
//#define __UTILS_H__

#include "cocos2d.h"
#include <iostream>

class Utils
{
	
	public:
		cocos2d::Animation* createAnimation(std::string file, int size, int frames);
		cocos2d::Sprite* createSprite(const char* fileName);
};

//#endif





