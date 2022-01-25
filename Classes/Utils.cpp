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
}