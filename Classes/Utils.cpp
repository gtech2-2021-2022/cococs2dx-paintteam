#include "Utils.h"

using namespace cocos2d;

Animation* Utils::createAnimation(std::string file, int size, int frames) {
	/*
	Utilisation AnimationCache

	Au chargement

	Animation* anim = Animation::create();
	for (...)
		anim->addSpriteFrame(...);
	anim->setDelayPerUnit(...);
	AnimationCache::getInstance()->addAnimation(anim, "mon_anim");


	et plus loin, à l'utilisation:

	auto anim_res = AnimationCache::getInstance()->getAnimation("mon_anim");
	auto sf = anim_res->getFrames().at(0)->getSpriteFrame();
	auto sprite = Sprite::createWithSpriteFrame(sf);
	auto action = Animate::create(anim_res);
	sprite->runAction(action);*/


	Animation* animation = Animation::create();
	for (int x = 0; x < frames; x++) {
		animation->addSpriteFrame(SpriteFrame::create(file, Rect(x * size, 0, size, size)));
	}
	return animation;
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