#pragma once

#include <iostream>
#include <string>
#include "item.h"
#include "cocos2d.h"


class Map;

class Player
{
public:
	Player();
	void receiveDammage(int nbDammage);
	void setWeapon(Weapon* weapon) { _weapon = weapon; };
	Weapon* getWeapon() { return _weapon; };
	std::string getWeaponName(Weapon* weapon) { return weapon->getName(); };
	int getWeaponDamage(Weapon* weapon) { return weapon->getDammage(); };
	void setArmor(Armor* armor);
	Armor* getHelmet() { return _helmet; };
	Armor* getChestplate() { return _chestplate; };
	Armor* getLegging() { return _legging; };
	Armor* getBoots() { return _boots; };
	std::string getArmorName(Armor* armor) { return armor->getName(); };
	int getArmorDefense(Armor* armor) { return armor->getDefense(); };
	int getDefense();
	bool isAlive() { return life > 0; };
	void heal() { life = 100; };
	int getLife() { return life; };
	std::string &GetName() { return _name; };
	void setName(std::string playerName) { _name = playerName; };
	void setGold(int newGold) { gold = gold + newGold; };
	int getGold() { return gold; };
	//void setPlayerY(int _playerY) { playerY = _playerY; };
	//void setPlayerX(int _playerX) { playerX = _playerX; };
	//int getPlayerY() { return playerY; };
	//int getPlayerX() { return playerX; };
	void setPlayerSprite(std::string path, cocos2d::Rect size);
	cocos2d::Sprite* getPlayerSprite();

protected:
	std::string _name;
	int life = 100;
	int gold = 0;
	Weapon* _weapon = nullptr;
	Armor* _helmet = nullptr;
	Armor* _chestplate = nullptr;
	Armor* _legging = nullptr;
	Armor* _boots = nullptr;
	//int playerX = 0;
	//int playerY = 0;
	cocos2d::Sprite* playerSprite = nullptr;
	
};

class Monster
{
public:
	Monster();
	void receiveDammage(int nbDammage);
	bool isAlive() { return life > 0; };
	std::string getName() { return _name; };
	int getLife() { return life; };
	int getDamage() { return dammage; };
	void setMonsterSprite(std::string path, cocos2d::Rect size);
	cocos2d::Sprite* getMonsterSprite();

protected:
	std::string _name;
	int life;
	int dammage;
	cocos2d::Sprite* monsterSprite = nullptr;
};