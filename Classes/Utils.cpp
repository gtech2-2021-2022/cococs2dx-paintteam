#include "Utils.h"
#include "entities.h"

using namespace cocos2d;

static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}


Sprite* Utils::createSprite(const char* fileName) {
	auto sprite = Sprite::create("lvl/Map3.png");
	if (sprite == nullptr)
	{
		problemLoading("'lvl/Map3.png'");
	}
	return sprite;
}