#include "Utils.h"
#include "entities.h"

using namespace cocos2d;

// Print useful error message instead of segfaulting when files are not there.
void Utils::problemLoading (const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}


Sprite* Utils::createSprite(const char* fileName) {
	auto sprite = Sprite::create(fileName);
	if (sprite == nullptr)
	{
		problemLoading(fileName);
	}
	return sprite;
}

cocos2d::Sprite* Utils::createSprite(const char* fileName,const cocos2d::Rect size) {
	Sprite* sprite = Sprite::create(fileName, size);
	if (sprite == nullptr)
	{
		problemLoading(fileName);
	}
	return sprite;
}