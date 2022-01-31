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

Vec2 HelloWorld::offSetScreen(Vec2 playerLocation) {
    Size const screenSize = Director::getInstance()->getVisibleSize();
    if (screenSize.width > screenSize.height) {
        if (playerLocation.y > screenSize.height / 2) {
            if (playerLocation.y < m_tileMap->getMapSize().height * m_tileMap->getTileSize().height * m_mapRatio - (screenSize.height / 2)) {
                // Follow transition
                return Vec2(0.f, playerLocation.y - (screenSize.height / 2));
            }
            // Top fixed
            return Vec2(0.f, m_tileMap->getMapSize().height * m_tileMap->getTileSize().height - screenSize.height);
        }
    }
    else if (screenSize.width < screenSize.height) {
        if (playerLocation.x > screenSize.width / 2) {
            if (playerLocation.x < m_tileMap->getMapSize().width * m_tileMap->getTileSize().width * m_mapRatio - (screenSize.width / 2)) {
                // Follow transition
                return Vec2(playerLocation.x - (screenSize.width / 2), 0.f);
            }
            // Right fixed
            return Vec2(0.f, m_tileMap->getMapSize().width * m_tileMap->getTileSize().width - screenSize.width);
        }
    }
    return Vec2::ZERO;
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
        this->addChild(_player, 0);
    }

    // follow the player
    auto followTheSprite = Follow::create(_player, Rect(0,0,followSize.width, followSize.height));
    this->runAction(followTheSprite);

    //Animation of the character
    player.createAnimation();

    //Add pokeball
    pokeball.setTreasureSprite("player/pokeball.png", Rect(0, 0, 16, 24));
    auto _pb = pokeball.getTreasureSprite();
    if (_pb == nullptr)
    {
        problemLoading("'player/pokeball.png'");
    }
    else
    {
        _pb->setPosition(Vec2(visibleSize.width / 2 + origin.x + 80, visibleSize.height / 2 + origin.y));
        this->addChild(_pb, 0);
    }
    log("%d", pokeball.getGoldNumber());

    //Add pickButton
    auto pickButton = MenuItemImage::create("pick.png", "pick.png",
        [=](Ref*) {
            pickPockeball(_pb, visibleSize, origin);
        });
    if (pickButton == nullptr || pickButton->getContentSize().width <= 0 || pickButton->getContentSize().height <= 0) {
        problemLoading("'pick.png'");
    }
    else {
        float x = origin.x + visibleSize.width * 5.15;
        float y = origin.y - visibleSize.height * 4;
        pickButton->setPosition(Vec2(x, y));
    }
    auto menu = Menu::create(pickButton, NULL);
    menu->setPosition(Vec2::ZERO);
    menu->setScale(0.1f, 0.1f);
    menu->setVisible(false);
    this->addChild(menu, 1);

   
    //Move character on click
    auto listener = EventListenerTouchOneByOne::create();
    const int movementTag = 1;
    listener->onTouchBegan = [=](Touch* touch, Event* event) {

        Vec2 pos = touch->getLocation();
        // touch->getLocationInView();
        // 
        //Vec2 destination =  pos - visibleSize/2 + _player->getPosition();
        /*cocos2d::log("%f", pos.x);
        log("%f", pos.y);*/

        Vec2 offSet = offSetScreen(pos);
        pos += offSet;

        /*cocos2d::log("%f", pos.x);
        log("%f", pos.y);*/

        Vec2 vector = { _player->getPosition().x - pos.x, _player->getPosition().y - pos.y };
        
        /*log("%f", touch->getLocationInView().x);
        log("%f", touch->getLocationInView().y);*/



        float angle = vector.getAngle() * 180 / PI;

        if (angle > -135 && angle < -45)
        {
            player.setDirection(UP);
        } else if (angle > -45 && angle < 45)
        {
            player.setDirection(LEFT);
        } else if (angle > 45 && angle < 135)
        {
            player.setDirection(DOWN);
        } else
        {
            player.setDirection(RIGHT);
        }
        player.updateAnimation(_player, player.getDirection());
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
                menu->setVisible(true);
            }
            else {
                menu->setVisible(false);
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

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    //Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}