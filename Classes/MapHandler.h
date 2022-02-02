#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include "entities.h"
#include "item.h"

class Player;

class Monster;

class Weapon;

class Armor;

class Treasure;

class Room
{

public:
	enum class Exist
	{
		YES,
		NO
	};

	Room(Exist e = Exist::NO) : exist(e) {};
	~Room();
	bool isRoomExisting() { return exist == Exist::YES ? true : false; }
	void setExist() { exist = Exist::YES; }
	void link(Room* n, Room* s, Room* e, Room* w);
	bool hasNorthLink() { return north != nullptr; }
	bool hasSouthLink() { return south != nullptr; }
	bool hasEastLink() { return east != nullptr; }
	bool hasWestLink() { return west != nullptr; }
	bool hasTreasure() { return treasure != nullptr; }
	bool hasWeapon() { return _weapon != nullptr; }
	bool hasHelmet() { return helmet != nullptr; }
	bool hasChestplate() { return chestplate != nullptr; }
	bool hasLegging() { return legging != nullptr; }
	bool hasBoots() { return boots != nullptr; }
	bool hasMonster() { return monster != nullptr; }
	void generateTreasure();
	int getTreasureGold();
	void takeTreasure(Player &player);
	void deleteTreasure();
	void generateWeapon(Weapon *weapon);
	std::string getWeaponName();
	void takeWeapon(Player &player);
	void generateArmor(Armor* weapon);
	std::string getArmorName(Armor* armor);
	Armor* getHelmet() { return helmet; };
	Armor* getChestplate() { return chestplate; };
	Armor* getLegging() { return legging; };
	Armor* getBoots() { return boots; };
	void takeArmor(Player& player, Armor* armor);
	void generateMonster();
	void deleteMonster();
	Monster* getMonster() { return monster;  };

protected:
	Exist exist;
	Room* north = nullptr;
	Room* south = nullptr;
	Room* east = nullptr;
	Room* west = nullptr;
	Treasure* treasure = nullptr;
	Monster* monster = nullptr;
	Weapon* _weapon = nullptr;
	Armor* helmet = nullptr;
	Armor* chestplate = nullptr;
	Armor* legging = nullptr;
	Armor* boots = nullptr;
	
};


class MapHandler
{
public:
	const int size = 5;
	MapHandler();
	Room& getRoom(int y, int x) { return _room[y][x]; };
	int getPlayerY() { return playerY; };
	int getPlayerX() { return playerX; };
	bool win();
protected:
	std::vector<std::vector<Room>> _room;
	std::vector<Weapon> _weapons;
	std::vector<Armor> _armors;
	int playerY;
	int playerX;
};