#pragma once

#include <iostream>
#include <string>
#include "cocos2d.h"
#include "Utils.h"

class Monster;

class Weapon
{
public:

    Weapon(std::string name, int dammage);
    ~Weapon();
    std::string getName() { return _name; };
    int getDammage() { return _dammage; };
    void setWeaponSprite(const char* path, const cocos2d::Rect size) { weaponSprite = Utils::createSprite(path, size); };
    cocos2d::Sprite* getWeaponSprite() { return weaponSprite; };
    void setName(std::string name) { _name = name; };
    void setDammage(int _dmg) { _dammage = _dmg; };
    cocos2d::Rect getTextureRect();
    void setTake(bool _take) { take = _take; };
    bool isTake() { return take; };

protected:

    std::string _name;
    int _dammage;
    cocos2d::Sprite* weaponSprite = nullptr;
    bool take = false;
};

enum class Type
{
    HELMET,
    CHESTPLATE,
    LEGGING,
    BOOTS

};

class Armor
{
public:
    Armor(std::string name, int defense, Type type);
    ~Armor();
    std::string getName() { return _name; };
    int getDefense() { return _defense; };
    Type getType() { return _type; };

protected:

    std::string _name;
    Type _type;
    int _defense;
};

class Treasure
{
public:
    Treasure() { goldNumber = rand() % 6; }
    int getGoldNumber() { return goldNumber; }
    void setTreasureSprite(const char* path, const cocos2d::Rect size) { treasureSprite = Utils::createSprite(path, size); };
    cocos2d::Sprite* getTreasureSprite() { return treasureSprite; };
    bool isOpen() { return open; };
    void setOpen(bool _open) { open = _open; };
    void setGold(int _gold) { goldNumber = _gold; };

protected:
    std::string name = "Treasure";
    int goldNumber;
    cocos2d::Sprite* treasureSprite = nullptr;
    bool open = false;
};
