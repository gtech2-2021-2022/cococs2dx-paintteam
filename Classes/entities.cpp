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
    AnimationCache::getInstance()->addAnimation(walkUpAnimation, "playerWalkUpAnimation");

    Animation* walkDownAnimation = Animation::create();
    for (int i = 0; i < 3; i++)
    {
        walkDownAnimation->addSpriteFrame(SpriteFrame::create("player/player.png", Rect(i * 32, 0, 32, 32)));
    }
    walkDownAnimation->setDelayPerUnit(0.25);
    AnimationCache::getInstance()->addAnimation(walkDownAnimation, "playerWalkDownAnimation");

    Animation* walkLeftAnimation = Animation::create();
    for (int i = 0; i < 3; i++)
    {
        walkLeftAnimation->addSpriteFrame(SpriteFrame::create("player/player.png", Rect(i * 32, 64, 32, 32)));
    }
    walkLeftAnimation->setDelayPerUnit(0.25);
    AnimationCache::getInstance()->addAnimation(walkLeftAnimation, "playerWalkLeftAnimation");

    Animation* walkRightAnimation = Animation::create();
    for (int i = 0; i < 3; i++)
    {
        walkRightAnimation->addSpriteFrame(SpriteFrame::create("player/player.png", Rect(i * 32, 96, 32, 32)));
    }
    walkRightAnimation->setDelayPerUnit(0.25);
    AnimationCache::getInstance()->addAnimation(walkRightAnimation, "playerWalkRightAnimation");

    Animation* idleUpAnimation = Animation::create();
    idleUpAnimation->addSpriteFrame(SpriteFrame::create("player/player.png", Rect(0, 32, 32, 32)));
    idleUpAnimation->setDelayPerUnit(1);
    AnimationCache::getInstance()->addAnimation(idleUpAnimation, "playerIdleUpAnimation");

    Animation* idleDownAnimation = Animation::create();
    idleDownAnimation->addSpriteFrame(SpriteFrame::create("player/player.png", Rect(0, 0, 32, 32)));
    idleDownAnimation->setDelayPerUnit(1);
    AnimationCache::getInstance()->addAnimation(idleDownAnimation, "playerIdleDownAnimation");

    Animation* idleLeftAnimation = Animation::create();
    idleLeftAnimation->addSpriteFrame(SpriteFrame::create("player/player.png", Rect(0, 64, 32, 32)));
    idleLeftAnimation->setDelayPerUnit(1);
    AnimationCache::getInstance()->addAnimation(idleLeftAnimation, "playerIdleLeftAnimation");

    Animation* idleRightAnimation = Animation::create();
    idleRightAnimation->addSpriteFrame(SpriteFrame::create("player/player.png", Rect(0, 96, 32, 32)));
    idleRightAnimation->setDelayPerUnit(1);
    AnimationCache::getInstance()->addAnimation(idleRightAnimation, "playerIdleRightAnimation");

}

void Player::updateAnimation(Sprite* _player, Direction direction) {
    _player->stopAllActions();
    Animation* anim;
    switch (direction)
    {
    case Direction::UP: {
        anim = AnimationCache::getInstance()->getAnimation("playerWalkUpAnimation");
        break; }
    case Direction::DOWN: {
        anim = AnimationCache::getInstance()->getAnimation("playerWalkDownAnimation");
        break; }
    case Direction::LEFT: {
        anim = AnimationCache::getInstance()->getAnimation("playerWalkLeftAnimation");
        break; }
    case Direction::RIGHT: {
        anim = AnimationCache::getInstance()->getAnimation("playerWalkRightAnimation");
        break; }
    }
    //auto sf = anim->getFrames().at(0)->getSpriteFrame();
    auto action = Animate::create(anim);
    _player->runAction(RepeatForever::create(action));
}

