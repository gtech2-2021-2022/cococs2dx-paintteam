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
#include "Utils.h"
#include "ui/CocosGUI.h"
#include <math.h>
#define PI           3.14159265358979323846  /* possiblement */

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

Size HelloWorld::setTileMap() {

    m_tileMap = CCTMXTiledMap::create("Texture/TestRoom.tmx");
    m_collisions = m_tileMap->layerNamed("Collisions");
    m_collisions->setVisible(false);
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
    this->addChild(m_tileMap);

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
    return followSize;


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


// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    Director::getInstance()->setContentScaleFactor(1);
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    /*/////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////*/

    //Add map
    Size followSize = setTileMap();
    
   


    //Add character
    player.setPlayerSprite("player/player.png", Rect(0, 0, 32, 32));
    auto _player = player.getPlayerSprite();
    if (_player == nullptr)
    {
        problemLoading("'player/player.png'");
    }
    else
    {
        _player->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        this->addChild(_player, 1);
    }

    // follow the player
    auto followTheSprite = Follow::create(_player, Rect(0,0,followSize.width, followSize.height));
    this->runAction(followTheSprite);

    //Animation of the character
    player.createAnimation();

    //Character's life
    auto _charaLife = charaLife->getLifeBar();
    if (_charaLife == nullptr)
    {
        problemLoading("'life.png'");
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
    if (_pokemon == nullptr)
    {
        problemLoading("'pokemon/enemy.png'");
    }
    else
    {
        _pokemon->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 1.25 + origin.y));
        this->addChild(_pokemon, 0);
    }

    //Pokemon's life
    auto _pokeLife = pokeLife->getLifeBar();
    if (_pokeLife == nullptr)
    {
        problemLoading("'life.png'");
    }
    else
    {
        _pokeLife->setPosition(Vec2(16, 35));
        _pokeLife->setPercent(100);
        _pokeLife->setScale(1.25, 1.25);
        _pokemon->addChild(_pokeLife, 0);
    }

    //Add fightButton
    auto fightButton = MenuItemImage::create("fight.png", "fight.png",
        [=](Ref*) {
            fightPokemon(player, _player, pokemon, _pokemon);
        });
    if (fightButton == nullptr || fightButton->getContentSize().width <= 0 || fightButton->getContentSize().height <= 0) {
        problemLoading("'fight.png'");
    }
    auto fight = Menu::create(fightButton, NULL);
    fight->setPosition(Vec2::ZERO);
    fight->setScale(0.1f, 0.1f);
    fight->setVisible(false);
    this->addChild(fight, 1);

    //Add pokeball
    pokeball.setTreasureSprite("player/pokeball.png", Rect(0, 0, 16, 24));
    auto _pb = pokeball.getTreasureSprite();
    if (_pb == nullptr)
    {
        problemLoading("'player/pokeball.png'");
    }
    else
    {
        _pb->setPosition(Vec2(visibleSize.width / 2 + origin.x + 50, visibleSize.height / 1.25 + origin.y));
        this->addChild(_pb, 0);
    }

    //Add pickButton
    auto pickButton = MenuItemImage::create("pick.png", "pick.png",
        [=](Ref*) {
            pickPockeball(_pb, visibleSize, origin);
        });
    if (pickButton == nullptr || pickButton->getContentSize().width <= 0 || pickButton->getContentSize().height <= 0) {
        problemLoading("'pick.png'");
    }
    auto pick = Menu::create(pickButton, NULL);
    pick->setPosition(Vec2::ZERO);
    pick->setScale(0.1f, 0.1f);
    pick->setVisible(false);
    this->addChild(pick, 1);

   
    //Move character on click
    auto listener = EventListenerTouchOneByOne::create();
    const int movementTag = 1;
    listener->onTouchBegan = [=](Touch* touch, Event* event) {
        fight->setVisible(false);
        pick->setVisible(false);
        Vec2 pos = touch->getLocation();
        /* log("x player : %f, y player : %f", _player->getPosition().x, _player->getPosition().y);*/

        // camera offset
        Vec2 offSet = offSetScreen(_player->getPosition());
        pos += offSet;

        Vec2 vector = { _player->getPosition().x - pos.x, _player->getPosition().y - pos.y };
        float directionAngle = fmod(vector.getAngle() * 180 / PI + 180, 360);
        log("angle : %f", directionAngle);
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
        player.updateAnimation(_player, player.getDirection());
        log("lenght: %f, speed: %f, time: %f", pos.length(), player.getPixelSpeed(), pos.length() / player.getPixelSpeed());
        auto move = MoveTo::create(pos.length()/player.getPixelSpeed(), pos);
        auto test = [=]() {
            _player->stopAllActions();
            Animation* anim;
            if (player.getDirection() == UP) {
                anim = AnimationCache::getInstance()->getAnimation("idleUpAnimation");
            }
            else if (player.getDirection() == DOWN) {
                anim = AnimationCache::getInstance()->getAnimation("idleDownAnimation");
            }
            else if (player.getDirection() == LEFT) {
                anim = AnimationCache::getInstance()->getAnimation("idleLeftAnimation");
            }
            else {
                anim = AnimationCache::getInstance()->getAnimation("idleRightAnimation");
            }
            auto sf = anim->getFrames().at(0)->getSpriteFrame();
            auto action = Animate::create(anim);
            _player->runAction(RepeatForever::create(action));
            if (_player->getBoundingBox().intersectsRect(_pb->getBoundingBox())) {
                float x = origin.x + visibleSize.width * 5.15;
                float y = origin.y - visibleSize.height * 4;
                pickButton->setPosition(Vec2(x, y) + offSetScreen(pos) * 10);
                pick->setVisible(true);
            }
            if (_player->getBoundingBox().intersectsRect(_pokemon->getBoundingBox())) {
                float x = origin.x + visibleSize.width * 5.15;
                float y = origin.y - visibleSize.height * 4;
                fightButton->setPosition(Vec2(x, y) + offSetScreen(pos) * 10);
                fight->setVisible(true);
            }
        };
        CallFunc* test2 = CallFunc::create(test);
        move->setTag(movementTag);
        Sequence* okmonbro = Sequence::create({move, test2});
        if (_player->getNumberOfRunningActions() == 0) {
            _player->runAction(okmonbro);
        }
        else if (_player->getNumberOfRunningActions() != 0) {
            _player->stopActionByTag(movementTag);
            _player->runAction(okmonbro);
        }
        return true;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

void HelloWorld::fightPokemon(Player _player, cocos2d::Sprite* _pl, Monster _pokemon, cocos2d::Sprite* _pk) {
    log("oooooooooo");
    _pokemon.receiveDammage(_player.getWeaponDamage(_player.getWeapon()));
    if (_pokemon.getLife() != 0) {
        _player.receiveDammage(_pokemon.getDamage());
        if (_player.getLife() == 0) {
            this->removeChild(_pl);
        }
    }
    else {
        this->removeChild(_pk);
    }
}

void HelloWorld::pickPockeball(Sprite* _pb, Size size, Vec2 origin) {
    this->removeChild(_pb);
    if (!pokeball.isOpen()) {
        this->removeChild(_pb);
        pokeball.setTreasureSprite("player/pokeball.png", Rect(32, 0, 16, 24));
        _pb = pokeball.getTreasureSprite();
        if (_pb == nullptr)
        {
            problemLoading("'player/pokeball.png'");
        }
        else
        {
            _pb->setPosition(Vec2(size.width / 2 + origin.x + 80, size.height / 2 + origin.y));
            this->addChild(_pb, 0);
        }
    }
}