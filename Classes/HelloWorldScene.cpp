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

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <math.h>
#define PI           3.14159265358979323846  /* possiblement */

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}


Size HelloWorld::setTileMap() {

    m_tileMap = CCTMXTiledMap::create("Texture/TestRoom.tmx");
    m_collisions = m_tileMap->layerNamed("Collisions");
    m_doorsLayer = m_tileMap->layerNamed("Doors");
    m_collisions->setVisible(false);
    m_doorsLayer->setVisible(false);
    /*
    All layers with != y level 
    DoorsOrigin 8
    Doors 7
    Collisions 6...
    Grass
    Rocks
    Wall2
    Wall
    Ground2 ...1
    Ground 0
    */
    //_tileMap->setTileSize({ 32, 32 }); Does not work maybe call before create?
    m_intermediateNode->addChild(m_tileMap);

    Size const screenSize = Director::getInstance()->getVisibleSize();
    Size const tileMapSize = { m_tileMap->getMapSize().width * m_tileMap->getTileSize().width, m_tileMap->getMapSize().height * m_tileMap->getTileSize().height };

    Size followSize;
    if (screenSize.width < screenSize.height) {
        m_mapRatio = (tileMapSize.height > screenSize.height) ? screenSize.height / tileMapSize.height : tileMapSize.height / screenSize.height;
        followSize = Size({ tileMapSize.width* m_mapRatio, screenSize.height });
    }
    else {
        m_mapRatio = (tileMapSize.width > screenSize.width) ? screenSize.width / tileMapSize.width : tileMapSize.width / screenSize.width;
        followSize = (screenSize.width == screenSize.height) ? Size({ screenSize.width, screenSize.height }) : Size({screenSize.width, tileMapSize.height* m_mapRatio });
    }
    
    m_tileMap->setScale(m_mapRatio);
    m_mapHandler.setDoors(m_tileMap);
    m_mapHandler.updateDoors(player.getPlayerX(), player.getPlayerY());
    return followSize;
}



Vec2 HelloWorld::getTileNumber(Vec2 coords) {
    Vec2 tileSize = m_tileMap->getTileSize() * m_mapRatio;
    Vec2 tileCoord = coords - Vec2(fmod(coords.x, tileSize.x), fmod(coords.y, tileSize.y));
    Vec2 tileNumber = Vec2(floor(tileCoord.x/tileSize.x), ceil(m_tileMap->getMapSize().height - 1 - tileCoord.y/tileSize.y)); // -1 because y starts at 0 for tiles but height must be < mapSize
    return tileNumber;
}

float HelloWorld::compareToOffset(float player, float screen, float tileMap) {
    if (player > screen / 2) {
        if (player < tileMap - (screen / 2)) {
            // Follow transition
            return player - (screen / 2);
        }
        // Top fixed
        return tileMap - screen;
    }
    return 0.f;
}

Vec2 HelloWorld::offSetScreen(Vec2 playerLocation) {
    Size const screenSize = Director::getInstance()->getVisibleSize();
    if (screenSize.width > screenSize.height) {
        return Vec2(0.f, compareToOffset(playerLocation.y, screenSize.height, m_tileMap->getMapSize().height * m_tileMap->getTileSize().height * m_mapRatio));
    }
    else if (screenSize.width < screenSize.height) {
        return Vec2(0.f, compareToOffset(playerLocation.x, screenSize.width, m_tileMap->getMapSize().width * m_tileMap->getTileSize().width * m_mapRatio));
    } 
    else {
        return Vec2(0.f, 0.f);
    }
}

void HelloWorld::setPlayerDirection(float directionAngle) {
    if (directionAngle > 45 && directionAngle < 135)
    {
        player.setDirection(UP);
    }
    else if (directionAngle > 135 && directionAngle < 225)
    {
        player.setDirection(LEFT);
    }
    else if (directionAngle > 225 && directionAngle < 315)
    {
        player.setDirection(DOWN);
    }
    else
    {
        player.setDirection(RIGHT);
    }
}


// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    m_intermediateNode = Node::create();
    this->addChild(m_intermediateNode);

    Director::getInstance()->setContentScaleFactor(1);
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //Add map
    Size const followSize = setTileMap();
    
    MenuItemImage* backMapButton = MenuItemImage::create("mapBackButton.png", "mapBackButton.png",
        [=](Ref*) {
            makeMapDissapear();
        }
        );
    if (backMapButton == nullptr || backMapButton->getContentSize().width <= 0 || backMapButton->getContentSize().height <= 0) {
        Utils::problemLoading("'map.png'");
    }
    backMapButton->setName("mapButton");
    auto bMB = Menu::create(backMapButton, NULL);
    bMB->setName("mapMenuButton");
    this->addChild(bMB);
    backMapButton->setAnchorPoint(Vec2::ZERO);
    bMB->setPosition(origin);
    backMapButton->setScale((visibleSize.width > visibleSize.height) ? visibleSize.width / backMapButton->getContentSize().width : visibleSize.width / backMapButton->getContentSize().height);
    backMapButton->setVisible(false);

    m_mapHandler.setBackMapSprite();
    m_mapDraw = m_mapHandler.getBackMapSprite();
    this->addChild(m_mapDraw);
    m_mapHandler.setDrawnMapSprites(visibleSize);
    m_mapDraw->setVisible(false);
    

    //Add character
    player.setPlayerSprite("player/player.png", Rect(0, 0, 32, 32));
    auto _player = player.getPlayerSprite();
    _player->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    m_intermediateNode->addChild(_player, 1);

    // follow the player
    auto followTheSprite = Follow::create(_player, Rect(0,0,followSize.width, followSize.height));
    m_intermediateNode->runAction(followTheSprite);

    //Animation of the character
    player.createAnimation();

    //Character's life
    auto _charaLife = charaLife->getLifeBar();
    if (_charaLife == nullptr)
    {
        Utils::problemLoading("'life.png'");
    }
    else
    {
        _charaLife->setPosition(Vec2(16, 35));
        _charaLife->setPercent(100);
        _charaLife->setScale(1.25, 1.25);
        _player->addChild(_charaLife, 1);
    }

    //Add pokemon
    pokemon.setMonsterSprite();
    auto _pokemon = pokemon.getMonsterSprite();
    _pokemon->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 1.25 + origin.y));
    m_intermediateNode->addChild(_pokemon, 0);

    //Pokemon's life
    auto _pokeLife = pokeLife->getLifeBar();
    if (_pokeLife == nullptr)
    {
        Utils::problemLoading("'life.png'");
    }
    else
    {
        _pokeLife->setPosition(Vec2(16, 35));
        _pokeLife->setPercent(100);
        _pokeLife->setScale(1.25, 1.25);
        _pokemon->addChild(_pokeLife, 0);
    }

    //Add pokeball
    pokeball.setTreasureSprite("player/pokeball.png", Rect(0, 0, 16, 24));
    auto _pb = pokeball.getTreasureSprite();
    _pb->setPosition(Vec2(visibleSize.width / 2 + origin.x + 50, visibleSize.height / 1.25 + origin.y));
    m_intermediateNode->addChild(_pb, 0);

    //Add fightButton
    auto fightButton = MenuItemImage::create("fight.png", "fight.png",
        [=](Ref*) {
            fightPokemon(player, _player, charaLife, pokemon, _pokemon, pokeLife);
        });
    if (fightButton == nullptr || fightButton->getContentSize().width <= 0 || fightButton->getContentSize().height <= 0) {
        Utils::problemLoading("'fight.png'");
    }
    auto fight = Menu::create(fightButton, NULL);
    fight->setPosition(Vec2::ZERO);
    fight->setVisible(false);
    m_intermediateNode->addChild(fight, 1);

    //Add pickButton
    auto pickButton = MenuItemImage::create("pick.png", "pick.png",
        [=](Ref*) {
            pickPockeball(_pb);
        });
    if (pickButton == nullptr || pickButton->getContentSize().width <= 0 || pickButton->getContentSize().height <= 0) {
        Utils::problemLoading("'pick.png'");
    }
    auto pick = Menu::create(pickButton, NULL);
    pick->setPosition(Vec2::ZERO);
    pick->setVisible(false);
    m_intermediateNode->addChild(pick, 1);
    
    //Add MapButton
    auto mapButton = MenuItemImage::create("map.png", "mapSelected.png",
        [=](Ref*) {
            makeMapAppear();
        });
    if (mapButton == nullptr || mapButton->getContentSize().width <= 0 || mapButton->getContentSize().height <= 0) {
        Utils::problemLoading("'map.png'");
    }
    auto mapB = Menu::create(mapButton, NULL);
    mapB->setPosition(origin);
    mapButton->setPosition(Vec2(visibleSize.width - (mapButton->getContentSize().width), visibleSize.height - (mapButton->getContentSize().height)));
    mapB->setScale(m_mapRatio*2);
    mapB->setVisible(true);
    mapB->setName("openMapButton");
    this->addChild(mapB, 1);

    //Move character on click
    auto listener = EventListenerTouchOneByOne::create();
    const int movementTag = 1; // constexpr
    listener->onTouchBegan = [=](Touch* touch, Event* event) {
        if (isOnDoorTile(touch->getLocation() + offSetScreen(_player->getPosition())) && isOnDoorTile(_player->getPosition()) && player.canMove()) {
            log("both on tile");
            if (changeRoom(touch->getLocation() + offSetScreen(_player->getPosition()))) {
                log("Changed room");
                updateRoom();
                return true;
            }
        }
        
        fight->setVisible(false);
        pick->setVisible(false);

        Vec2 const pos = touch->getLocation() + offSetScreen(_player->getPosition());  
        MoveTo* move = MoveTo::create(Vec2(pos - _player->getPosition()).length()/player.getPixelSpeed(), pos);
        setPlayerDirection(fmod(Vec2(_player->getPosition().x - pos.x, _player->getPosition().y - pos.y).getAngle() * 180 / PI + 180, 360));
        player.updateAnimation(_player, player.getDirection());
        
        auto playerStop = [=]() {
            player.becomeIdle();

            if (_player->getBoundingBox().intersectsRect(_pb->getBoundingBox())) {
                float x = origin.x + visibleSize.width - pickButton->getContentSize().width / 20;
                float y = origin.y + pickButton->getContentSize().height / 20;
                pickButton->setPosition(Vec2(x, y) + offSetScreen(pos));
                pickButton->setScale(0.1f, 0.1f);
                pick->setVisible(true);
            }
            if (_player->getBoundingBox().intersectsRect(_pokemon->getBoundingBox())) {
                float x = origin.x + visibleSize.width - fightButton->getContentSize().width / 20;
                float y = origin.y + fightButton->getContentSize().height / 20;
                fightButton->setPosition(Vec2(x, y) + offSetScreen(pos));
                fightButton->setScale(0.1f, 0.1f);
                fight->setVisible(true);
            }
        };
        CallFunc* becomeIdle = CallFunc::create(playerStop);
        move->setTag(movementTag);

        Sequence* moveThenIdle = Sequence::create({move, becomeIdle});

        if (_player->getNumberOfRunningActions() == 0) {
            _player->runAction(moveThenIdle);
        }
        else if (_player->getNumberOfRunningActions() != 0) {
            _player->stopActionByTag(movementTag);
            _player->runAction(moveThenIdle);
        }
        return true;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

void HelloWorld::fightPokemon(Player _player, cocos2d::Sprite* _pl, LifeBar* _charaLife, Monster _pokemon, cocos2d::Sprite* _pk, LifeBar* _pokeLife) {
    _pokemon.receiveDammage(_player.getWeaponDamage(_player.getWeapon()));
    _pokeLife->updateLife(_player.getWeaponDamage(_player.getWeapon()));
    if (_pokeLife->getLife() != 0) {
        _player.receiveDammage(_pokemon.getDamage());
        _charaLife->updateLife(_pokemon.getDamage());
        if (_charaLife->getLife() == 0) {
            m_intermediateNode->removeChild(_pl);
        }
    }
    else {
        m_intermediateNode->removeChild(_pk);
    }
}

void HelloWorld::pickPockeball(Sprite* _pb) {
    if (!pokeball.isOpen()) {
        pokeball.setOpen(true);
        _pb->setTexture("player/pokeball.png");
        _pb->setTextureRect(Rect(32, 0, 16, 24));
    }
}

void HelloWorld::makeMapAppear() {
    m_mapDraw->removeAllChildren();
    m_mapHandler.createMapAndDraw(player.getPlayerX(), player.getPlayerY()); 
    Node* _button = this->getChildByName("mapMenuButton")->getChildByName("mapButton");
    m_mapDraw->setVisible(true);
    _button->setVisible(true);
    FadeIn* fadeInAction = FadeIn::create(0.75f);
    m_mapDraw->runAction(fadeInAction);
    _button->runAction(fadeInAction);
    
    MenuItemImage* closeBtn = MenuItemImage::create("pokeCloseNormal.png", "pokeCloseSelected.png",
        [=](Ref*) {
            makeMapDissapear();
        }
    );
    if (closeBtn == nullptr || closeBtn->getContentSize().width <= 0 || closeBtn->getContentSize().height <= 0) {
        Utils::problemLoading("'pokeCloseNormal.png'");
    }
    closeBtn->setName("mapButton");
    auto cBtn = Menu::create(closeBtn, NULL);
    cBtn->setName("mapMenuButton");
    m_mapDraw->addChild(cBtn);
    closeBtn->setAnchorPoint(Vec2::ZERO);
    closeBtn->setZOrder(3);
    closeBtn->setScale(m_mapDraw->getContentSize().width * m_mapDraw->getScale() * 0.10f / closeBtn->getContentSize().width);
    closeBtn->setPosition(Vec2(closeBtn->getContentSize().width * closeBtn->getScale(), m_mapDraw->getContentSize().height * m_mapDraw->getScale()/3));
    


    Node* _openButton = this->getChildByName("openMapButton");
    _openButton->setVisible(false);
}

void HelloWorld::makeMapDissapear() {
    Node* _openButton = this->getChildByName("openMapButton");
    

    Node* _button = this->getChildByName("mapMenuButton")->getChildByName("mapButton");
    auto disappear = [=]() {
        _button->setVisible(false);
        m_mapDraw->setVisible(false);
        _openButton->setVisible(true);
    };

    CallFunc* GoodByeMap = CallFunc::create(disappear);
    FadeOut* fadeAction = FadeOut::create(0.75f);
    Sequence* FadeAndDisappear = Sequence::create({ fadeAction, GoodByeMap });
    m_mapDraw->runAction(FadeAndDisappear);
    _button->runAction(FadeAndDisappear);
    
}

bool HelloWorld::isOnDoorTile(Vec2 position) {
    Vec2 tileCoord = getTileNumber(position);
    Sprite* tileSprite = m_doorsLayer->getTileAt(tileCoord);
    return tileSprite != nullptr;
}


bool HelloWorld::changeRoom(Vec2 pos) {
    Vec2 middle = m_tileMap->getContentSize()/2.f * m_mapRatio;
    setPlayerDirection(fmod(Vec2(middle.x - pos.x, middle.y - pos.y).getAngle() * 180 / PI + 180, 360));
    int direction = player.getDirection();
    
    switch (direction)
    {
    case Direction::UP:
        log("up");
        if (m_mapHandler.roomYXHasNorthLink(player.getPlayerX(), player.getPlayerY())) {
            player.setPlayerY(player.getPlayerY() - 1);
            return true;
        }
        break;
    case Direction::DOWN:
        log("down");
        if (m_mapHandler.roomYXHasSouthLink(player.getPlayerX(), player.getPlayerY())) {
            player.setPlayerY(player.getPlayerY() + 1);
            return true;
        }
        break;
    case Direction::LEFT:
        log("left");
        if (m_mapHandler.roomYXHasWestLink(player.getPlayerX(), player.getPlayerY())) {
            player.setPlayerX(player.getPlayerX() - 1);
            
            return true;
        }
        break;
    case Direction::RIGHT:
        log("right");
        if (m_mapHandler.roomYXHasEastLink(player.getPlayerX(), player.getPlayerY())) {
            player.setPlayerX(player.getPlayerX() + 1);
            return true;
        }
        break;
    default:
        return false;
        break;
    }
    return false;
}

void HelloWorld::updateRoom() {
    player.changeCanMove();
    m_mapHandler.updateDoors(player.getPlayerX(), player.getPlayerY());
    player.changeCanMove();
}