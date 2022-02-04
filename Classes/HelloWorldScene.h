/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "entities.h"
#include "item.h"
#include "lifebar.h"
#include "Utils.h"
#include "MapHandler.h"

class HelloWorld : public cocos2d::Scene
{
private:
    Player player;
    LifeBar* charaLife = new LifeBar(player.getLife());
    Monster pokemon;
    cocos2d::Sprite* _pokemon;
    LifeBar* pokeLife = new LifeBar(pokemon.getLife());
    Treasure pokeball;
    cocos2d::Sprite* _pb;
    Weapon weapon = Weapon("Hands", 10);
    cocos2d::Sprite* _weapon;
    Armor helmet = Armor("", 0, Type::HELMET);
    Armor chestplate = Armor("", 0, Type::CHESTPLATE);
    Armor legging = Armor("", 0, Type::LEGGING);
    Armor boots = Armor("", 0, Type::BOOTS);
    cocos2d::CCTMXTiledMap* m_tileMap;
    cocos2d::CCTMXLayer* m_collisions;
    cocos2d::CCTMXLayer* m_doorsLayer;
    cocos2d::Node* m_intermediateNode;
    MapHandler m_mapHandler;
    float m_mapRatio = 1;
    cocos2d::Sprite* m_mapDraw;
    



public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    cocos2d::Size setTileMap();
    cocos2d::Vec2 offSetScreen(cocos2d::Vec2 playerLocation);
    float compareToOffset(float player, float screen, float tileMap);
    cocos2d::Vec2 HelloWorld::getTileNumber(cocos2d::Vec2 coords);
    void setDirection(float directionAngle);

    void fightPokemon(cocos2d::Sprite* _player, cocos2d::Sprite* _pk);
    void pickPockeball(cocos2d::Sprite* _pb, cocos2d::Size _size, cocos2d::Vec2 _origin);
    void pickWeapon(cocos2d::Label* _wpAtk);
    
    void makeMapAppear();
    void makeMapDissapear();
    
    bool isOnDoorTile(cocos2d::Vec2);

    bool changeRoom(cocos2d::Vec2);
    void updateRoom(cocos2d::Label* _playerAtk, cocos2d::Label* _pokeAtk);
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);


};

#endif // __HELLOWORLD_SCENE_H__