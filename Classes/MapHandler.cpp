#include "MapHandler.h"

MapHandler::MapHandler()
{
	for (int y = 0; y < size; y++)
	{
		_room.push_back(std::vector<Room>());
		for (int x = 0; x < size; x++)
		{
			_room[y].push_back(Room());
		}
	}
	_room[0][0].link(nullptr, &_room[1][0], nullptr, nullptr);
	_room[0][1].link(nullptr, &_room[1][1], &_room[0][2], nullptr);
	_room[0][2].link(nullptr, nullptr, nullptr, &_room[0][1]);
	_room[0][3].link(nullptr, &_room[1][3], &_room[0][4], nullptr);
	_room[0][4].link(nullptr, &_room[1][4], nullptr, &_room[0][3]);
	_room[1][0].link(&_room[0][0], &_room[2][0], nullptr, nullptr);
	_room[1][1].link(&_room[0][1], nullptr, &_room[1][2], nullptr);
	_room[1][2].link(nullptr, &_room[2][2], &_room[1][3], &_room[1][1]);
	_room[1][3].link(&_room[0][3], &_room[2][3], nullptr, &_room[1][2]);
	_room[1][4].link(&_room[0][4], nullptr, nullptr, nullptr);
	_room[2][0].link(&_room[1][0], nullptr, &_room[2][1], nullptr);
	_room[2][1].link(nullptr, &_room[3][1], &_room[2][2], &_room[2][0]);
	_room[2][2].link(&_room[1][2], nullptr, nullptr, &_room[2][1]);
	_room[2][3].link(&_room[1][3], &_room[3][3], &_room[2][4], nullptr);
	_room[2][4].link(nullptr, nullptr, nullptr, &_room[2][3]);
	_room[3][1].link(&_room[2][1], &_room[4][1], nullptr, nullptr);
	_room[3][2].link(nullptr, &_room[4][2], &_room[3][3], nullptr);
	_room[3][3].link(&_room[2][3], nullptr, &_room[3][4], &_room[3][2]);
	_room[3][4].link(nullptr, nullptr, nullptr, &_room[3][3]);
	_room[4][0].link(nullptr, nullptr, &_room[4][1], nullptr);
	_room[4][1].link(&_room[3][1], nullptr, nullptr, &_room[4][0]);
	_room[4][2].link(&_room[3][2], nullptr, &_room[4][3], nullptr);
	_room[4][3].link(nullptr, nullptr, &_room[4][4], &_room[4][2]);
	_room[4][4].link(nullptr, nullptr, nullptr, &_room[4][3]);
	do
	{
		playerX = rand() % 5;
		playerY = rand() % 5;
	} while (_room[playerY][playerX].isRoomExisting() != true);
	_weapons.push_back(Weapon("Golden Sword", 20));
	_weapons.push_back(Weapon("Iron Sword", 30));
	_weapons.push_back(Weapon("Diamond Sword", 40));
	_armors.push_back(Armor("Golden Helmet", 2, Type::HELMET));
	_armors.push_back(Armor("Golden Chestplate", 2, Type::CHESTPLATE));
	_armors.push_back(Armor("Golden Legging", 2, Type::LEGGING));
	_armors.push_back(Armor("Golden Boots", 2, Type::BOOTS));
	_armors.push_back(Armor("Iron Helmet", 4, Type::HELMET));
	_armors.push_back(Armor("Iron Chestplate", 4, Type::CHESTPLATE));
	_armors.push_back(Armor("Iron Legging", 4, Type::LEGGING));
	_armors.push_back(Armor("Iron Boots", 4, Type::BOOTS));
	_armors.push_back(Armor("Diamond Helmet", 6, Type::HELMET));
	_armors.push_back(Armor("Diamond Chestplate", 6, Type::CHESTPLATE));
	_armors.push_back(Armor("Diamond Legging", 6, Type::LEGGING));
	_armors.push_back(Armor("Diamond Boots", 6, Type::BOOTS));
	int i = 0;
	int j = 0;
	for (int y = 0; y < size; y++)
	{
		for (int x = 0; x < size; x++)
		{
			if (y != playerY && x != playerX)
			{
				if (!(_weapons.empty()) && i < 3)
				{
					_room[y][x].generateWeapon(&_weapons[i]);
					if (_room[y][x].hasWeapon())
					{
						i++;
					}

				}
				if (!(_room[y][x].hasWeapon()) && !(_armors.empty()) && j < 12)
				{
					_room[y][x].generateArmor(&_armors[j]);
					j++;
				}
				if (!(_room[y][x].hasWeapon()) && !(_room[y][x].hasHelmet()) && !(_room[y][x].hasChestplate()) && !(_room[y][x].hasLegging()) && !(_room[y][x].hasBoots()))
				{
					_room[y][x].generateMonster();
				}
				if (!(_room[y][x].hasWeapon()) && !(_room[y][x].hasHelmet()) && !(_room[y][x].hasChestplate()) && !(_room[y][x].hasLegging()) && !(_room[y][x].hasBoots()) && !(_room[y][x].hasMonster()))
				{
					_room[y][x].generateTreasure();
				}
			}
		}
	}
}



