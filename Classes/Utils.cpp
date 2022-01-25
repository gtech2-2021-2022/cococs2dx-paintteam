#include "Utils.h"

using namespace cocos2d;

void Utils::createAnimation() {
	Animation* idleAnimation = Animation::create();
	for (int i = 0; i < 12; i++)
	{
		idleAnimation->addSpriteFrame(SpriteFrame::create("player/player.png", Rect(i * 32, 0, 32, 32)));
	}
	idleAnimation->setDelayPerUnit(0.2);
	AnimationCache::getInstance()->addAnimation(idleAnimation, "idleAnimation");

	Animation* walkDownAnimation = Animation::create();
	for (int i = 0; i < 24; i++)
	{
		walkDownAnimation->addSpriteFrame(SpriteFrame::create("player/player.png", Rect(i * 32, 32, 32, 32)));
	}
	walkDownAnimation->setDelayPerUnit(0.03);
	AnimationCache::getInstance()->addAnimation(walkDownAnimation, "walkDownAnimation");
}

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