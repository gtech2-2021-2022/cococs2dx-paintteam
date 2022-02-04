#include "MapHandler.h"

USING_NS_CC;

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

void MapHandler::createMapAndDraw(int xpos, int ypos) {
	/*
	size int
	_room[0->size-1][0->size-1] -> hasMonster, hasNorthLink, hasSouthLink, has...
	playerX, playerY int
	cocos2d::Sprite* m_sprite;
	
	float m_backRatio = 1;
	float m_elementRatio = 1;
	*/

	//calculate an offset rect where the 
	Vec2 offset = m_sprite->getContentSize() * m_backRatio * 0.15f;
	Size offsetSize = m_sprite->getContentSize() * m_backRatio * 0.85f;
	int tag = 0;
	for (int y = 0; y < size; y++)
	{
		for (int x = 0; x < size; x++)
		{
			if (_room[y][x].isRoomExisting()) {
				
				if (_room[y][x].hasBeenVisited()) {
					m_sprite->addChild(Utils::createElementWithTag(m_elements.visited, tag));
				}
				else {
					m_sprite->addChild(Utils::createElementWithTag(m_elements.unvisited, tag));
				}
				Node* roomSprite = m_sprite->getChildByTag(tag);


				float Xposition = offset.x + static_cast<float>(x) / static_cast<float>(size) * offsetSize.width;
				float Yposition =  (static_cast<float>(size - y) / static_cast<float>(size) * offsetSize.height);// -offset.y +
				float XMidOffset = roomSprite->getContentSize().width * roomSprite->getScale() / 2;
				float YMidOffset = roomSprite->getContentSize().height * roomSprite->getScale() / 2;
				Vec2 coords = Vec2(Xposition, Yposition);
				roomSprite->setPosition(coords);
				
			
				if (_room[y][x].hasNorthLink()) {
					m_sprite->addChild(Utils::createElement(m_elements.vertical, coords + Vec2(0, YMidOffset)));
				}
				if (_room[y][x].hasSouthLink()) {
					m_sprite->addChild(Utils::createElement(m_elements.vertical, coords + Vec2(0, -YMidOffset)));
				}
				if (_room[y][x].hasEastLink()) {
					m_sprite->addChild(Utils::createElement(m_elements.horizontal, coords + Vec2(XMidOffset, 0)));
				}
				if (_room[y][x].hasWestLink()) {
					m_sprite->addChild(Utils::createElement(m_elements.horizontal, coords + Vec2(-XMidOffset, 0)));
				}
				if (x == xpos && y == ypos) {
					m_sprite->addChild(Utils::createElement(m_elements.player, coords));
				} else if(_room[y][x].hasMonster()) {
					m_sprite->addChild(Utils::createElement(m_elements.enemy, coords));
				}
			}
			tag++;
		}
		/*m_sprite->addChild(Utils::createElement(m_elements.visited, Vec2::ZERO));
		m_sprite->addChild(Utils::createElement(m_elements.unvisited, offset));
		m_sprite->addChild(Utils::createElement(m_elements.unvisited, Vec2(offsetSize.width, offsetSize.height)));*/
	}
}

void MapHandler::setDrawnMapSprites(Size screenSize) {
	screenSize.width *= 0.95f, screenSize.height *= 0.95f;
	if (screenSize.width > screenSize.height) {
		m_backRatio = screenSize.height / m_sprite->getContentSize().height;
		m_elementRatio = (m_sprite->getContentSize().height * m_backRatio * 0.9f / size) / 30; // 0.9 for 10% of margin, 30 because room size is 15 + path size 15
	}
	else {
		m_backRatio = screenSize.width / m_sprite->getContentSize().width;
		m_elementRatio = (m_sprite->getContentSize().width * m_backRatio * 0.9f / size) / 30;
	}
	m_sprite->setScale(m_backRatio);
	m_sprite->setAnchorPoint({ 0, 0 });
	m_sprite->setPosition(screenSize/0.95f-screenSize);

	float headImageRation = 0.44f * m_elementRatio;
	// log("element ratio : %f, Head ratio : %f", m_elementRatio, headImageRation);

	m_elements.player = { Rect(0, 0, 17, 17), headImageRation, 2 , "player"};
	m_elements.enemy = { Rect(17, 0, 17, 17), headImageRation, 2 , "enemy"};
	m_elements.unvisited = { Rect(0, 17, 15, 15), m_elementRatio, 1 , "unvisited"};
	m_elements.visited = { Rect(15, 17, 15, 15), m_elementRatio, 1, "visited"};
	m_elements.vertical = { Rect(30, 17, 15, 15), m_elementRatio, 0, "vertical"};
	m_elements.horizontal = { Rect(45, 17, 15, 15), m_elementRatio, 0, "horizontal"};

}

