#include "item.h"
#include "entities.h"

using namespace std;

Weapon::Weapon(std::string name, int dammage)
{
    _name = name;
    _dammage = dammage;
}

Weapon::~Weapon() {}

Armor::Armor(std::string name, int defense, Type type)
{
    _name = name;
    _defense = defense;
    _type = type;
}

Armor::~Armor() {}
