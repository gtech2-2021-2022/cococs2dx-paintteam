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

void Player::setPlayerSprite(string path, cocos2d::Vec2 size)
{
    playerSprite = Sprite::create(path);
}

cocos2d::Sprite* Player::getPlayerSprite()
{
    return playerSprite;
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

