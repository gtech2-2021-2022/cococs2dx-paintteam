#pragma once

#include <iostream>
#include <string>

class Monster;

class Weapon
{
public:

    Weapon(std::string name, int dammage);
    ~Weapon();
    std::string getName() { return _name; };
    int getDammage() { return _dammage; };

protected:

    std::string _name;
    int _dammage;
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

protected:
    std::string name = "Treasure";
    int goldNumber;
};