bool MapHandler::win()
{
	int i = 0;
	for (int y = 0; y < size; y++)
	{
		for (int x = 0; x < size; x++)
		{
			if (!(_room[y][x].hasMonster()))
			{
				if (!(_room[y][x].hasTreasure()))
				{
					i++;
				}
			}
		}
	}
	if (i == 25)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Room::link(Room* n, Room* s, Room* e, Room* w)
{
	if (n)
	{
		setExist();
		north = n;
		n->setExist();
	}
	if (s)
	{
		setExist();
		south = s;
		s->setExist();
	}
	if (e)
	{
		setExist();
		east = e;
		e->setExist();
	}
	if (w)
	{
		setExist();
		west = w;
		w->setExist();
	}
}

void Room::generateTreasure()
{
	if (rand() % 5 == 2)
	{
		treasure = new Treasure();
	}
}

int Room::getTreasureGold()
{
	return treasure->getGoldNumber();
}

void Room::takeTreasure(Player &player)
{	
	player.setGold(treasure->getGoldNumber());
	deleteTreasure();
}

void Room::deleteTreasure()
{
	delete treasure;
	treasure = nullptr;
}

void Room::generateWeapon(Weapon *weapon)
{
	if (rand() % 6 == 1)
	{
		_weapon = weapon;
	}
}

std::string Room::getWeaponName()
{
	return _weapon->getName();
}

void Room::takeWeapon(Player& player)
{
	if (_weapon->getDammage() > player.getWeaponDamage(player.getWeapon()))
	{
		player.setWeapon(_weapon);
		std::cout << "You equip it.\n\n";
	}
	else
	{
		std::cout << "\n";
	}
	_weapon = nullptr;
}

void Room::generateArmor(Armor* armor)
{
	if (rand() % 4 == 1)
	{
		switch (armor->getType())
		{
		case Type::HELMET:
			helmet = armor;
			break;
		case Type::CHESTPLATE:
			chestplate = armor;
			break;
		case Type::LEGGING:
			legging = armor;
			break;
		case Type::BOOTS:
			boots = armor;
			break;
		};
	}
}

std::string Room::getArmorName(Armor* armor)
{
	return armor->getName();
}

void Room::takeArmor(Player& player, Armor* armor)
{
	switch (armor->getType())
	{
	case Type::HELMET:
		if (player.getHelmet() != nullptr)
		{
			if (armor->getDefense() > player.getArmorDefense(player.getHelmet()))
			{
				player.setArmor(armor);
				std::cout << "You equip it.\n\n";
			}
			else
			{
				std::cout << "\n\n";
			}
		}
		else {
			player.setArmor(armor);
			std::cout << "You equip it.\n\n";
		}
		helmet = nullptr;
		break;
	case Type::CHESTPLATE:
		if (player.getChestplate() != nullptr)
		{
			if (armor->getDefense() > player.getArmorDefense(player.getChestplate()))
			{
				player.setArmor(armor);
				std::cout << "You equip it.\n\n";
			}
			else
			{
				std::cout << "\n\n";
			}
		}
		else
		{
			player.setArmor(armor);
			std::cout << "You equip it.\n\n";
		}
		chestplate = nullptr;
		break;
	case Type::LEGGING:
		if (player.getLegging() != nullptr)
		{
			if (armor->getDefense() > player.getArmorDefense(player.getLegging()))
			{
				player.setArmor(armor);
				std::cout << "You equip it.\n\n";
			}
			else
			{
				std::cout << "\n\n";
			}
		}
		else
		{
			player.setArmor(armor);
			std::cout << "You equip it.\n\n";
		}
		legging = nullptr;
		break;
	case Type::BOOTS:
		if (player.getBoots() != nullptr)
		{
			if (armor->getDefense() > player.getArmorDefense(player.getBoots()))
			{
				player.setArmor(armor);
				std::cout << "You equip them.\n\n";
			}
			else
			{
				std::cout << "\n\n";
			}
		}
		else
		{
			player.setArmor(armor);
			std::cout << "You equip them.\n\n";
		}
		boots = nullptr;
		break;
	};
}

void Room::generateMonster()
{
	if (rand() % 5 == 2)
	{
		monster = new Monster();
	}
}

void Room::deleteMonster()
{
	delete monster;
	monster = nullptr;
}

Room::~Room()
{
	if (_weapon)
	{
		delete _weapon;
		_weapon = nullptr;
	}
	if (helmet)
	{
		delete helmet;
		helmet = nullptr;
	}
	if (chestplate)
	{
		delete chestplate;
		chestplate = nullptr;
	}
	if (legging)
	{
		delete legging;
		legging = nullptr;
	}
	if (boots)
	{
		delete boots;
		boots = nullptr;
	}
	if (monster)
	{
		delete monster;
		monster = nullptr;
	}
	if (treasure)
	{
		delete treasure;
		treasure = nullptr;
	}
}