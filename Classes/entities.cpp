#include "entities.h"

using namespace std;
using namespace cocos2d;

Player::Player() : life(100) 
{
    _weapon = new Weapon("Stone Sword", 10);
}

void Player::receiveDammage(int nbDammage)
{
    life -= nbDammage;
    //On enlève le nombre de dégâts reçus à la vie du personnage

    if (life < 0) //Pour éviter d'avoir une vie négative
    {
        life = 0; //On met la vie à 0 (mort)
    }
}

int Player::getDefense()
{
    int _defense = 0;
    if (_helmet)
    {
        _defense += _helmet->getDefense();
    }
    if (_chestplate)
    {
        _defense += _chestplate->getDefense();
    }
    if (_legging)
    {
        _defense += _legging->getDefense();
    }
    if (_boots)
    {
        _defense += _boots->getDefense();
    }
    return _defense;
}

void Player::setArmor(Armor* armor)
{
    switch (armor->getType())
    {
    case Type::HELMET:
        _helmet = armor;
        break;
    case Type::CHESTPLATE:
        _chestplate = armor;
        break;
    case Type::LEGGING:
        _legging = armor;
        break;
    case Type::BOOTS:
        _boots = armor;
        break;
    };
}

void Player::createAnimation() {
    Animation* walkUpAnimation = Animation::create();
    for (int i = 0; i < 3; i++)
    {
        walkUpAnimation->addSpriteFrame(SpriteFrame::create("player/player.png", Rect(i * 32, 32, 32, 32)));
    }
    walkUpAnimation->setDelayPerUnit(0.25);
    AnimationCache::getInstance()->addAnimation(walkUpAnimation, "walkUpAnimation");

    Animation* walkDownAnimation = Animation::create();
    for (int i = 0; i < 3; i++)
    {
        walkDownAnimation->addSpriteFrame(SpriteFrame::create("player/player.png", Rect(i * 32, 0, 32, 32)));
    }
    walkDownAnimation->setDelayPerUnit(0.25);
    AnimationCache::getInstance()->addAnimation(walkDownAnimation, "walkDownAnimation");

    Animation* walkLeftAnimation = Animation::create();
    for (int i = 0; i < 3; i++)
    {
        walkLeftAnimation->addSpriteFrame(SpriteFrame::create("player/player.png", Rect(i * 32, 64, 32, 32)));
    }
    walkLeftAnimation->setDelayPerUnit(0.25);
    AnimationCache::getInstance()->addAnimation(walkLeftAnimation, "walkLeftAnimation");

    Animation* walkRightAnimation = Animation::create();
    for (int i = 0; i < 3; i++)
    {
        walkRightAnimation->addSpriteFrame(SpriteFrame::create("player/player.png", Rect(i * 32, 96, 32, 32)));
    }
    walkRightAnimation->setDelayPerUnit(0.25);
    AnimationCache::getInstance()->addAnimation(walkRightAnimation, "walkRightAnimation");

    Animation* idleUpAnimation = Animation::create();
    idleUpAnimation->addSpriteFrame(SpriteFrame::create("player/player.png", Rect(0, 32, 32, 32)));
    idleUpAnimation->setDelayPerUnit(1);
    AnimationCache::getInstance()->addAnimation(idleUpAnimation, "idleUpAnimation");

    Animation* idleDownAnimation = Animation::create();
    idleDownAnimation->addSpriteFrame(SpriteFrame::create("player/player.png", Rect(0, 0, 32, 32)));
    idleDownAnimation->setDelayPerUnit(1);
    AnimationCache::getInstance()->addAnimation(idleDownAnimation, "idleDownAnimation");

    Animation* idleLeftAnimation = Animation::create();
    idleLeftAnimation->addSpriteFrame(SpriteFrame::create("player/player.png", Rect(0, 64, 32, 32)));
    idleLeftAnimation->setDelayPerUnit(1);
    AnimationCache::getInstance()->addAnimation(idleLeftAnimation, "idleLeftAnimation");

    Animation* idleRightAnimation = Animation::create();
    idleRightAnimation->addSpriteFrame(SpriteFrame::create("player/player.png", Rect(0, 96, 32, 32)));
    idleRightAnimation->setDelayPerUnit(1);
    AnimationCache::getInstance()->addAnimation(idleRightAnimation, "idleRightAnimation");

}

void Player::updateAnimation(Sprite* _player, Direction direction) {
    _player->stopAllActions();
    Animation* anim;
    switch (direction)
    {
    case Direction::UP: {
        anim = AnimationCache::getInstance()->getAnimation("walkUpAnimation");
        break; }
    case Direction::DOWN: {
        anim = AnimationCache::getInstance()->getAnimation("walkDownAnimation");
        break; }
    case Direction::LEFT: {
        anim = AnimationCache::getInstance()->getAnimation("walkLeftAnimation");
        break; }
    case Direction::RIGHT: {
        anim = AnimationCache::getInstance()->getAnimation("walkRightAnimation");
        break; }
    }
    auto sf = anim->getFrames().at(0)->getSpriteFrame();
    auto action = Animate::create(anim);
    _player->runAction(RepeatForever::create(action));
}

void Player::becomeIdle() {
    playerSprite->stopAllActions();
    Animation* anim;
    if (direction == UP) {
        anim = AnimationCache::getInstance()->getAnimation("idleUpAnimation");
    }
    else if (direction == DOWN) {
        anim = AnimationCache::getInstance()->getAnimation("idleDownAnimation");
    }
    else if (direction == LEFT) {
        anim = AnimationCache::getInstance()->getAnimation("idleLeftAnimation");
    }
    else {
        anim = AnimationCache::getInstance()->getAnimation("idleRightAnimation");
    }
    // auto sf = anim->getFrames().at(0)->getSpriteFrame();
    auto action = Animate::create(anim);
    playerSprite->runAction(RepeatForever::create(action));
}

Monster::Monster()
{   
    int random;
    do
    {
        random = rand() % 4;
    } while (random == 0);
    if (random == 1) {
        _name = "Charmander";
        life = 50;
        dammage = 10;
    }
    else if (random == 2) {
        _name = "Charmeleon";
        life = 100;
        dammage = 20;
    }
    else if (random == 3) {
        _name = "Charizard";
        life = 150;
        dammage = 30;
    }
}

void Monster::receiveDammage(int nbDammage)
{
    life -= nbDammage;
    //On enlève le nombre de dégâts reçus à la vie du personnage

    if (life < 0) //Pour éviter d'avoir une vie négative
    {
        life = 0; //On met la vie à 0 (mort)
    }
}

void Monster::setMonsterSprite()
{
    if (_name == "Charmander")
    {
        monsterSprite = Utils::createSprite("pokemon/enemy.png", Rect(32, 0, 32, 32));
    }
    else if (_name == "Charmeleon") {
        monsterSprite = Utils::createSprite("pokemon/enemy.png", Rect(32, 128, 32, 32));
    }
    else if (_name == "Charizard") {
        monsterSprite = Utils::createSprite("pokemon/enemy.png", Rect(32, 256, 32, 32));
    }
}

cocos2d::Sprite* Monster::getMonsterSprite()
{
    return monsterSprite;
}