void Player::becomeIdle() {
    playerSprite->stopAllActions();
    Animation* anim;
    if (direction == UP) {
        anim = AnimationCache::getInstance()->getAnimation("playerIdleUpAnimation");
    }
    else if (direction == DOWN) {
        anim = AnimationCache::getInstance()->getAnimation("playerIdleDownAnimation");
    }
    else if (direction == LEFT) {
        anim = AnimationCache::getInstance()->getAnimation("playerIdleLeftAnimation");
    }
    else {
        anim = AnimationCache::getInstance()->getAnimation("playerIdleRightAnimation");
    }
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

void Monster::createAnimation()
{
    if (_name == "Charmander")
    {
        Animation* walkUpAnimation1 = Animation::create();
        for (int i = 0; i < 3; i++)
        {
            walkUpAnimation1->addSpriteFrame(SpriteFrame::create("pokemon/enemy.png", Rect(i * 32, 32, 32, 32)));
        }
        walkUpAnimation1->setDelayPerUnit(0.25);
        AnimationCache::getInstance()->addAnimation(walkUpAnimation1, "charmanderWalkUpAnimation");

        Animation* walkDownAnimation1 = Animation::create();
        for (int i = 0; i < 3; i++)
        {
            walkDownAnimation1->addSpriteFrame(SpriteFrame::create("pokemon/enemy.png", Rect(i * 32, 0, 32, 32)));
        }
        walkDownAnimation1->setDelayPerUnit(0.25);
        AnimationCache::getInstance()->addAnimation(walkDownAnimation1, "charmanderWalkDownAnimation");

        Animation* walkLeftAnimation1 = Animation::create();
        for (int i = 0; i < 3; i++)
        {
            walkLeftAnimation1->addSpriteFrame(SpriteFrame::create("pokemon/enemy.png", Rect(i * 32, 64, 32, 32)));
        }
        walkLeftAnimation1->setDelayPerUnit(0.25);
        AnimationCache::getInstance()->addAnimation(walkLeftAnimation1, "charmanderWalkLeftAnimation");

        Animation* walkRightAnimation1 = Animation::create();
        for (int i = 0; i < 3; i++)
        {
            walkRightAnimation1->addSpriteFrame(SpriteFrame::create("pokemon/enemy.png", Rect(i * 32, 96, 32, 32)));
        }
        walkRightAnimation1->setDelayPerUnit(0.25);
        AnimationCache::getInstance()->addAnimation(walkRightAnimation1, "charmanderWalkRightAnimation");

        Animation* idleUpAnimation1 = Animation::create();
        idleUpAnimation1->addSpriteFrame(SpriteFrame::create("pokemon/enemy.png", Rect(32, 32, 32, 32)));
        idleUpAnimation1->setDelayPerUnit(1);
        AnimationCache::getInstance()->addAnimation(idleUpAnimation1, "charmanderIdleUpAnimation");

        Animation* idleDownAnimation1 = Animation::create();
        idleDownAnimation1->addSpriteFrame(SpriteFrame::create("pokemon/enemy.png", Rect(32, 0, 32, 32)));
        idleDownAnimation1->setDelayPerUnit(1);
        AnimationCache::getInstance()->addAnimation(idleDownAnimation1, "charmanderIdleDownAnimation");

        Animation* idleLeftAnimation1 = Animation::create();
        idleLeftAnimation1->addSpriteFrame(SpriteFrame::create("pokemon/enemy.png", Rect(32, 64, 32, 32)));
        idleLeftAnimation1->setDelayPerUnit(1);
        AnimationCache::getInstance()->addAnimation(idleLeftAnimation1, "charmanderIdleLeftAnimation");

        Animation* idleRightAnimation1 = Animation::create();
        idleRightAnimation1->addSpriteFrame(SpriteFrame::create("pokemon/enemy.png", Rect(32, 96, 32, 32)));
        idleRightAnimation1->setDelayPerUnit(1);
        AnimationCache::getInstance()->addAnimation(idleRightAnimation1, "charmanderIdleRightAnimation");
    }
    else if (_name == "Charmeleon") {
        Animation* walkUpAnimation2 = Animation::create();
        for (int i = 0; i < 3; i++)
        {
            walkUpAnimation2->addSpriteFrame(SpriteFrame::create("pokemon/enemy.png", Rect(i * 32, 160, 32, 32)));
        }
        walkUpAnimation2->setDelayPerUnit(0.25);
        AnimationCache::getInstance()->addAnimation(walkUpAnimation2, "charmeleonWalkUpAnimation");

        Animation* walkDownAnimation2 = Animation::create();
        for (int i = 0; i < 3; i++)
        {
            walkDownAnimation2->addSpriteFrame(SpriteFrame::create("pokemon/enemy.png", Rect(i * 32, 128, 32, 32)));
        }
        walkDownAnimation2->setDelayPerUnit(0.25);
        AnimationCache::getInstance()->addAnimation(walkDownAnimation2, "charmeleonWalkDownAnimation");

        Animation* walkLeftAnimation2 = Animation::create();
        for (int i = 0; i < 3; i++)
        {
            walkLeftAnimation2->addSpriteFrame(SpriteFrame::create("pokemon/enemy.png", Rect(i * 32, 192, 32, 32)));
        }
        walkLeftAnimation2->setDelayPerUnit(0.25);
        AnimationCache::getInstance()->addAnimation(walkLeftAnimation2, "charmeleonWalkLeftAnimation");

        Animation* walkRightAnimation2 = Animation::create();
        for (int i = 0; i < 3; i++)
        {
            walkRightAnimation2->addSpriteFrame(SpriteFrame::create("pokemon/enemy.png", Rect(i * 32, 224, 32, 32)));
        }
        walkRightAnimation2->setDelayPerUnit(0.25);
        AnimationCache::getInstance()->addAnimation(walkRightAnimation2, "charmeleonWalkRightAnimation");

        Animation* idleUpAnimation2 = Animation::create();
        idleUpAnimation2->addSpriteFrame(SpriteFrame::create("pokemon/enemy.png", Rect(32, 160, 32, 32)));
        idleUpAnimation2->setDelayPerUnit(1);
        AnimationCache::getInstance()->addAnimation(idleUpAnimation2, "charmeleonIdleUpAnimation");

        Animation* idleDownAnimation2 = Animation::create();
        idleDownAnimation2->addSpriteFrame(SpriteFrame::create("pokemon/enemy.png", Rect(32, 128, 32, 32)));
        idleDownAnimation2->setDelayPerUnit(1);
        AnimationCache::getInstance()->addAnimation(idleDownAnimation2, "charmeleonIdleDownAnimation");

        Animation* idleLeftAnimation2 = Animation::create();
        idleLeftAnimation2->addSpriteFrame(SpriteFrame::create("pokemon/enemy.png", Rect(32, 192, 32, 32)));
        idleLeftAnimation2->setDelayPerUnit(1);
        AnimationCache::getInstance()->addAnimation(idleLeftAnimation2, "charmeleonIdleLeftAnimation");

        Animation* idleRightAnimation2 = Animation::create();
        idleRightAnimation2->addSpriteFrame(SpriteFrame::create("pokemon/enemy.png", Rect(32, 224, 32, 32)));
        idleRightAnimation2->setDelayPerUnit(1);
        AnimationCache::getInstance()->addAnimation(idleRightAnimation2, "charmeleonIdleRightAnimation");
    }
    else if (_name == "Charizard") {
    Animation* walkUpAnimation3 = Animation::create();
    for (int i = 0; i < 3; i++)
    {
        walkUpAnimation3->addSpriteFrame(SpriteFrame::create("pokemon/enemy.png", Rect(i * 32, 288, 32, 32)));
    }
    walkUpAnimation3->setDelayPerUnit(0.25);
    AnimationCache::getInstance()->addAnimation(walkUpAnimation3, "charizardWalkUpAnimation");

    Animation* walkDownAnimation3 = Animation::create();
    for (int i = 0; i < 3; i++)
    {
        walkDownAnimation3->addSpriteFrame(SpriteFrame::create("pokemon/enemy.png", Rect(i * 32, 256, 32, 32)));
    }
    walkDownAnimation3->setDelayPerUnit(0.25);
    AnimationCache::getInstance()->addAnimation(walkDownAnimation3, "charizardWalkDownAnimation");

    Animation* walkLeftAnimation3 = Animation::create();
    for (int i = 0; i < 3; i++)
    {
        walkLeftAnimation3->addSpriteFrame(SpriteFrame::create("pokemon/enemy.png", Rect(i * 32, 320, 32, 32)));
    }
    walkLeftAnimation3->setDelayPerUnit(0.25);
    AnimationCache::getInstance()->addAnimation(walkLeftAnimation3, "charizardWalkLeftAnimation");

    Animation* walkRightAnimation3 = Animation::create();
    for (int i = 0; i < 3; i++)
    {
        walkRightAnimation3->addSpriteFrame(SpriteFrame::create("pokemon/enemy.png", Rect(i * 32, 352, 32, 32)));
    }
    walkRightAnimation3->setDelayPerUnit(0.25);
    AnimationCache::getInstance()->addAnimation(walkRightAnimation3, "charizardWalkRightAnimation");

    Animation* idleUpAnimation3 = Animation::create();
    idleUpAnimation3->addSpriteFrame(SpriteFrame::create("pokemon/enemy.png", Rect(32, 288, 32, 32)));
    idleUpAnimation3->setDelayPerUnit(1);
    AnimationCache::getInstance()->addAnimation(idleUpAnimation3, "charizardIdleUpAnimation");

    Animation* idleDownAnimation3 = Animation::create();
    idleDownAnimation3->addSpriteFrame(SpriteFrame::create("pokemon/enemy.png", Rect(32, 256, 32, 32)));
    idleDownAnimation3->setDelayPerUnit(1);
    AnimationCache::getInstance()->addAnimation(idleDownAnimation3, "charizardIdleDownAnimation");

    Animation* idleLeftAnimation3 = Animation::create();
    idleLeftAnimation3->addSpriteFrame(SpriteFrame::create("pokemon/enemy.png", Rect(32, 320, 32, 32)));
    idleLeftAnimation3->setDelayPerUnit(1);
    AnimationCache::getInstance()->addAnimation(idleLeftAnimation3, "charizardIdleLeftAnimation");

    Animation* idleRightAnimation3 = Animation::create();
    idleRightAnimation3->addSpriteFrame(SpriteFrame::create("pokemon/enemy.png", Rect(32, 352, 32, 32)));
    idleRightAnimation3->setDelayPerUnit(1);
    AnimationCache::getInstance()->addAnimation(idleRightAnimation3, "charizardIdleRightAnimation");
    }
}

void Monster::updateAnimation(cocos2d::Sprite* _pokemon, Direction direction)
{
    _pokemon->stopAllActions();
    Animation* anim;
    if (_name == "Charmander")
    {
        switch (direction)
        {
        case Direction::UP: {
            anim = AnimationCache::getInstance()->getAnimation("charmanderWalkUpAnimation");
            break; }
        case Direction::DOWN: {
            anim = AnimationCache::getInstance()->getAnimation("charmanderWalkDownAnimation");
            break; }
        case Direction::LEFT: {
            anim = AnimationCache::getInstance()->getAnimation("charmanderWalkLeftAnimation");
            break; }
        case Direction::RIGHT: {
            anim = AnimationCache::getInstance()->getAnimation("charmanderWalkRightAnimation");
            break; }
        }
    }
    else if (_name == "Charmeleon") {
        switch (direction)
        {
        case Direction::UP: {
            anim = AnimationCache::getInstance()->getAnimation("charmeleonWalkUpAnimation");
            break; }
        case Direction::DOWN: {
            anim = AnimationCache::getInstance()->getAnimation("charmeleonWalkDownAnimation");
            break; }
        case Direction::LEFT: {
            anim = AnimationCache::getInstance()->getAnimation("charmeleonWalkLeftAnimation");
            break; }
        case Direction::RIGHT: {
            anim = AnimationCache::getInstance()->getAnimation("charmeleonWalkRightAnimation");
            break; }
        }
    }
    else if (_name == "Charizard") {
        switch (direction)
        {
        case Direction::UP: {
            anim = AnimationCache::getInstance()->getAnimation("charizardWalkUpAnimation");
            break; }
        case Direction::DOWN: {
            anim = AnimationCache::getInstance()->getAnimation("charizardWalkDownAnimation");
            break; }
        case Direction::LEFT: {
            anim = AnimationCache::getInstance()->getAnimation("charizardWalkLeftAnimation");
            break; }
        case Direction::RIGHT: {
            anim = AnimationCache::getInstance()->getAnimation("charizardWalkRightAnimation");
            break; }
        }
    }
    auto sf = anim->getFrames().at(0)->getSpriteFrame();
    auto action = Animate::create(anim);
    _pokemon->runAction(RepeatForever::create(action));
}

void Monster::becomeIdle()
{
    monsterSprite->stopAllActions();
    Animation* anim;
    if (_name == "Charmander")
    {
        if (direction == UP) {
            anim = AnimationCache::getInstance()->getAnimation("charmanderIdleUpAnimation");
        }
        else if (direction == DOWN) {
            anim = AnimationCache::getInstance()->getAnimation("charmanderIdleDownAnimation");
        }
        else if (direction == LEFT) {
            anim = AnimationCache::getInstance()->getAnimation("charmanderIdleLeftAnimation");
        }
        else {
            anim = AnimationCache::getInstance()->getAnimation("charmanderIdleRightAnimation");
        }
    }
    else if (_name == "Charmeleon") {
        if (direction == UP) {
            anim = AnimationCache::getInstance()->getAnimation("charmeleonIdleUpAnimation");
        }
        else if (direction == DOWN) {
            anim = AnimationCache::getInstance()->getAnimation("charmeleonIdleDownAnimation");
        }
        else if (direction == LEFT) {
            anim = AnimationCache::getInstance()->getAnimation("charmeleonIdleLeftAnimation");
        }
        else {
            anim = AnimationCache::getInstance()->getAnimation("charmeleonIdleRightAnimation");
        }
    }
    else {
        if (direction == UP) {
            anim = AnimationCache::getInstance()->getAnimation("charizardIdleUpAnimation");
        }
        else if (direction == DOWN) {
            anim = AnimationCache::getInstance()->getAnimation("charizardIdleDownAnimation");
        }
        else if (direction == LEFT) {
            anim = AnimationCache::getInstance()->getAnimation("charizardIdleLeftAnimation");
        }
        else {
            anim = AnimationCache::getInstance()->getAnimation("charizardIdleRightAnimation");
        }
    }
    auto action = Animate::create(anim);
    monsterSprite->runAction(RepeatForever::create(action));
}

