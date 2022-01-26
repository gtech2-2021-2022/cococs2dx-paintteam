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

void Player::setPlayerSprite(string path, Rect size)
{
    playerSprite = Sprite::create(path, size);
}

cocos2d::Sprite* Player::getPlayerSprite()
{
    return playerSprite;
}

void Player::createAnimation() {
    Animation* walkUpAnimation = Animation::create();
    for (int i = 1; i < 3; i++)
    {
        walkUpAnimation->addSpriteFrame(SpriteFrame::create("player/player.png", Rect(i * 32, 32, 32, 32)));
    }
    walkUpAnimation->setDelayPerUnit(0.25);
    AnimationCache::getInstance()->addAnimation(walkUpAnimation, "walkUpAnimation");

    Animation* walkDownAnimation = Animation::create();
    for (int i = 1; i < 3; i++)
    {
        walkDownAnimation->addSpriteFrame(SpriteFrame::create("player/player.png", Rect(i * 32, 0, 32, 32)));
    }
    walkDownAnimation->setDelayPerUnit(0.25);
    AnimationCache::getInstance()->addAnimation(walkDownAnimation, "walkDownAnimation");

    Animation* walkLeftAnimation = Animation::create();
    for (int i = 1; i < 3; i++)
    {
        walkLeftAnimation->addSpriteFrame(SpriteFrame::create("player/player.png", Rect(i * 32, 64, 32, 32)));
    }
    walkLeftAnimation->setDelayPerUnit(0.25);
    AnimationCache::getInstance()->addAnimation(walkLeftAnimation, "walkLeftAnimation");

    Animation* walkRightAnimation = Animation::create();
    for (int i = 1; i < 3; i++)
    {
        walkRightAnimation->addSpriteFrame(SpriteFrame::create("player/player.png", Rect(i * 32, 96, 32, 32)));
    }
    walkRightAnimation->setDelayPerUnit(0.25);
    AnimationCache::getInstance()->addAnimation(walkRightAnimation, "walkRightAnimation");
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

Monster::Monster()
{   
    int random;
    do
    {
        random = rand() % 4;
    } while (random == 0);
    if (random == 1) {
        _name = "zombie";
        life = 50;
        dammage = 10;
    }
    else if (random == 2) {
        _name = "skeleton";
        life = 100;
        dammage = 20;
    }
    else if (random == 3) {
        _name = "enderman";
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

void Monster::setMonsterSprite(string path, Rect size)
{
    monsterSprite = Sprite::create(path, size);
}

cocos2d::Sprite* Monster::getMonsterSprite()
{
    return monsterSprite;
}