void MapHandler::setDoors(CCTMXTiledMap* parent) {
	m_doors.top = setDoorSprite(parent, Rect(0, 0, 64, 64));
	m_doors.left = setDoorSprite(parent, Rect(64, 0, 64, 64));
	m_doors.right = setDoorSprite(parent, Rect(128, 0, 64, 64));
	m_doors.bottom = setDoorSprite(parent, Rect(192, 0, 64, 64));
	placeDoors(parent);
}

Sprite* MapHandler::setDoorSprite(CCTMXTiledMap* parent, Rect size) {
	Sprite* door = Utils::createSprite("Texture/doorTLRB.png", size);
	parent->addChild(door);
	door->setVisible(false);
	//door->setScale(1/parent->getScale());
	door->setLocalZOrder(9);
	return door;
}

void MapHandler::placeDoors(CCTMXTiledMap* map) {
	m_doors.top->setAnchorPoint({ 0, 1 });
	m_doors.left->setAnchorPoint({ 0, 0 });
	m_doors.right->setAnchorPoint({ 1, 0 });
	m_doors.bottom->setAnchorPoint({ 0, 0 });
	float xMidWithOffset = (map->getContentSize().width) / 2 -(m_doors.right->getContentSize().width / 2);
	float yMidWithOffset = (map->getContentSize().height) / 2 - (m_doors.right->getContentSize().height/ 2);
	m_doors.top->setPosition(xMidWithOffset, map->getContentSize().height);
	m_doors.bottom->setPosition(xMidWithOffset, map->getTileSize().height);
	m_doors.right->setPosition(map->getContentSize().width, yMidWithOffset);
	m_doors.left->setPosition(0, yMidWithOffset);
	//test
}

void MapHandler::updateDoors(int xpos, int ypos) {
	(_room[ypos][xpos].hasNorthLink()) ? m_doors.top->setVisible(true) : m_doors.top->setVisible(false);
	(_room[ypos][xpos].hasSouthLink()) ? m_doors.bottom->setVisible(true) : m_doors.bottom->setVisible(false);
	(_room[ypos][xpos].hasEastLink()) ? m_doors.right->setVisible(true) : m_doors.right->setVisible(false);
	(_room[ypos][xpos].hasWestLink()) ? m_doors.left->setVisible(true) : m_doors.left->setVisible(false);
	_room[ypos][xpos].isVisited();
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

void Room::generateWeapon(Weapon* weapon)
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
			}
		}
		else {
			player.setArmor(armor);
		}
		helmet = nullptr;
		break;
	case Type::CHESTPLATE:
		if (player.getChestplate() != nullptr)
		{
			if (armor->getDefense() > player.getArmorDefense(player.getChestplate()))
			{
				player.setArmor(armor);

			}
		}
		else
		{
			player.setArmor(armor);
		}
		chestplate = nullptr;
		break;
	case Type::LEGGING:
		if (player.getLegging() != nullptr)
		{
			if (armor->getDefense() > player.getArmorDefense(player.getLegging()))
			{
				player.setArmor(armor);
			}
		}
		else
		{
			player.setArmor(armor);
		}
		legging = nullptr;
		break;
	case Type::BOOTS:
		if (player.getBoots() != nullptr)
		{
			if (armor->getDefense() > player.getArmorDefense(player.getBoots()))
			{
				player.setArmor(armor);
			}

		}
		else
		{
			player.setArmor(armor);
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