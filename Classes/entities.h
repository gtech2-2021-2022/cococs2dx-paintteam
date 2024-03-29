#pragma once

#include <iostream>
#include <string>
#include "item.h"
#include "cocos2d.h"
#include "Utils.h"


class Map;

enum Direction {UP, DOWN, LEFT, RIGHT};

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
	void setPlayerY(int _playerY) { playerY = _playerY; };
	void setPlayerX(int _playerX) { playerX = _playerX; };
	int getPlayerY() { return playerY; };
	int getPlayerX() { return playerX; };
	void setPlayerSprite(const char* path, const cocos2d::Rect size) { playerSprite = Utils::createSprite(path, size); };
	cocos2d::Sprite* getPlayerSprite() { return playerSprite; };
	void createAnimation();
	void updateAnimation(cocos2d::Sprite* _player, enum Direction direction);
	void setDirection(Direction _direction) { direction = _direction;  };
	Direction getDirection() { return direction;  };
	const float getPixelSpeed() noexcept { return pixelPerSecond; };
	void becomeIdle();
	void changeCanMove() { move = !move; }
	bool canMove() { return move; }

protected:
	std::string _name;
	int life = 100;
	int gold = 0;
	Weapon* _weapon = nullptr;
	Armor* _helmet = nullptr;
	Armor* _chestplate = nullptr;
	Armor* _legging = nullptr;
	Armor* _boots = nullptr;
	int playerX = 0;
	int playerY = 0;
	cocos2d::Sprite* playerSprite = nullptr;
	Direction direction;
	float const pixelPerSecond = 115;
	bool move = true;
	
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
	void setMonsterSprite();
	cocos2d::Sprite* getMonsterSprite();
	void createAnimation();
	void updateAnimation(cocos2d::Sprite* _pokemon, enum Direction direction);
	void becomeIdle();
	void setDirection(Direction _direction) { direction = _direction; };
	Direction getDirection() { return direction; };
	int getGold() { return gold; };
	void setName(std::string name) { _name = name; };
	cocos2d::Rect getTextureRect();
	void setDamage(int _dmg) { dammage = _dmg; };
	void setLife(int _life) { life = _life; };

protected:
	std::string _name;
	int life;
	int dammage;
	cocos2d::Sprite* monsterSprite = nullptr;
	Direction direction;
	int gold;
};