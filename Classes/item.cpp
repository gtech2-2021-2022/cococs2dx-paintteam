#include "item.h"
#include "entities.h"

using namespace std;
using namespace cocos2d;

Weapon::Weapon(std::string name, int dammage)
{
    _name = name;
    _dammage = dammage;
}

Rect Weapon::getTextureRect() {
    if (_name == "Squirtle")
    {
        return Rect(0, 0, 26, 26);
    }
    else if (_name == "Wartortle") {
        return Rect(26, 0, 26, 26);
    }
    else if (_name == "Blastoise") {
        return Rect(52, 0, 26, 26);
    }
}

Weapon::~Weapon() {}

Armor::Armor(std::string name, int defense, Type type)
{
    _name = name;
    _defense = defense;
    _type = type;
}

Armor::~Armor() {}
