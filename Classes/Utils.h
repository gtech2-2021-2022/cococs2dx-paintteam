#pragma once
//#ifndef __UTILS_H__
//#define __UTILS_H__

#include "cocos2d.h"
#include <iostream>


class Utils
{
	
	public:
		struct ElementDetails {
			cocos2d::Rect rect;
			float ratio;
			int32_t ZOrder;
			std::string name;
		};

		static cocos2d::Sprite* createSprite(const char* fileName);
		static cocos2d::Sprite* createSprite(const char* fileName,const cocos2d::Rect size);
		static void problemLoading(const char* filename);
		static cocos2d::Sprite* createElement(Utils::ElementDetails& elementInfo, cocos2d::Vec2 position);
		static cocos2d::Sprite* createElementWithTag(Utils::ElementDetails& elementInfo, cocos2d::Vec2 position, int tagNumber);
		static cocos2d::Sprite* createElement(Utils::ElementDetails& elementInfo);
		static cocos2d::Sprite* createElementWithTag(Utils::ElementDetails& elementInfo, int tagNumber);
		static cocos2d::Sprite* cloneSprite(cocos2d::Sprite* spriteToClone);
		static cocos2d::Sprite* cloneSprite(cocos2d::Sprite* spriteToClone, cocos2d::Vec2 position);
		
};

//#endif





