#pragma once
//#ifndef __UTILS_H__
//#define __UTILS_H__

#include "cocos2d.h"
#include <iostream>


class Utils
{
	
	public:
		static cocos2d::Sprite* createSprite(const char* fileName);
		static cocos2d::Sprite* createSprite(const char* fileName,const cocos2d::Rect size);
		static void problemLoading(const char* filename);
};

//#endif





