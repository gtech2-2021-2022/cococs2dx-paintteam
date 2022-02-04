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

Sprite* Utils::createSprite(const char* fileName,const cocos2d::Rect size) {
	Sprite* sprite = Sprite::create(fileName, size);
	if (sprite == nullptr)
	{
		problemLoading(fileName);
	}
	return sprite;
}


Sprite* Utils::createElement(Utils::ElementDetails& elementInfo) {
	Sprite* element = Utils::createSprite("mapElement.png", elementInfo.rect);
	element->setScale(elementInfo.ratio);
	element->setAnchorPoint(Vec2(0.5, 0.5));
	element->setLocalZOrder(elementInfo.ZOrder);
	element->setName(elementInfo.name);
	return element;
}

Sprite* Utils::createElement(Utils::ElementDetails& elementInfo, Vec2 position) {
	Sprite* element = Utils::createSprite("mapElement.png", elementInfo.rect);
	element->setScale(elementInfo.ratio);
	element->setAnchorPoint(Vec2(0.5, 0.5));
	element->setLocalZOrder(elementInfo.ZOrder);
	element->setName(elementInfo.name);
	element->setPosition(position);
	return element;
}

Sprite* Utils::createElementWithTag(Utils::ElementDetails& const elementInfo, int tagNumber) {
	Sprite* element = Utils::createSprite("mapElement.png", elementInfo.rect);
	element->setScale(elementInfo.ratio);
	element->setAnchorPoint(Vec2(0.5, 0.5));
	element->setLocalZOrder(elementInfo.ZOrder);
	element->setName(elementInfo.name);
	element->setTag(tagNumber);
	return element;
}

Sprite* Utils::createElementWithTag(Utils::ElementDetails& elementInfo, Vec2 position, int tagNumber) {
	Sprite* element = Utils::createSprite("mapElement.png", elementInfo.rect);
	element->setScale(elementInfo.ratio);
	element->setAnchorPoint(Vec2(0.5, 0.5));
	element->setLocalZOrder(elementInfo.ZOrder);
	element->setName(elementInfo.name);
	element->setPosition(position);
	element->setTag(tagNumber);
	return element;
}

Sprite* Utils:: cloneSprite(Sprite* spriteToClone)
{
	Sprite* clonedSprite = Sprite::createWithTexture(spriteToClone->getTexture());
	clonedSprite->setScale(spriteToClone->getScale());
	clonedSprite->setAnchorPoint(spriteToClone->getAnchorPoint());
	clonedSprite->setLocalZOrder(spriteToClone->getLocalZOrder());
	return clonedSprite;
}

Sprite* Utils::cloneSprite(Sprite* spriteToClone, Vec2 position) {
	Sprite* clonedSprite = Sprite::createWithTexture(spriteToClone->getTexture());
	clonedSprite->setScale(spriteToClone->getScale());
	clonedSprite->setAnchorPoint(spriteToClone->getAnchorPoint());
	clonedSprite->setLocalZOrder(spriteToClone->getLocalZOrder());
	clonedSprite->setPosition(position);
	return clonedSprite;
}
